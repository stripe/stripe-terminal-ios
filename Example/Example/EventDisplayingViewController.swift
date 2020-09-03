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

enum Event {
    case log(LogEvent)
    case action(ActionEvent)
}

class EventDisplayingViewController: TableViewController, TerminalDelegate, ReaderDisplayDelegate, CancelableViewController {

    private let headerView = ReaderHeaderView()
    private let logHeaderView = ActivityIndicatorHeaderView(title: "EVENT LOG")
    internal weak var cancelButton: UIBarButtonItem?
    private weak var doneButton: UIBarButtonItem?
    private var completed = false

    internal var cancelable: Cancelable? = nil {
        didSet {
            setAllowedCancelMethods(cancelable != nil ? .all : [])
        }
    }
    var events: [Event] = [] {
        didSet {
            updateContent()
        }
    }

    override init(style: UITableView.Style) {
        super.init(style: style)
        self.title = "Testing"
        tableView.separatorInset = .zero
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    deinit {
        TerminalDelegateAnnouncer.shared.removeListener(self)
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
            Section(header: Section.Extremity.view(logHeaderView), rows: events.map { event in
                if case let Event.log(logEvent) = event {
                    switch logEvent.result {
                    case .started:
                        return Row(text: logEvent.method.rawValue,
                                   cellClass: MethodStartCell.self)
                    default:
                        return Row(text: logEvent.description, detailText: logEvent.method.rawValue, selection: { [unowned self] in
                            let vc = LogEventViewController(event: logEvent)
                            self.navigationController?.pushViewController(vc, animated: true)
                            }, accessory: .disclosureIndicator,
                               cellClass: LogEventCell.self)
                    }
                } else if case let Event.action(actionEvent) = event,
                    let nc = self.navigationController {
                    return Row(text: actionEvent.stringValue, selection: {
                        actionEvent.action(nc)
                    }, accessory: .disclosureIndicator)
                } else {
                    return Row()
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
        var event = LogEvent(method: .cancelCollectPaymentMethod)
        self.events.append(.log(event))
        cancelable?.cancel { error in
            if let error = error {
                event.result = .errored
                event.object = .error(error as NSError)
            } else {
                event.result = .succeeded
                self.dismiss(animated: true, completion: nil)
            }
            self.events.append(.log(event))
        }
    }

    // MARK: TerminalDelegate

    func terminal(_ terminal: Terminal, didChangeConnectionStatus status: ConnectionStatus) {
        headerView.connectionStatus = status
    }

    func terminal(_ terminal: Terminal, didReportReaderEvent event: ReaderEvent, info: [AnyHashable: Any]?) {
        var logEvent = LogEvent(method: .reportReaderEvent)
        logEvent.result = .message(Terminal.stringFromReaderEvent(event))
        self.events.append(.log(logEvent))
    }

    func terminal(_ terminal: Terminal, didReportUnexpectedReaderDisconnect reader: Reader) {
        var logEvent = LogEvent(method: .reportReaderEvent)
        logEvent.result = .message("Disconnected from reader: \(reader.serialNumber)")
        self.events.append(.log(logEvent))
        presentAlert(title: "Reader disconnected!", message: "")
    }

    // MARK: ReaderDisplayDelegate
    func terminal(_ terminal: Terminal, didRequestReaderInput inputOptions: ReaderInputOptions) {
        var event = LogEvent(method: .requestReaderInput)
        event.result = .message(Terminal.stringFromReaderInputOptions(inputOptions))
        self.events.append(.log(event))
    }

    func terminal(_ terminal: Terminal, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {
        var event = LogEvent(method: .requestReaderDisplayMessage)
        event.result = .message(Terminal.stringFromReaderDisplayMessage(displayMessage))
        self.events.append(.log(event))
    }
}
