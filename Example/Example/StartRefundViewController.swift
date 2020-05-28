//
//  StartRefundViewController.swift
//  Example
//
//  Created by James Little on 11/5/19.
//  Copyright © 2019 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class StartRefundViewController: TableViewController {

    private let amountView = AmountInputView()
    private let chargeIdView = TextFieldView(text: "text", footer: "")
    private var startSection: Section?

    convenience init() {
        self.init(style: .grouped)
        amountView.numberFormatter.currencyCode = "CAD"
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "Collect refund"

        amountView.onAmountUpdated = { amountString in
            self.startSection?.header = Section.Extremity.title(amountString)
            self.updateContent()
        }
        let headerString: String
        headerString = "Refund a payment using a physical Interac test card. In-person refunds can only be processed if the payment method requires an in-person refund; if not, use the Stripe API."

        self.startSection = Section(header: Section.Extremity.title(self.amountView.amountString), rows: [
            Row(text: "Collect refund", selection: {
                self.startRefund()
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

    internal func startRefund() {
        let refundParams = RefundParameters(chargeId: chargeIdView.textField.text ?? "",
                                            amount: amountView.amount,
                                            currency: "cad")

        let vc = RefundViewController(refundParams: refundParams)
        let navController = LargeTitleNavigationController(rootViewController: vc)
        self.present(navController, animated: true, completion: nil)
    }

    private func updateContent() {
        let chargeIdSection = Section(header: "Charge ID", rows: [],
                                      footer: Section.Extremity.autoLayoutView(chargeIdView))

        let amountSection = Section(header: "Amount", rows: [],
                                    footer: Section.Extremity.autoLayoutView(amountView))


        var sections: [Section] = [
            chargeIdSection,
            amountSection,
        ]
        if let startSection = self.startSection {
            sections.append(startSection)
        }
        dataSource.sections = sections
    }
}
