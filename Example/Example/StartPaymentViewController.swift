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
    
    struct Amount {
        var amountString: String
        var currencyString: String
        
        var display: String {
            return "\(amountString) \(currencyString)"
        }
    }

    private let amountView = AmountInputView()
    private let currencyView = CurrencyInputView()
    private var startSection: Section?
    private var amount = Amount(amountString: "$1.00", currencyString: "USD")

    convenience init() {
        self.init(style: .grouped)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "Collect card payment"

        amountView.onAmountUpdated = { amountString in
            self.amount.amountString = amountString
            self.startSection?.header = Section.Extremity.title(self.amount.display)
            self.updateContent()
        }
        
        currencyView.onCurrencyUpdated = { currencyString in
            self.amount.currencyString = currencyString
            self.startSection?.header = Section.Extremity.title(self.amount.display)
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
                headerString = "Collect a card payment using a physical stripe test card and the WisePad 3."
            @unknown default:
                headerString = "Collect a card payment using a physical Stripe test card and reader."
            }
        }
        self.startSection = Section(header: Section.Extremity.title(self.amount.display), rows: [
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
        let navController = LargeTitleNavigationController(rootViewController: vc)
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
