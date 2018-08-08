//
//  PaymentViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/7/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit
import StripePOS

class PaymentViewController: StackViewController, SCPReadCardDelegate, SCPTerminalDelegate {

    weak var terminal: SCPTerminal?
    weak var apiClient: APIClient?

    private var intent: SCPPaymentIntent? {
        didSet {
            updateButtons()
        }
    }
    private let amountControl = ValueControl<UInt>(title: "Amount (Cents)", value: 100)
    private let currencyControl = ValueControl(title: "Currency",
                                               value: "usd",
                                               options: ["usd", "gbp", "jpy"])
    private let paymentStatusView = StatusView<SCPPaymentStatus>(title: "Payment Status",
                                                                 value: .notReady)
    private let startButton = ColoredButton(title: "Start", color: UIColor.stripeGreen)
    private let cancelButton = ColoredButton(title: "Cancel", color: UIColor.stripeRed)
    private weak var attachSourceCancelable: SCPCancelable?

    override func viewDidLoad() {
        super.viewDidLoad()

        startButton.onTap =  {
            guard let terminal = self.terminal else { return }
            if let intent = self.intent {
                if intent.status == .requiresSource {
                    self.attachSourceAndConfirm(intent: intent)
                }
                else if intent.status == .requiresConfirmation {
                    self.confirm(intent: intent)
                }
            }
            else {
                let params = SCPPaymentParameters(amount: self.amountControl.value,
                                                  currency: self.currencyControl.value)
                terminal.createPaymentIntent(params) { intent, error in
                    if let intent = intent {
                        self.attachSourceAndConfirm(intent: intent)
                    }
                    else if let error = error {
                        self.presentAlert(error: error)
                    }
                }
            }
        }
        cancelButton.onTap = {
            self.attachSourceCancelable?.cancel() { [weak self] canceled in
                if !canceled {
                    self?.presentAlert(title: "Error", message: "Cancel failed")
                }
            }
        }
        let altButton = ColoredButton(title: "Alt", color: UIColor.stripeOrange) {
            guard let terminal = self.terminal else { return }
            let altVC = AltViewController(terminal: terminal)
            let navController = UINavigationController(rootViewController: altVC)
            navController.navigationBar.isTranslucent = false
            self.present(navController, animated: true, completion: nil)
        }
        
        stack = [
            [amountControl, currencyControl],
            [paymentStatusView],
            [startButton],
            [cancelButton, altButton],
        ]
    }

    func attachSourceAndConfirm(intent: SCPPaymentIntent) {
        guard let terminal = self.terminal else { return }
        self.intent = intent
        self.attachSourceCancelable = terminal.attachSource(intent, readCardDelegate: self) { newIntent, error in
            if let newIntent = newIntent {
                self.intent = newIntent
                self.confirm(intent: newIntent)
            }
            else if let error = error {
                print("Attach source failed: \(error)")
                self.presentAlert(error: error)
            }
        }
        updateButtons()
    }

    func confirm(intent: SCPPaymentIntent) {
        guard let terminal = self.terminal else { return }
        self.intent = intent
        terminal.confirmPaymentIntent(intent) { confirmedIntent, error in
            if let confirmedIntent = confirmedIntent {
                print("Confirm succeeded, created payment intent: \(intent.stripeId)")
                print("You must send this ID to your backend to capture the payment intent.")
                let vc = PaymentIntentViewController(intent: confirmedIntent,
                                                     terminal: terminal)
                let navController = UINavigationController(rootViewController: vc)
                navController.navigationBar.isTranslucent = false
                self.present(navController, animated: true, completion: nil)
                self.intent = nil
            }
            else if let error = error {
                print("Confirm failed: \(error)")
                self.intent = error.paymentIntent
                self.presentAlert(title: "Confirm failed", message: error.reason)
            }
        }
    }

    func updateButtons() {
        guard let terminal = self.terminal else {
            return
        }
        if let cancelable = self.attachSourceCancelable {
            self.cancelButton.isEnabled = !cancelable.completed
        }
        else {
            self.cancelButton.isEnabled = false
        }
        guard let intent = self.intent else {
            startButton.isEnabled = true
            amountControl.isEnabled = true
            currencyControl.isEnabled = true
            startButton.setTitle("Start", for: .normal)
            return
        }
        startButton.isEnabled = true
        amountControl.isEnabled = false
        currencyControl.isEnabled = false
        switch terminal.paymentStatus {
        case .notReady:
            startButton.isEnabled = false
            startButton.setTitle("Start", for: .normal)
            break
        case .attachingSource, .confirmingPaymentIntent:
            startButton.isEnabled = false
            startButton.setTitle("Processing", for: .normal)
            break
        case .ready:
            startButton.isEnabled = true
            cancelButton.isEnabled = false
            switch intent.status {
            case .requiresSource:
                startButton.setTitle("Start", for: .normal)
                break;
            case .requiresConfirmation:
                startButton.setTitle("Retry Processing", for: .normal)
                break
            case .requiresCapture,
                 .canceled,
                 .succeeded:
                startButton.setTitle("Done", for: .normal)
                break
            }
            break
        }
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        self.terminal?.terminalDelegate = self
        paymentStatusView.value = terminal?.paymentStatus
        intent = nil
        updateButtons()
    }

    // MARK: SCPReadCardDelegate

    func terminal(_ terminal: SCPTerminal, didBeginWaitingForCard presentationType: SCPCardPresentationType) {
        showNotification(title: SCPTerminal.string(from: presentationType))
    }
    
    func terminal(terminal: SCPTerminal, didRequestReadCardPrompt prompt: SCPReadCardPrompt) {
        showNotification(title: SCPTerminal.string(from: prompt))
    }

    // MARK: SCPTerminalDelegate

    func terminal(_ terminal: SCPTerminal, didChange status: SCPPaymentStatus) {
        paymentStatusView.value = status
        updateButtons()
    }

}
