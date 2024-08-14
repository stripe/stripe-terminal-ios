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
    private var skipTipping = false
    private var interacPresentEnabled = false
    private var automaticCaptureEnabled = false
    private var manualPreferredEnabled = false
    private var setupFutureUsage: String?
    private var requestedPriority: String?
    private var requestExtendedAuthorization = false
    private var requestIncrementalAuthorizationSupport = false
    private var declineCardBrand: CardBrand?
    private var recollectAfterCardBrandDecline = false

    private var connectedAccountId: String {
        connectedAccountTextField.textField.text ?? ""
    }

    private var applicationFeeAmount: NSNumber {
        NSNumber(value: (Double(applicationFeeAmountTextField.textField.text ?? "0") ?? 0))
    }

    private let connectedAccountTextField = TextFieldView(
        placeholderText: "Connected Stripe Account ID")

    private let applicationFeeAmountTextField = TextFieldView(placeholderText: "Application Fee Amount")


    private lazy var tipEligibleAmountTextField: AmountInputView = {
        let textField = AmountInputView(footer: "Must have on-reader tipping configured to have any effect.", placeholderText: "Tip-eligible amount")
        textField.textField.text = nil
        textField.textField.clearButtonMode = .whileEditing
        textField.textField.keyboardType = .numbersAndPunctuation
        return textField
    }()

    private lazy var simulatedTipAmountTextField: AmountInputView = {
        let textField = AmountInputView(placeholderText: "Simulated tip amount")
        textField.textField.text = nil
        textField.textField.clearButtonMode = .whileEditing
        textField.textField.keyboardType = .numberPad
        return textField
    }()

    convenience init() {
        self.init(style: .grouped)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()

        title = "Collect card payment"

        connectedAccountTextField.textField.autocorrectionType = .no
        connectedAccountTextField.textField.autocapitalizationType = .none
        connectedAccountTextField.textField.delegate = self
        connectedAccountTextField.textField.clearButtonMode = .whileEditing

        applicationFeeAmountTextField.textField.autocorrectionType = .no
        applicationFeeAmountTextField.textField.autocapitalizationType = .none
        applicationFeeAmountTextField.textField.delegate = self
        applicationFeeAmountTextField.textField.clearButtonMode = .whileEditing
        applicationFeeAmountTextField.textField.keyboardType = .numberPad


        amountView.onAmountUpdated = { [unowned self] amountString in
            self.startSection?.header = Section.Extremity.title(amountString)
            self.updateContent()
        }

        currencyView.onCurrencyUpdated = { [unowned self] currencyString in
            self.amountView.numberFormatter.currencyCode = currencyString
            self.startSection?.header = Section.Extremity.title(self.amountView.amountString)
            self.updateContent()
        }

        let headerString: String
        if ReaderViewController.readerConfiguration.simulated {
            headerString = "Collect a card payment using a simulated reader."
        } else {
            let readerString: String = {
                if let reader = Terminal.shared.connectedReader {
                    return "the \(Terminal.stringFromDeviceType(reader.deviceType))"
                } else {
                    return "reader"
                }
            }()
            headerString = "Collect a card payment using a physical Stripe test card and \(readerString)"
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
    }

    // MARK: - UIAdaptivePresentationControllerDelegate

    func presentationControllerDidDismiss(_ presentationController: UIPresentationController) {
        performCancel(presentationController: presentationController)
    }

    // MARK: - Internal

    internal func startPayment() {
        let captureMethod = self.automaticCaptureEnabled ? CaptureMethod.automatic : CaptureMethod.manual
        var paymentMethodTypes = ["card_present"]

        if self.interacPresentEnabled {
            paymentMethodTypes.append("interac_present")
        }

        let paymentParams = PaymentIntentParameters(amount: amountView.amount,
                                                    currency: currencyView.currency,
                                                    paymentMethodTypes: paymentMethodTypes,
                                                    captureMethod: captureMethod)

        paymentParams.setupFutureUsage = self.setupFutureUsage

        paymentParams.paymentMethodOptionsParameters = makePaymentMethodOptionsParameters()

        // Set up destination payment
        if !connectedAccountId.isEmpty {
            paymentParams.transferDataDestination = connectedAccountId
            paymentParams.onBehalfOf = connectedAccountId
        }

        if applicationFeeAmount != 0 {
            paymentParams.applicationFeeAmount = applicationFeeAmount
        }

        Terminal.shared.simulatorConfiguration.simulatedTipAmount = NSNumber(value: simulatedTipAmountTextField.amount)

        let collectConfig = CollectConfiguration(skipTipping: self.skipTipping, updatePaymentIntent: declineCardBrand != nil)
        if let eligibleAmount = Int(tipEligibleAmountTextField.textField.text ?? "none") {
            let tippingConfig = TippingConfiguration(eligibleAmount: eligibleAmount)
            collectConfig.tippingConfiguration = tippingConfig
        }
        let vc = PaymentViewController(paymentParams: paymentParams,
                                       collectConfig: collectConfig,
                                       declineCardBrand: declineCardBrand,
                                       recollectAfterCardBrandDecline: recollectAfterCardBrandDecline
        )
        let navController = LargeTitleNavigationController(rootViewController: vc)
        navController.presentationController?.delegate = self
        self.present(navController, animated: true, completion: nil)
    }

    private func makePaymentMethodOptionsParameters() -> PaymentMethodOptionsParameters {
        let cardPresentParams: CardPresentParameters = CardPresentParameters(
            requestExtendedAuthorization: self.requestExtendedAuthorization,
            requestIncrementalAuthorizationSupport: self.requestIncrementalAuthorizationSupport)

        if self.manualPreferredEnabled {
            cardPresentParams.captureMethod = NSNumber(value: CardPresentCaptureMethod.manualPreferred.rawValue)
        }

        if requestedPriority == "Domestic" {
            cardPresentParams.requestedPriority = NSNumber(value: CardPresentRouting.domestic.rawValue)
        }

        if requestedPriority == "International" {
            cardPresentParams.requestedPriority = NSNumber(value: CardPresentRouting.international.rawValue)
        }

        return PaymentMethodOptionsParameters(cardPresentParameters: cardPresentParams)
    }

    private func makeAmountSection() -> Section {
        Section(
            header: "AMOUNT",
            rows: [],
            footer: Section.Extremity.autoLayoutView(amountView))
    }

    private func makeCurrencySection() -> Section {
        Section(
            header: "CURRENCY",
            rows: [],
            footer: Section.Extremity.autoLayoutView(currencyView))
    }

    private func makeTippingSection() -> Section {
        Section(
            header: "TIPPING",
            rows: [Row(text: "Skip Tipping", accessory: .switchToggle(value: self.skipTipping) { [unowned self] _ in
                self.skipTipping.toggle()
                self.updateContent()
            })],
            footer: .autoLayoutView(tipEligibleAmountTextField))
    }

    private func makeSimulatedTipAmountSection() -> Section? {
        if Terminal.shared.connectedReader?.simulated == true {
            return Section(
                header: "SIMULATED TIP AMOUNT",
                footer: .autoLayoutView(simulatedTipAmountTextField))
        } else {
            return nil
        }
    }

    private func makePaymentMethodSection() -> Section {
        let shouldShowTestCardPickerView = Terminal.shared.connectedReader?.simulated == true

        let paymentMethodSection = Section(header: Section.Extremity.title("Payment Method"), rows: [
            Row(text: "Enable Interac Present", accessory: .switchToggle(value: self.interacPresentEnabled) { [unowned self] _ in
                self.interacPresentEnabled.toggle()
                self.updateContent()
            }),
            Row(text: "Enable Automatic Capture", accessory: .switchToggle(value: self.automaticCaptureEnabled) { [unowned self] _ in
                self.automaticCaptureEnabled.toggle()
                self.updateContent()
            }),
            Row(text: "Enable Manual Preferred", accessory: .switchToggle(value: self.manualPreferredEnabled) { [unowned self] _ in
                self.manualPreferredEnabled.toggle()
                self.updateContent()
            }),
            Row(text: "Decline Card Brand", detailText: {if let brand = declineCardBrand { return Terminal.stringFromCardBrand(brand) } else { return "None" }}(), selection: { [unowned self] in
                let brands: [CardBrand] = [
                    .visa,
                    .amex,
                    .masterCard,
                    .discover,
                    .JCB,
                    .dinersClub,
                    .interac,
                    .unionPay,
                    .eftposAu,
                ]
                self.presentValuePicker(options: ["None"] + brands.map { Terminal.stringFromCardBrand($0) }) { picked in
                    self.declineCardBrand = nil
                    for brand in brands where picked == Terminal.stringFromCardBrand(brand) {
                        self.declineCardBrand = brand
                        break
                    }
                    self.updateContent()
                }
            }, accessory: .disclosureIndicator, cellClass: Value1Cell.self),
            Row(text: "Requested Routing Priority",
                detailText: requestedPriority ?? "None",
                selection: { [unowned self] in
                    self.presentValuePicker(options: ["Domestic", "International", "None"]) { picked in
                        self.requestedPriority = (picked == "None") ? nil : picked
                        self.updateContent()
                    }
            }, accessory: .disclosureIndicator, cellClass: Value1Cell.self),
            Row(text: "Recollect After Card Brand Decline", accessory: .switchToggle(value: recollectAfterCardBrandDecline) { [unowned self] _ in
                recollectAfterCardBrandDecline.toggle()
                self.updateContent()
            }),
            Row(text: "Request Extended Authorization", accessory: .switchToggle(value: self.requestExtendedAuthorization) { [unowned self] _ in
                self.requestExtendedAuthorization.toggle()
                self.updateContent()
            }),
            Row(text: "Request Incremental Authorization Support", accessory: .switchToggle(value: self.requestIncrementalAuthorizationSupport) { [unowned self] _ in
                self.requestIncrementalAuthorizationSupport.toggle()
                self.updateContent()
            }),
        ], footer: shouldShowTestCardPickerView ? Section.Extremity.autoLayoutView(TestCardPickerView()) : nil)

        return paymentMethodSection
    }

    /// Makes the "SETUP FUTURE USAGE" section.
    private func makeSetupFutureUsageSection() -> Section? {
        let rows: [Row] = [
            Row(text: "Value",
                accessory: .segmentedControl(
                    items: ["default", "on_session", "off_session"],
                    selectedIndex: 0) { [unowned self] newIndex, _ in
                        switch newIndex {
                        case 0: self.setupFutureUsage = nil
                        case 1: self.setupFutureUsage = "on_session"
                        case 2: self.setupFutureUsage = "off_session"
                        default:
                            fatalError("Unknown option selected")
                        }
                    }
               )
        ]

        return Section(header: "SETUP FUTURE USAGE", rows: rows)
    }

    func makeDestinationPaymentSection() -> Section {

        let destinationPaymentSection = Section(
            header: "Destination Charge",
            rows: [],
            footer: Section.Extremity.autoLayoutView(connectedAccountTextField)
        )
        return destinationPaymentSection
    }

    // TODO: Consolidate this section with the Destination Charge Section
    func makeApplicationFeeAmountSection() -> Section {

        let applicationFeeAmountSection = Section(
            header: "Application Fee Amount",
            rows: [],
            footer: Section.Extremity.autoLayoutView(applicationFeeAmountTextField)
        )
        return applicationFeeAmountSection
    }


    private func updateContent() {

        let sections: [Section?] = [
            self.makeAmountSection(),
            self.makeCurrencySection(),
            self.makeTippingSection(),
            self.makeSimulatedTipAmountSection(),
            self.makePaymentMethodSection(),
            self.makeDestinationPaymentSection(),
            self.makeApplicationFeeAmountSection(),
            self.makeSetupFutureUsageSection(),
            self.startSection
        ]

        dataSource.sections = sections.compactMap { $0 }
    }
}


extension StartPaymentViewController: UITextFieldDelegate {
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
}
