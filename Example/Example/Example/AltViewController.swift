//
//  KeyedPaymentViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 2/14/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import StripePOS
import Stripe

class AltViewController: StackViewController, SCPReadCardDelegate {

    private let cardField = STPPaymentCardTextField()
    private weak var terminal: SCPTerminal?
    private var readSourceCancelable: SCPCancelable?

    init(terminal: SCPTerminal) {
        self.terminal = terminal
        super.init(nibName: nil, bundle: nil)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        title = "Alt"
        navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .done, target: self, action: #selector(doneAction))

        guard let terminal = self.terminal else { return }

        cardField.borderColor = UIColor.stripeLightGrey
        cardField.borderWidth = 1.0
        cardField.postalCodeEntryEnabled = false
        let params = STPCardParams()
        params.number = "4242424242424242";
        params.expMonth = 10;
        params.expYear = 29;
        params.cvc = "123";
        cardField.cardParams = params

        let keyInButton = ColoredButton(title: "Create Keyed Source", color: UIColor.stripeOrange) {
            terminal.createKeyedSource(withSTPPaymentCardTextField: self.cardField) {
                source, error in
                if let source = source {
                    let vc = TextViewController(object: source)
                    let navController = UINavigationController(rootViewController: vc)
                    navController.navigationBar.isTranslucent = false
                    self.present(navController, animated: true, completion: nil)
                }
                else if let error = error {
                    print("Create source failed: \(error)")
                    self.presentAlert(error: error)
                }
            }
        }

        let readButton = ColoredButton(title: "Read Source", color: UIColor.stripeGreen) {
            let params = SCPReadSourceParameters()
            self.readSourceCancelable = terminal.readSource(params, readCardDelegate: self) { source, error in
                if let source = source {
                    let vc = TextViewController(object: source)
                    let navController = UINavigationController(rootViewController: vc)
                    navController.navigationBar.isTranslucent = false
                    self.present(navController, animated: true, completion: nil)
                }
                else if let error = error {
                    print("Read source failed: \(error)")
                    self.presentAlert(error: error)
                }
            }
        }

        let cancelReadButton = ColoredButton(title: "Cancel Read Source", color: UIColor.stripeRed) {
            self.readSourceCancelable?.cancel() { error in
                if let error = error {
                    self.presentAlert(error: error)
                }
            }
        }

        stack = [
            [readButton],
            [cancelReadButton],
            [cardField],
            [keyInButton],
            [UIView()],
            [UIView()],
        ]
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        cardField.resignFirstResponder()
    }

    @objc private func doneAction() {
        dismiss(animated: true, completion: nil)
    }

    // MARK: SCPReadCardDelegate

    func terminal(_ terminal: SCPTerminal, didBeginWaitingForCard presentationType: SCPCardPresentationType) {
        showNotification(title: SCPTerminal.string(from: presentationType))
    }

    func terminal(terminal: SCPTerminal, didRequestReadCardPrompt prompt: SCPReadCardPrompt) {
        showNotification(title: SCPTerminal.string(from: prompt))
    }
}
