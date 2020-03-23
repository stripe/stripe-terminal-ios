//
//  ReaderDiscoveryViewController.swift
//  Dev
//
//  Created by Ben Guo on 7/18/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class ReaderDiscoveryViewController: TableViewController, DiscoveryDelegate {

    var onConnectedToReader: (Reader) -> () = { _ in }
    private let config: DiscoveryConfiguration
    private var discoverCancelable: Cancelable? = nil
    private weak var cancelButton: UIBarButtonItem?
    private let activityIndicatorView = ActivityIndicatorHeaderView(title: "HOLD READER NEARBY")
    private var readers: [Reader] = []

    private enum ViewState {
        /// Have not started discovering Readers yet
        case preDiscovery
        /// Actively discovering readers
        case discovering
        /// Actively connecting to a reader
        case connecting
        /// Done actively discovering readers
        case doneDiscovering
    }
    private var viewState = ViewState.preDiscovery

    init(discoveryConfig: DiscoveryConfiguration) {
        self.config = discoveryConfig
        super.init(style: .grouped)
        self.title = "Discovery"
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        let cancelButton = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(dismissAction))
        self.cancelButton = cancelButton
        navigationItem.leftBarButtonItem = cancelButton
        activityIndicatorView.activityIndicator.hidesWhenStopped = true

        updateContent()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)

        if viewState == .preDiscovery {
            // 1. discover readers
            discoverCancelable = Terminal.shared.discoverReaders(config, delegate: self) { error in
                if let error = error {
                    print("discoverReaders failed: \(error)")
                    self.presentAlert(error: error) { _ in
                        self.presentingViewController?.dismiss(animated: true, completion: nil)
                    }
                }
                self.discoverCancelable = nil;
                self.viewState = .doneDiscovering
                self.updateContent()
            }
            viewState = .discovering
            updateContent()
        }
    }

    private func updateContent() {
        updateActivityIndicatorView()

        let rows = readers.map { reader in
            row(for: reader,
                discoveryMethod: self.config.discoveryMethod,
                selection:{ [unowned self] in
                    self.connect(to: reader)
            })
        }

        dataSource.sections = [
            Section(header: Section.Extremity.view(activityIndicatorView),
                    rows: rows,
                    footer: (readers.isEmpty
                        ? nil
                        : footer(for: readers, discoveryMethod: self.config.discoveryMethod))
            )
        ]
    }

    // 2. connect to a selected reader
    private func connect(to reader: Reader, failIfInUse: Bool = true) {
        cancelButton?.isEnabled = false

        viewState = .connecting
        updateContent()
        Terminal.shared.connectReader(reader, connectionConfig: ConnectionConfiguration(failIfInUse: failIfInUse)) { connectedReader, error in
            if let connectedReader = connectedReader {
                self.discoverCancelable = nil
                self.onConnectedToReader(connectedReader)
                return
            } else if let error = error as NSError?,
                error.code == ErrorCode.connectFailedReaderIsInUse.rawValue {
                self.presentAlert(
                    title: "\(reader.label ?? reader.serialNumber) in use",
                    message: "Reader is already collecting a payment. Interrupt the in-progress transaction?",
                    okButtonTitle: "Interrupt",
                    handler: { (shouldInterrupt) in
                        if shouldInterrupt {
                            self.connect(to: reader, failIfInUse: false)
                        } else {
                            self.viewState = .discovering
                            self.updateContent()
                        }
                })
            } else if let error = error {
                self.presentAlert(error: error)
                self.viewState = .discovering
                self.updateContent()
            }
            self.cancelButton?.isEnabled = true
        }
    }

    @objc func dismissAction() {
        if let cancelable = discoverCancelable {
            cancelable.cancel { error in
                if let error = error {
                    print("cancel discoverReaders failed: \(error)")
                } else {
                    self.presentingViewController?.dismiss(animated: true, completion: nil)
                }
                self.discoverCancelable = nil
            }
        } else {
            presentingViewController?.dismiss(animated: true, completion: nil)
        }
    }

    // MARK: SCPDiscoveryDelegate
    func terminal(_ terminal: Terminal, didUpdateDiscoveredReaders readers: [Reader]) {
        self.readers = readers
        switch (self.config.discoveryMethod, readers.count) {
        case (.bluetoothProximity, 1) where readers.first?.batteryLevel != nil:
            // Once we've received battery level, don't expect further callbacks
            viewState = .doneDiscovering
        case (.internet, _):
            // internet only has one callback
            viewState = .doneDiscovering
        default:
            // If receiving `didUpdateDiscoveredReaders` calls, still actively discovering.
            // This also covers the case where the `.bluetoothProximity` Reader goes away.
            viewState = .discovering
        }
        updateContent()
    }

    // MARK: - updateContents helpers

    private func updateActivityIndicatorView() {
        if viewState == .discovering || viewState == .connecting {
            activityIndicatorView.activityIndicator.startAnimating()
        } else {
            activityIndicatorView.activityIndicator.stopAnimating()
        }

        switch (config.discoveryMethod, readers.count, viewState) {
        case (_, _, .connecting):
            activityIndicatorView.title = "Connecting..."

        case (.bluetoothProximity, 0, _):
            activityIndicatorView.title = "HOLD READER NEARBY"
        case (.bluetoothProximity, _, _):
            activityIndicatorView.title = "DISCOVERED READER"

        case (.bluetoothScan, _, _):
            activityIndicatorView.title = "NEARBY READERS"

        case (.internet, 0, .doneDiscovering):
            activityIndicatorView.title = "NO REGISTERED READERS FOUND"
        case (.internet, _, .doneDiscovering):
            activityIndicatorView.title = "REGISTERED READERS"
        case (.internet, _, _):
            activityIndicatorView.title = "LOOKING UP REGISTERED READERS"

        @unknown default:
            activityIndicatorView.title = "READERS"
        }
    }

    /// Returns a Row with details about the reader.
    ///
    /// The row formatting depends on the current discoveryMethod, as there are
    /// different things we choose to show our users.
    ///
    /// - Parameters:
    ///   - reader: the reader that the row should display
    ///   - discoveryMethod: how the reader was discovered
    ///   - selection: action to take when row is selected
    /// - Returns: A Row (from Static library) for this reader
    private func row(for reader: Reader, discoveryMethod: DiscoveryMethod, selection: @escaping Selection) -> Row {
        let detailText: String?

        if discoveryMethod == .internet {
            if reader.status == .online, let ipAddress = reader.ipAddress {
                detailText = ipAddress
            } else {
                detailText = "(offline)"
            }
        } else {
            if let battery = reader.batteryLevel {
                detailText = "🔋 \(String(format: "%.0f", battery.floatValue * 100))%"
            } else {
                detailText = nil
            }
        }

        // prefer reader's label, fall back to serial number
        return Row(text: reader.label ?? reader.serialNumber,
                   detailText: detailText,
                   selection: selection,
                   cellClass: Value1Cell.self)
    }

    /// Optionally return footer for this discovery method & readers.
    ///
    /// In `.bluetoothProximity` mode, there's only one reader discovered, and
    /// this displays it's current software version.
    /// In `.internet` mode, we display the iOS device's wifi IP address.
    ///
    /// - Parameters:
    ///   - readers: the readers being displayed in the table
    ///   - discoveryMethod: how those readers were discovered
    /// - Returns: optional footer to display on screen
    private func footer(for readers: [Reader], discoveryMethod: DiscoveryMethod) -> Section.Extremity? {
        if discoveryMethod == .bluetoothProximity, let softwareVersion = readers.first?.deviceSoftwareVersion {
            return Section.Extremity.title("Reader software: \(softwareVersion)")
        } else if self.config.discoveryMethod == .internet {
            // This is not dynamic: doesn't detect & update when network changes.
            // It's not the right solutions for store clerks, who shouldn't need to know
            // the network config, but may be a useful sanity check for developers
            // w/connectivity problems
            return Section.Extremity.title("Device IP: \(ifaddrs_h.getWifiIPAddress() ?? "unknown")")
        } else {
            return nil
        }
    }
}


