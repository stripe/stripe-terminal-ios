//
//  CreateSourceViewController.swift
//  AppStore
//
//  Created by Ben Guo on 9/12/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class CreateSourceViewController: TableViewController, TerminalDelegate, ReaderInputDelegate {

    private let headerView = ReaderHeaderView()
    private let logHeaderView = ActivityIndicatorHeaderView(title: "EVENT LOG")
    private weak var cancelButton: UIBarButtonItem?
    private weak var doneButton: UIBarButtonItem?
    private var completed = false

    private let terminal: Terminal
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

    init(terminal: Terminal) {
        self.terminal = terminal
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

        terminal.terminalDelegate = self
        if completed || terminal.paymentStatus != .ready {
            return
        }

        headerView.connectedReader = terminal.connectedReader
        headerView.connectionStatus = terminal.connectionStatus
        updateContent()

        let params = ReadSourceParameters()
        var readEvent = LogEvent(method: .readSource)
        self.events.append(readEvent)
        self.collectPaymentMethodCancelable = self.terminal.readSource(params, delegate: self) { source, error in
            self.collectPaymentMethodCancelable = nil
            if let error = error {
                readEvent.result = .errored
                readEvent.object = error
            }
            else if let source = source {
                readEvent.result = .succeeded
                readEvent.object = source
            }
            self.events.append(readEvent)
            self.complete()
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
        collectPaymentMethodCancelable?.cancel { error in
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
        event.result = .message(Terminal.stringFromReaderInputOptions(inputOptions))
        events.append(event)
    }

    func terminal(terminal: Terminal, didRequestReaderInputPrompt inputPrompt: ReaderInputPrompt) {
        var event = LogEvent(method: .readSourcePrompt)
        event.result = .message(Terminal.stringFromReaderInputPrompt(inputPrompt))
        events.append(event)
    }

}

