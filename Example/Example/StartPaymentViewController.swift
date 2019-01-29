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

    private let currencyView = CurrencyInputView()
    private let amountView = AmountInputView()
    private var startSection: Section?

    convenience init() {
        self.init(style: .grouped)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "Collect card payment"

        currencyView.initialize()
        currencyView.textField.isEnabled = false
        currencyView.textField.textColor = UIColor.gray
        amountView.onAmountUpdated = { amountString in
            self.startSection?.header = Section.Extremity.title(amountString)
            self.updateContent()
        }
        currencyView.onCurrencyUpdated = { currency in
            var localeInfo = [NSLocale.Key.currencyCode.rawValue: currency]
            if let language = Locale.preferredLanguages.first {
                localeInfo[NSLocale.Key.languageCode.rawValue] = language
            }
            let localeID = Locale.identifier(fromComponents: localeInfo)
            let locale = Locale(identifier: localeID)
            self.amountView.numberFormatter.locale = locale
            self.amountView.numberFormatter.currencyCode = currency
            self.startSection?.header = Section.Extremity.title(self.amountView.amountString)
            self.updateContent()
        }
        let headerString: String
        switch ReaderViewController.deviceType {
        case .chipper2X:
            headerString = "Collect a card payment using a physical Stripe test card and the Chipper 2X."
        case .readerSimulator:
            headerString = "Collect a card payment using a simulated reader."
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
                                                    currency: currencyView.currency)
        let vc = PaymentViewController(paymentParams: paymentParams)
        let navController = UINavigationController(rootViewController: vc)
        navController.navigationBar.isTranslucent = false
        if #available(iOS 11.0, *) {
            navController.navigationBar.prefersLargeTitles = true
        }
        self.present(navController, animated: true, completion: nil)
    }

    private func updateContent() {
        let amountSection = Section(header: "AMOUNT", rows: [],
                                    footer: Section.Extremity.autoLayoutView(amountView))
        let currencySection = Section(header: "CURRENCY", rows: [],
                                      footer: Section.Extremity.autoLayoutView(currencyView))
        var sections: [Section] = [
            amountSection,
            currencySection,
        ]
        if let startSection = self.startSection {
            sections.append(startSection)
        }
        dataSource.sections = sections
    }
}
