//
//  PaymentLogViewController.swift
//  Example
//
//  Created by Ben Guo on 9/6/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class PaymentViewController: TableViewController, TerminalDelegate, ReaderInputDelegate {

    private let terminal: Terminal
    private let paymentParams: PaymentIntentParameters

    private let headerView = ReaderHeaderView()
    private let logHeaderView = ActivityIndicatorHeaderView(title: "EVENT LOG")
    private weak var cancelButton: UIBarButtonItem?
    private weak var doneButton: UIBarButtonItem?
    private var completed = false

    private var collectPaymentMethodCancelable: Cancelable? = nil {
        didSet {
            cancelButton?.isEnabled = (collectPaymentMethodCancelable != nil)
        }
    }
    private var events: [LogEvent] = [] {
        didSet {
            updateContent()
        }
    }

    init(terminal: Terminal, paymentParams: PaymentIntentParameters) {
        self.terminal = terminal
        self.paymentParams = paymentParams
        super.init(style: .grouped)
        self.title = "Testing"
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
        updateContent()

        if let terminal = RootViewController.terminal {
            headerView.connectedReader = terminal.connectedReader
            headerView.connectionStatus = terminal.connectionStatus
        }
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        guard let terminal = RootViewController.terminal,
            let apiClient = RootViewController.apiClient else {
                return
        }
        terminal.terminalDelegate = self
        if completed || terminal.paymentStatus != .ready {
            return
        }

        // 1. create PaymentIntent
        self.terminal.createPaymentIntent(self.paymentParams) { intent, createError in
            var createEvent = LogEvent(method: .createPaymentIntent)
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
                self.collectPaymentMethodCancelable = self.terminal.collectPaymentMethod(intent, delegate: self) { intentWithSource, attachError in
                    var collectEvent = LogEvent(method: .collectPaymentMethod)
                    self.collectPaymentMethodCancelable = nil
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
                        self.terminal.confirmPaymentIntent(intent) { confirmedIntent, confirmError in
                            var confirmEvent = LogEvent(method: .confirmPaymentIntent)
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
                return Row(text: event.description, detailText: event.method.rawValue, selection: { [unowned self] in
                    let vc = LogEventViewController(event: event)
                    self.navigationController?.pushViewController(vc, animated: true)
                    }, accessory: .disclosureIndicator,
                       cellClass: LogEventCell.self)
            })
        ]
    }

    @objc func doneAction() {
        dismiss(animated: true, completion: nil)
    }

    @objc func cancelAction() {
        // cancel collectPaymentMethod
        collectPaymentMethodCancelable?.cancel { error in
            var event = LogEvent(method: .cancelCollectPaymentMethod)
            if let error = error {
                event.result = .errored
                event.object = error
            }
            else {
                event.result = .succeeded
            }
            self.events.append(event)
        }
    }

    // MARK: TerminalDelegate

    func terminal(_ terminal: Terminal, didChangeConnectionStatus status: ConnectionStatus) {
        headerView.connectionStatus = status
    }

    // MARK: ReadCardDelegate
    func terminal(_ terminal: Terminal, didBeginWaitingForReaderInput inputOptions: ReaderInputOptions) {
        var event = LogEvent(method: .waitingForReaderInput)
        event.result = .message(Terminal.string(from: inputOptions))
        events.append(event)
    }

    func terminal(terminal: Terminal, didRequestReaderInputPrompt inputPrompt: ReaderInputPrompt) {
        var event = LogEvent(method: .readSourcePrompt)
        event.result = .message(Terminal.string(from: inputPrompt))
        events.append(event)
    }

}
