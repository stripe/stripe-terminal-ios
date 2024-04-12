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
    weak var doneButton: UIBarButtonItem?
    private var completed = false

    /// Override this property with the log event that should be displayed when
    /// the test is cancelled.
    var cancelLogMethod: LogEvent.Method {
        return .cancelCollectPaymentMethod
    }

    internal var cancelable: Cancelable? {
        didSet {
            // Only allow explicit button cancel (no swipe to dismiss) for users of EventDisablingVC which are
            // used for collecting payment methods and so may have some additional work to do to fully cancel.
            setAllowedCancelMethods(cancelable != nil ? .button : [])
        }
    }
    var events: [Event] = [] {
        didSet {
            updateContent()
            let lastSection = tableView.numberOfSections - 1
            let lastRow = tableView.numberOfRows(inSection: lastSection) - 1
            if lastSection >= 0 && lastRow >= 0 {
                tableView.scrollToRow(at: IndexPath(row: lastRow, section: lastSection), at: .bottom, animated: true)
            }
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
        BluetoothOrUsbReaderDelegateAnnouncer.shared.removeListener(self)
        LocalMobileReaderDelegateAnnouncer.shared.removeListener(self)
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
        BluetoothOrUsbReaderDelegateAnnouncer.shared.addListener(self)
        LocalMobileReaderDelegateAnnouncer.shared.addListener(self)

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
        let displayIdentifier = reader.label ?? reader.serialNumber

        var logEvent = LogEvent(method: .reportReaderEvent)
        logEvent.result = .message("Disconnected from reader: \(displayIdentifier)")
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

// MARK: LocalMobileReaderDelegate
extension EventDisplayingViewController: LocalMobileReaderDelegate {
    func localMobileReader(_ reader: Reader, didStartInstallingUpdate update: ReaderSoftwareUpdate, cancelable: Cancelable?) {
        // No-op.
    }

    func localMobileReader(_ reader: Reader, didReportReaderSoftwareUpdateProgress progress: Float) {
        // No-op.
    }

    func localMobileReader(_ reader: Reader, didFinishInstallingUpdate update: ReaderSoftwareUpdate?, error: Error?) {
        // No-op.
    }

    func localMobileReader(_ reader: Reader, didRequestReaderInput inputOptions: ReaderInputOptions = []) {
        self.events.append({
            var event = LogEvent(method: .requestReaderInput)
            event.result = .message(Terminal.stringFromReaderInputOptions(inputOptions))
            return event
        }())
    }

    func localMobileReader(_ reader: Reader, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {
        self.events.append({
            var event = LogEvent(method: .requestReaderDisplayMessage)
            event.result = .message(Terminal.stringFromReaderDisplayMessage(displayMessage))
            return event
        }())
    }
}
