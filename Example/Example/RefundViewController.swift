//
//  RefundViewController.swift
//  Example
//
//  Created by James Little on 3/16/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class RefundViewController: TableViewController, TerminalDelegate, ReaderDisplayDelegate, CancelableViewController {

    private let refundParameters: RefundParameters

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
    private var events: [LogEvent] = [] {
        didSet {
            updateContent()
        }
    }

    init(refundParams: RefundParameters) {
        self.refundParameters = refundParams
        super.init(style: .grouped)
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
        let doneButton = UIBarButtonItem(barButtonSystemItem: .done, target: self, action: #selector(doneAction))
        doneButton.isEnabled = false
        self.doneButton = doneButton
        let cancelButton = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(cancelAction))
        cancelButton.isEnabled = false
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


        // 1. collectRefundMethod
        var collectEvent = LogEvent(method: .collectRefundPaymentMethod)
        self.events.append(collectEvent)
        self.cancelable = Terminal.shared.collectRefundPaymentMethod(self.refundParameters) { collectError in
            if let error = collectError {
                collectEvent.result = .errored
                collectEvent.object = .error(error as NSError)
                self.events.append(collectEvent)
                self.complete()
            } else {
                collectEvent.result = .succeeded
                self.events.append(collectEvent)

                // 2. process refund
                var processEvent = LogEvent(method: .processRefund)
                self.events.append(processEvent)
                Terminal.shared.processRefund { processedRefund, processError in
                    if let error = processError {
                        processEvent.result = .errored
                        processEvent.object = .error(error as NSError)
                        self.events.append(processEvent)
                        self.complete()
                    } else if let refund = processedRefund, refund.status == .succeeded {
                        processEvent.result = .succeeded
                        processEvent.object = .refund(refund)
                        self.events.append(processEvent)
                        self.complete()
                    } else if processedRefund != nil {
                        self.events.append(processEvent)
                        self.complete()
                    }
                }
            }
        }
    }

    private func complete() {
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
                switch event.result {
                case .started:
                    return Row(text: event.method.rawValue,
                               cellClass: MethodStartCell.self)
                default:
                    return Row(text: event.description, detailText: event.method.rawValue, selection: { [unowned self] in
                        let vc = LogEventViewController(event: event)
                        self.navigationController?.pushViewController(vc, animated: true)
                    }, accessory: .disclosureIndicator, cellClass: LogEventCell.self)
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
        // cancel collectPaymentMethod
        var event = LogEvent(method: .cancelCollectRefundPaymentMethod)
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

    // MARK: TerminalDelegate

    func terminal(_ terminal: Terminal, didChangeConnectionStatus status: ConnectionStatus) {
        headerView.connectionStatus = status
    }

    func terminal(_ terminal: Terminal, didReportReaderEvent event: ReaderEvent, info: [AnyHashable: Any]?) {
        var logEvent = LogEvent(method: .reportReaderEvent)
        logEvent.result = .message(Terminal.stringFromReaderEvent(event))
        events.append(logEvent)
    }

    func terminal(_ terminal: Terminal, didReportUnexpectedReaderDisconnect reader: Reader) {
        var logEvent = LogEvent(method: .reportReaderEvent)
        logEvent.result = .message("Disconnected from reader: \(reader.serialNumber)")
        events.append(logEvent)
        presentAlert(title: "Reader disconnected!", message: "")
    }

    // MARK: ReaderDisplayDelegate
    func terminal(_ terminal: Terminal, didRequestReaderInput inputOptions: ReaderInputOptions) {
        var event = LogEvent(method: .requestReaderInput)
        event.result = .message(Terminal.stringFromReaderInputOptions(inputOptions))
        events.append(event)
    }

    func terminal(_ terminal: Terminal, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {
        var event = LogEvent(method: .requestReaderDisplayMessage)
        event.result = .message(Terminal.stringFromReaderDisplayMessage(displayMessage))
        events.append(event)
    }

}
