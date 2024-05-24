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
    private var enableCustomerCancellation: Bool = false
    private let isSposReader: Bool
    private var refundWithChargeId: Bool = true
    private var chargeId: String = ""
    private var paymentIntentId: String = ""

    private let amountView = AmountInputView()
    private let paymentOrChargeIdView = TextFieldView(text: "text", footer: "")
    private var startSection: Section?

    init(isSposReader: Bool, chargeId: String = "", paymentIntentId: String = "", amount: UInt = 100) {
        self.isSposReader = isSposReader
        super.init(style: .grouped)
        self.chargeId = chargeId
        self.paymentIntentId = paymentIntentId
        amountView.numberFormatter.currencyCode = "CAD"
        amountView.textField.text = String(amount)
        paymentOrChargeIdView.textField.text = chargeId
        self.refundWithChargeId = true
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()
        title = "Collect refund"

        paymentOrChargeIdView.textField.autocorrectionType = .no
        paymentOrChargeIdView.textField.autocapitalizationType = .none
        paymentOrChargeIdView.textField.delegate = self
        paymentOrChargeIdView.textField.clearButtonMode = .whileEditing

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
        let refundParamsBuilder: RefundParametersBuilder
        if self.refundWithChargeId == true {
            refundParamsBuilder = RefundParametersBuilder(chargeId: paymentOrChargeIdView.textField.text ?? "",
                                                            amount: amountView.amount,
                                                          currency: "cad")
        } else {
            refundParamsBuilder = RefundParametersBuilder(paymentIntentId: paymentOrChargeIdView.textField.text ?? "",
                                                                   amount: amountView.amount,
                                                                 currency: "cad")
        }

        if let refundApplicationFee = refundApplicationFee {
            refundParamsBuilder.setRefundApplicationFee(refundApplicationFee)
        }

        if let reverseTransfer = reverseTransfer {
            refundParamsBuilder.setReverseTransfer(reverseTransfer)
        }

        do {
            let refundParams = try refundParamsBuilder.build()
            let refundConfig = try RefundConfigurationBuilder()
                .setEnableCustomerCancellation(enableCustomerCancellation)
                .build()
            let vc = RefundViewController(refundParams: refundParams, refundConfig: refundConfig)
            let navController = LargeTitleNavigationController(rootViewController: vc)
            self.present(navController, animated: true, completion: nil)
        } catch {
            self.presentAlert(error: error)
        }
    }

    private func updateContent() {
        let amountSection = Section(header: "Amount", rows: [],
                                    footer: Section.Extremity.autoLayoutView(amountView))

        let shouldShowTestCardPickerView = Terminal.shared.connectedReader?.simulated == true &&
            [DeviceType.stripeM2, DeviceType.chipper2X, DeviceType.wisePad3].contains(Terminal.shared.connectedReader?.deviceType)

        let paymentMethodSection = Section(header: Section.Extremity.title("Payment Method"), rows: [],
                                           footer: Section.Extremity.autoLayoutView(TestCardPickerView()))

        var sections: [Section] = [
            makeIdLabelSection(),
            amountSection,
            makeTransactionSection(),
            makeRefundApplicationFeeSection(),
            makeReverseTransferSection(),
            shouldShowTestCardPickerView ? paymentMethodSection : nil
        ].compactMap { $0 }

        if let startSection = self.startSection {
            sections.append(startSection)
        }

        dataSource.sections = sections
    }

    func makeIdLabelSection() -> Section {
        var selectedIndex: Int
        if self.refundWithChargeId == true {
            selectedIndex = 0
        } else {
            selectedIndex = 1
        }
        let rows: [Row] = [
            Row(text: "Value",
                accessory: .segmentedControl(
                    items: ["charge id", "payment intent id"],
                    selectedIndex: selectedIndex) { [unowned self] newIndex, _ in
                        switch newIndex {
                        case 0: self.refundWithChargeId = true
                        case 1: self.refundWithChargeId = false
                        default:
                            self.refundWithChargeId = true
                        }
                        // copy text from the payment/charge id view into a temp string
                        let tempId: String = paymentOrChargeIdView.textField.text ?? ""
                        if newIndex != selectedIndex {
                            // when change to index occurs
                            if self.refundWithChargeId {
                                // update the payment or charge id view with the stored chargeid, and save the temp value to the
                                paymentOrChargeIdView.textField.text = self.chargeId
                                self.paymentIntentId = tempId
                            } else {
                                // update the payment or charge id view ith the stored payment id
                                paymentOrChargeIdView.textField.text = self.paymentIntentId
                                self.chargeId = tempId
                            }
                        }
                        self.updateContent()
                    }
               )
        ]

        return Section(header: "REFUND ID", rows: rows, footer: Section.Extremity.autoLayoutView(paymentOrChargeIdView))
    }

    private func makeTransactionSection() -> Section? {
        if self.isSposReader {
            return Section(
                header: "TRANSACTION FEATURES",
                rows: [Row(text: "Customer cancellation", accessory: .switchToggle(value: self.enableCustomerCancellation) { [unowned self] _ in
                    self.enableCustomerCancellation.toggle()
                    self.updateContent()
                })])
        } else {
            return nil
        }
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
