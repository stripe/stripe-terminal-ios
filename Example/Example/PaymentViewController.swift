//
//  PaymentViewController.swift
//  Example
//
//  Created by Ben Guo on 9/6/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class PaymentViewController: TableViewController, TerminalDelegate, ReaderInputDelegate {

    private let paymentParams: PaymentIntentParameters

    private let headerView = ReaderHeaderView()
    private let logHeaderView = ActivityIndicatorHeaderView(title: "EVENT LOG")
    private weak var cancelButton: UIBarButtonItem?
    private weak var doneButton: UIBarButtonItem?
    private var completed = false

    private var cancelable: Cancelable? = nil {
        didSet {
            cancelButton?.isEnabled = (cancelable != nil)
        }
    }
    private var events: [LogEvent] = [] {
        didSet {
            updateContent()
        }
    }

    init(paymentParams: PaymentIntentParameters) {
        self.paymentParams = paymentParams
        super.init(style: .grouped)
        self.title = "Testing"
        tableView.separatorInset = .zero
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        let doneButton = UIBarButtonItem(barButtonSystemItem: .done, target: self, action: #selector(doneAction))
        doneButton.isEnabled = false
        self.doneButton = doneButton
        let cancelButton = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(cancelAction))
        cancelButton.isEnabled = false
        self.cancelButton = cancelButton
        navigationItem.leftBarButtonItem = cancelButton
        navigationItem.rightBarButtonItem = doneButton

        guard let apiClient = RootViewController.apiClient else {
                return
        }
        Terminal.shared.delegate = self
        if completed || Terminal.shared.paymentStatus != .ready {
            return
        }

        headerView.connectedReader = Terminal.shared.connectedReader
        headerView.connectionStatus = Terminal.shared.connectionStatus
        updateContent()

        // 1. create PaymentIntent
        var createEvent = LogEvent(method: .createPaymentIntent)
        self.events.append(createEvent)
        Terminal.shared.createPaymentIntent(self.paymentParams) { intent, createError in
            if let error = createError {
                createEvent.result = .errored
                createEvent.object = error
                self.events.append(createEvent)
                self.complete()
            }
            else if let intent = intent {
                createEvent.result = .succeeded
                createEvent.object = intent
                self.events.append(createEvent)

                // 2. collectPaymentMethod
                var collectEvent = LogEvent(method: .collectPaymentMethod)
                self.events.append(collectEvent)
                self.cancelable = Terminal.shared.collectPaymentMethod(intent, delegate: self) { intentWithSource, attachError in
                    self.cancelable = nil
                    if let error = attachError {
                        collectEvent.result = .errored
                        collectEvent.object = error
                        self.events.append(collectEvent)
                        self.complete()
                    }
                    else if let intent = intentWithSource {
                        collectEvent.result = .succeeded
                        collectEvent.object = intent
                        self.events.append(collectEvent)

                        // 3. confirm PaymentIntent
                        var confirmEvent = LogEvent(method: .confirmPaymentIntent)
                        self.events.append(confirmEvent)
                        Terminal.shared.confirmPaymentIntent(intent) { confirmedIntent, confirmError in
                            if let error = confirmError {
                                confirmEvent.result = .errored
                                confirmEvent.object = error
                                self.events.append(confirmEvent)
                                self.complete()
                            }
                            else if let intent = confirmedIntent {
                                confirmEvent.result = .succeeded
                                confirmEvent.object = intent
                                self.events.append(confirmEvent)

                                // 4. send to backend for capture
                                var captureEvent = LogEvent(method: .capturePaymentIntent)
                                self.events.append(captureEvent)
                                apiClient.capturePaymentIntent(intent.stripeId) { captureError in
                                    if let error = captureError {
                                        captureEvent.result = .errored
                                        captureEvent.object = error
                                    }
                                    else {
                                        captureEvent.result = .succeeded
                                    }
                                    self.events.append(captureEvent)
                                    self.complete()
                                }
                            }

                        }
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
                        }, accessory: .disclosureIndicator,
                           cellClass: LogEventCell.self)
                }
            })
        ]
    }

    @objc func doneAction() {
        dismiss(animated: true, completion: nil)
    }

    @objc func cancelAction() {
        // cancel collectPaymentMethod
        var event = LogEvent(method: .cancelCollectPaymentMethod)
        self.events.append(event)
        cancelable?.cancel { error in
            if let error = error {
                event.result = .errored
                event.object = error
            }
            else {
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

    func terminal(_ terminal: Terminal, didReportReaderEvent event: ReaderEvent, info: [AnyHashable : Any]?) {
        var logEvent = LogEvent(method: .readerEvent)
        logEvent.result = .message(Terminal.stringFromReaderEvent(event))
        events.append(logEvent)
    }

    // MARK: ReaderInputDelegate
    func terminal(_ terminal: Terminal, didBeginWaitingForReaderInput inputOptions: ReaderInputOptions) {
        var event = LogEvent(method: .waitingForReaderInput)
        event.result = .message(Terminal.stringFromReaderInputOptions(inputOptions))
        events.append(event)
    }

    func terminal(_ terminal: Terminal, didRequestReaderInputPrompt inputPrompt: ReaderInputPrompt) {
        var event = LogEvent(method: .readSourcePrompt)
        event.result = .message(Terminal.stringFromReaderInputPrompt(inputPrompt))
        events.append(event)
    }

}
