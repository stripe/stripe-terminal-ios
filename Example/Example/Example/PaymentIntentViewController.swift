//
//  TransactionResultViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/12/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit
import StripePOS

class PaymentIntentViewController: StackViewController {

    let statusView: StatusView<SCPPaymentIntentStatus>
    let intent: SCPPaymentIntent
    weak var terminal: SCPTerminal?

    init(intent: SCPPaymentIntent, terminal: SCPTerminal) {
        self.intent = intent
        self.terminal = terminal
        self.statusView = StatusView<SCPPaymentIntentStatus>(title: "Status", value: intent.status)
        super.init(nibName: nil, bundle: nil)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "Payment Intent"
        navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .done, target: self, action: #selector(doneAction))

        guard let terminal = self.terminal else { return }

        let statusView = StatusView<SCPPaymentIntentStatus>(title: "Status", value: intent.status)
        stackView.addArrangedSubview(statusView)
        switch intent.status {
        case .requiresSource,
             .canceled,
             .succeeded,
             .requiresConfirmation:
            for _ in 0..<4 {
                stackView.addArrangedSubview(UIView())
            }
            break;
        case .requiresCapture:
            let chargeButton = ColoredButton(title: "View Payment Intent", color: UIColor.stripeGreen) {
                let viewController = TextViewController(object: self.intent)
                self.navigationController?.pushViewController(viewController, animated: true)
            }
            stackView.addArrangedSubview(chargeButton)
            let cancelButton = ColoredButton(title: "Cancel Payment Intent", color: UIColor.stripeRed) {
                terminal.cancel(self.intent) { intent, error in
                    if let i = intent {
                        let viewController = PaymentIntentViewController(intent: i, terminal: terminal)
                        self.navigationController?.pushViewController(viewController, animated: true)
                    }
                    else if let e = error {
                        self.presentAlert(error: e)
                    }
                }
            }
            stackView.addArrangedSubview(cancelButton)
            break;
        }
    }

    @objc private func doneAction() {
        dismiss(animated: true, completion: nil)
    }
}

