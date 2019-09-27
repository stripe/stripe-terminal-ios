//
//  StartPaymentViewController.swift
//  Example
//
//  Created by Ben Guo on 9/6/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class StartPaymentViewController: TableViewController {

    private let amountView = AmountInputView()
    private var startSection: Section?

    convenience init() {
        self.init(style: .grouped)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "Collect card payment"

        amountView.onAmountUpdated = { amountString in
            self.startSection?.header = Section.Extremity.title(amountString)
            self.updateContent()
        }
        let headerString: String
        if ReaderViewController.simulated {
            headerString = "Collect a card payment using a simulated reader."
        }
        else {
            switch ReaderViewController.deviceType {
            case .chipper2X:
                headerString = "Collect a card payment using a physical Stripe test card and the Chipper 2X."
            @unknown default:
                headerString = "Collect a card payment using a physical Stripe test card and reader."
            }
        }
        self.startSection = Section(header: "$1.00", rows: [
            Row(text: "Collect payment", selection: { [unowned self] in
                self.startPayment()
                }, cellClass: ButtonCell.self),
            ], footer: Section.Extremity.title(headerString))
        updateContent()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        // pop if no reader is connected
        guard Terminal.shared.connectedReader != nil else {
            navigationController?.popViewController(animated: true)
            return
        }
        amountView.textField.becomeFirstResponder()
    }

    internal func startPayment() {
        let paymentParams = PaymentIntentParameters(amount: amountView.amount,
                                                    currency: "usd")
        let vc = PaymentViewController(paymentParams: paymentParams)
        let navController = LargeTitleNavigationController(rootViewController: vc)
        self.present(navController, animated: true, completion: nil)
    }

    private func updateContent() {
        let amountSection = Section(header: "AMOUNT", rows: [],
                                    footer: Section.Extremity.autoLayoutView(amountView))
        var sections: [Section] = [
            amountSection,
        ]
        if let startSection = self.startSection {
            sections.append(startSection)
        }
        dataSource.sections = sections
    }
}
