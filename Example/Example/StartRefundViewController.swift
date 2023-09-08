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

    private var refundApplicationFee: Bool?
    private var reverseTransfer: Bool?

    private let amountView = AmountInputView()
    private let chargeIdView = TextFieldView(text: "text", footer: "")
    private var startSection: Section?

    convenience init(chargeId: String = "", amount: UInt = 100) {
        self.init(style: .grouped)
        amountView.numberFormatter.currencyCode = "CAD"
        amountView.textField.text = String(amount)
        chargeIdView.textField.text = chargeId
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()
        title = "Collect refund"

        chargeIdView.textField.autocorrectionType = .no
        chargeIdView.textField.autocapitalizationType = .none
        chargeIdView.textField.delegate = self
        chargeIdView.textField.clearButtonMode = .whileEditing

        amountView.onAmountUpdated = { [unowned self] amountString in
            self.startSection?.header = Section.Extremity.title(amountString)
            self.updateContent()
        }
        let headerString: String
        headerString = "Refund a payment using a physical Interac test card. In-person refunds can only be processed if the payment method requires an in-person refund; if not, use the Stripe API."

        self.startSection = Section(header: Section.Extremity.title(self.amountView.amountString), rows: [
            Row(text: "Collect refund", selection: { [unowned self] in
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
    }

    internal func startRefund() {
        let refundParamsBuilder = RefundParametersBuilder(chargeId: chargeIdView.textField.text ?? "",
            amount: amountView.amount,
            currency: "cad")

        if let refundApplicationFee = refundApplicationFee {
            refundParamsBuilder.setRefundApplicationFee(refundApplicationFee)
        }

        if let reverseTransfer = reverseTransfer {
            refundParamsBuilder.setReverseTransfer(reverseTransfer)
        }

        do {
            let refundParams = try refundParamsBuilder.build()
            let vc = RefundViewController(refundParams: refundParams)
            let navController = LargeTitleNavigationController(rootViewController: vc)
            self.present(navController, animated: true, completion: nil)
        } catch {
            self.presentAlert(error: error)
        }
    }

    private func updateContent() {
        let chargeIdSection = Section(header: "Charge ID", rows: [],
                                      footer: Section.Extremity.autoLayoutView(chargeIdView))

        let amountSection = Section(header: "Amount", rows: [],
                                    footer: Section.Extremity.autoLayoutView(amountView))

        let shouldShowTestCardPickerView = Terminal.shared.connectedReader?.simulated == true &&
            [DeviceType.stripeM2, DeviceType.chipper2X, DeviceType.wisePad3].contains(Terminal.shared.connectedReader?.deviceType)

        let paymentMethodSection = Section(header: Section.Extremity.title("Payment Method"), rows: [],
                                           footer: Section.Extremity.autoLayoutView(TestCardPickerView()))


        var sections: [Section] = [
            chargeIdSection,
            amountSection,
            makeRefundApplicationFeeSection(),
            makeReverseTransferSection(),
            shouldShowTestCardPickerView ? paymentMethodSection : nil
        ].compactMap { $0 }

        if let startSection = self.startSection {
            sections.append(startSection)
        }

        dataSource.sections = sections
    }

    func makeRefundApplicationFeeSection() -> Section {
        let rows: [Row] = [
            Row(text: "Value",
                accessory: .segmentedControl(
                    items: ["default", "true", "false"],
                    selectedIndex: 0) { [unowned self] newIndex, _ in
                        switch newIndex {
                        case 0: self.refundApplicationFee = nil
                        case 1: self.refundApplicationFee = true
                        case 2: self.refundApplicationFee = false
                        default:
                            fatalError("Unknown option selected")
                        }
                    }
               )
        ]

        return Section(header: "REFUND APPLICATION FEE", rows: rows)
    }

    func makeReverseTransferSection() -> Section {
        let rows: [Row] = [
            Row(text: "Value",
                accessory: .segmentedControl(
                    items: ["default", "true", "false"],
                    selectedIndex: 0) { [unowned self] newIndex, _ in
                        switch newIndex {
                        case 0: self.reverseTransfer = nil
                        case 1: self.reverseTransfer = true
                        case 2: self.reverseTransfer = false
                        default:
                            fatalError("Unknown option selected")
                        }
                    }
               )
        ]

        return Section(header: "REVERSE TRANSFER", rows: rows)
    }
}

extension StartRefundViewController: UITextFieldDelegate {
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
}
