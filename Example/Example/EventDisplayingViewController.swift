//
//  EventDisplayingViewController.swift
//  Example
//
//  Created by Matthew Krager on 6/1/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class EventDisplayingViewController: TableViewController, CancelableViewController {

    private let headerView = ReaderHeaderView()
    private let logHeaderView = ActivityIndicatorHeaderView(title: "EVENT LOG")
    internal weak var cancelButton: UIBarButtonItem?
    private weak var doneButton: UIBarButtonItem?
    private var completed = false

    /// Override this property with the log event that should be displayed when
    /// the test is cancelled.
    var cancelLogMethod: LogEvent.Method {
        return .cancelCollectPaymentMethod
    }

    internal var cancelable: Cancelable? {
        didSet {
            setAllowedCancelMethods(cancelable != nil ? .all : [])
        }
    }
    var events: [Event] = [] {
        didSet {
            updateContent()
        }
    }

    init() {
        super.init(style: .grouped)
        self.title = "Testing"
        tableView.separatorInset = .zero
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    deinit {
        TerminalDelegateAnnouncer.shared.removeListener(self)
        BluetoothReaderDelegateAnnouncer.shared.removeListener(self)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()

        let doneButton = UIBarButtonItem(barButtonSystemItem: .done, target: self, action: #selector(doneAction))
        doneButton.isEnabled = false
        self.doneButton = doneButton

        let cancelButton = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(cancelAction))
        self.cancelButton = cancelButton

        setAllowedCancelMethods([])
        navigationItem.leftBarButtonItem = cancelButton
        navigationItem.rightBarButtonItem = doneButton

        TerminalDelegateAnnouncer.shared.addListener(self)
        BluetoothReaderDelegateAnnouncer.shared.addListener(self)

        if completed || Terminal.shared.paymentStatus != .ready {
            return
        }

        headerView.connectedReader = Terminal.shared.connectedReader
        headerView.connectionStatus = Terminal.shared.connectionStatus
        updateContent()
    }

    internal func complete() {
        title = "Test completed"
        doneButton?.isEnabled = true
        logHeaderView.activityIndicator.stopAnimating()
        completed = true
        setAllowedCancelMethods([.swipe])
    }

    private func updateContent() {
        dataSource.sections = [
            Section(header: "", rows: [], footer: Section.Extremity.view(headerView)),
            Section(header: Section.Extremity.view(logHeaderView), rows: events.map { logEvent -> Row in
                switch logEvent.result {
                case .started:
                    return Row(text: logEvent.method?.rawValue ?? "Unknown Event",
                               cellClass: MethodStartCell.self)
                default:
                    return Row(
                        text: logEvent.description,
                        detailText: logEvent.method?.rawValue,
                        selection: { [unowned self] in
                            self.navigationController?.pushViewController(logEvent.viewController, animated: true)
                        },
                        accessory: .disclosureIndicator,
                        cellClass: LogEventCell.self
                    )
                }
            })
        ]
    }

    @objc
    func doneAction() {
        dismiss(animated: true, completion: nil)
    }

    @objc
    func cancelAction() {
        var event = LogEvent(method: cancelLogMethod)
        self.events.append(event)
        cancelable?.cancel { error in
            if let error = error {
                event.result = .errored
                event.object = .error(error as NSError)
            } else {
                event.result = .succeeded
                self.dismiss(animated: true, completion: nil)
            }
            self.events.append(event)
        }
    }
}

// MARK: TerminalDelegate
extension EventDisplayingViewController: TerminalDelegate {
    func terminal(_ terminal: Terminal, didChangeConnectionStatus status: ConnectionStatus) {
        headerView.connectionStatus = status
    }

    func terminal(_ terminal: Terminal, didReportUnexpectedReaderDisconnect reader: Reader) {
        var logEvent = LogEvent(method: .reportReaderEvent)
        logEvent.result = .message("Disconnected from reader: \(reader.serialNumber)")
        self.events.append(logEvent)
        presentAlert(title: "Reader disconnected!", message: "")
    }
}

// MARK: BluetoothReaderDelegate
extension EventDisplayingViewController: BluetoothReaderDelegate {
    func reader(_ reader: Reader, didReportReaderEvent event: ReaderEvent, info: [AnyHashable: Any]?) {
        var logEvent = LogEvent(method: .reportReaderEvent)
        logEvent.result = .message(Terminal.stringFromReaderEvent(event))
        self.events.append(logEvent)
    }

    func reader(_ reader: Reader, didRequestReaderInput inputOptions: ReaderInputOptions = []) {
        var event = LogEvent(method: .requestReaderInput)
        event.result = .message(Terminal.stringFromReaderInputOptions(inputOptions))
        self.events.append(event)
    }

    func reader(_ reader: Reader, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {
        var event = LogEvent(method: .requestReaderDisplayMessage)
        event.result = .message(Terminal.stringFromReaderDisplayMessage(displayMessage))
        self.events.append(event)
    }

    func reader(_ reader: Reader, didReportAvailableUpdate update: ReaderSoftwareUpdate) {
    }

    func reader(_ reader: Reader, didStartInstallingUpdate update: ReaderSoftwareUpdate, cancelable: Cancelable?) {
    }

    func reader(_ reader: Reader, didReportReaderSoftwareUpdateProgress progress: Float) {
    }

    func reader(_ reader: Reader, didFinishInstallingUpdate update: ReaderSoftwareUpdate?, error: Error?) {
    }
}
