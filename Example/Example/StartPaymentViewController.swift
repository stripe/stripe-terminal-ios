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

class StartPaymentViewController: TableViewController, CancelingViewController {

    private let amountView = AmountInputView()
    private let currencyView = CurrencyInputView()
    private var startSection: Section?

    convenience init() {
        self.init(style: .grouped)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()

        title = "Collect card payment"

        amountView.onAmountUpdated = { amountString in
            self.startSection?.header = Section.Extremity.title(amountString)
            self.updateContent()
        }

        currencyView.onCurrencyUpdated = { currencyString in
            self.amountView.numberFormatter.currencyCode = currencyString
            self.startSection?.header = Section.Extremity.title(self.amountView.amountString)
            self.updateContent()
        }

        let headerString: String
        if ReaderViewController.readerConfiguration.simulated {
            headerString = "Collect a card payment using a simulated reader."
        } else {
            switch ReaderViewController.readerConfiguration.deviceType {
            case .chipper2X:
                headerString = "Collect a card payment using a physical Stripe test card and the Chipper 2X."
            case .verifoneP400:
                headerString = "Collect a card payment using a physical Stripe test card and the Verifone P400."
            case .wisePad3:
                headerString = "Collect a card payment using a physical Stripe test card and the WisePad 3."
            @unknown default:
                headerString = "Collect a card payment using a physical Stripe test card and reader."
            }
        }
        self.startSection = Section(header: Section.Extremity.title(self.amountView.amountString), rows: [
            Row(text: "Collect payment", selection: { [unowned self] in
                self.startPayment()
                }, cellClass: ButtonCell.self)
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

    // MARK: - UIAdaptivePresentationControllerDelegate

    // See comment in `CancelingViewController` for why we're canceling during `ShouldDismiss` instead of `DidDismiss`
    func presentationControllerShouldDismiss(_ presentationController: UIPresentationController) -> Bool {
        performCancel(presentationController: presentationController)
        return true
    }

    // MARK: - Internal

    internal func startPayment() {
        let paymentParams = PaymentIntentParameters(amount: amountView.amount,
                                                    currency: currencyView.currency)
        let vc = PaymentViewController(paymentParams: paymentParams)
        let navController = LargeTitleNavigationController(rootViewController: vc)
        navController.presentationController?.delegate = self
        self.present(navController, animated: true, completion: nil)
    }

    private func updateContent() {
        let amountSection = Section(header: "AMOUNT", rows: [],
                                    footer: Section.Extremity.autoLayoutView(amountView))

        let currencySection = Section(header: "CURRENCY", rows: [],
                                      footer: Section.Extremity.autoLayoutView(currencyView))

        var sections: [Section] = [
            amountSection,
            currencySection
        ]

        if let startSection = self.startSection {
            sections.append(startSection)
        }

        dataSource.sections = sections
    }
}
