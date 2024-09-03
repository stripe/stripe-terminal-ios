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
    private var enableCustomerCancellation = false
    private var interacPresentEnabled = false
    private var automaticCaptureEnabled = false
    private var manualPreferredEnabled = false
    private var setupFutureUsage: String?
    private var requestedPriority: String?
    private var requestExtendedAuthorization = false
    private var requestIncrementalAuthorizationSupport = false
    private var declineCardBrand: CardBrand?
    private var recollectAfterCardBrandDecline = false
    private let isSposReader: Bool
    private var updatePaymentIntent = false
    private var requestDcc = false
    private var skipCapture = false
    private var paymentMethodTypes: [String] = [
        "card_present",
        "card",
        "interac_present",
        "wechat_pay"
    ]
    private var selectedPaymentMethodTypes: [String] = ["card_present"]

    private var connectedAccountId: String {
        connectedAccountTextField.textField.text ?? ""
    }

    private var applicationFeeAmount: NSNumber {
        NSNumber(value: (Double(applicationFeeAmountTextField.textField.text ?? "0") ?? 0))
    }

    private let connectedAccountTextField = TextFieldView(
        placeholderText: "Connected Stripe Account ID")

    private let applicationFeeAmountTextField = TextFieldView(placeholderText: "Application Fee Amount")

    private var offlineBehavior: OfflineBehavior = .preferOnline

    private lazy var offlineTransactionLimitTextField: TextFieldView = {
        let textField = TextFieldView(placeholderText: "10000", keyboardType: .numberPad)
        textField.textField.autocorrectionType = .no
        textField.textField.autocapitalizationType = .none
        textField.textField.clearButtonMode = .whileEditing
        return textField
    }()

    private lazy var offlineStoredTransactionLimitTextField: TextFieldView = {
        let textField = TextFieldView(placeholderText: "50000", keyboardType: .numberPad)
        textField.textField.autocorrectionType = .no
        textField.textField.autocapitalizationType = .none
        textField.textField.clearButtonMode = .whileEditing
        return textField
    }()

    private lazy var tipEligibleAmountTextField: AmountInputView = {
        let textField = AmountInputView(footer: "Must have on-reader tipping configured to have any effect.", placeholderText: "Tip-eligible amount")
        textField.textField.text = nil
        textField.textField.clearButtonMode = .whileEditing
        textField.textField.keyboardType = .numbersAndPunctuation
        return textField
    }()

    private lazy var simulatedTipAmountTextField: AmountInputView = {
        let textField = AmountInputView(placeholderText: "Simulated tip amount", keyboardType: .numberPad)
        textField.textField.text = nil
        textField.textField.clearButtonMode = .whileEditing
        return textField
    }()

    private lazy var surchargeNoticeTextField: TextFieldView = {
        let textField = TextFieldView(placeholderText: "Surcharge Notice")
        textField.textField.autocorrectionType = .no
        textField.textField.autocapitalizationType = .none
        textField.textField.clearButtonMode = .whileEditing
        textField.textField.keyboardType = .default
        return textField
    }()

    private lazy var amountSurchargeTextField: TextFieldView = {
        let textField = TextFieldView(placeholderText: "Amount Surcharge", keyboardType: .numberPad)
        textField.textField.autocorrectionType = .no
        textField.textField.autocapitalizationType = .none
        textField.textField.clearButtonMode = .whileEditing
        return textField
    }()

    init(isSposReader: Bool) {
        self.isSposReader = isSposReader
        super.init(style: .grouped)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
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

        offlineTransactionLimitTextField.textField.delegate = self
        offlineStoredTransactionLimitTextField.textField.delegate = self

        surchargeNoticeTextField.textField.delegate = self
        amountSurchargeTextField.textField.delegate = self

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

        let paymentParamsBuilder = PaymentIntentParametersBuilder(amount: amountView.amount,
                                                    currency: currencyView.currency)
            .setPaymentMethodTypes(self.selectedPaymentMethodTypes)
            .setCaptureMethod(captureMethod)
            .setSetupFutureUsage(setupFutureUsage)
            .setPaymentMethodOptionsParameters(makePaymentMethodOptionsParameters())
            .setMetadata([PaymentIntent.offlineIdMetadataKey: UUID().uuidString])

        // Set up destination payment
        if !connectedAccountId.isEmpty {
            paymentParamsBuilder.setTransferDataDestination(connectedAccountId)
            paymentParamsBuilder.setOnBehalfOf(connectedAccountId)
        }

        if applicationFeeAmount != 0 {
            paymentParamsBuilder.setApplicationFeeAmount(applicationFeeAmount)
        }

        Terminal.shared.simulatorConfiguration.simulatedTipAmount = NSNumber(value: simulatedTipAmountTextField.amount)

        let updatePaymentIntent = self.updatePaymentIntent || (self.declineCardBrand != nil)
        var surchargeNotice: String?
        if let text = surchargeNoticeTextField.textField.text, !text.isEmpty {
            surchargeNotice = text
        }
        let collectConfigBuilder = CollectConfigurationBuilder()
            .setSkipTipping(self.skipTipping)
            .setUpdatePaymentIntent(updatePaymentIntent)
            .setEnableCustomerCancellation(self.enableCustomerCancellation)
            .setRequestDynamicCurrencyConversion(self.requestDcc)
            .setSurchargeNotice(surchargeNotice)
        let confirmConfigBuilder = ConfirmConfigurationBuilder()

        if let amountSurcharge = amountSurchargeTextField.textField.text {
            if let parsedAmount = UInt(amountSurcharge, radix: 10) {
                confirmConfigBuilder.setAmountSurcharge(parsedAmount)
            }
        }

        do {
            if let eligibleAmount = Int(tipEligibleAmountTextField.textField.text ?? "none") {
                collectConfigBuilder.setTippingConfiguration(
                    try TippingConfigurationBuilder()
                        .setEligibleAmount(eligibleAmount)
                        .build()
                )
            }
            let collectConfig = try collectConfigBuilder.build()
            let confirmConfig = try confirmConfigBuilder.build()
            let vc = PaymentViewController(paymentParams: try paymentParamsBuilder.build(),
                collectConfig: collectConfig,
                confirmConfig: confirmConfig,
                declineCardBrand: declineCardBrand,
                recollectAfterCardBrandDecline: recollectAfterCardBrandDecline,
                isSposReader: self.isSposReader,
                offlineTransactionLimit: Int(offlineTransactionLimitTextField.textField.text ?? "10000") ?? 10000,
                offlineTotalTransactionLimit: Int(offlineStoredTransactionLimitTextField.textField.text ?? "50000") ?? 50000,
                offlineBehavior: self.offlineBehavior,
                skipCapture: self.skipCapture
            )
            let navController = LargeTitleNavigationController(rootViewController: vc)
            navController.presentationController?.delegate = self
            self.present(navController, animated: true, completion: nil)
        } catch {
            // Validation error generating the config.
            self.presentAlert(error: error)
        }
    }

    private func makePaymentMethodOptionsParameters() -> PaymentMethodOptionsParameters {
        let cardPresentParamsBuilder = CardPresentParametersBuilder()
            .setRequestExtendedAuthorization(self.requestExtendedAuthorization)
            .setRequestIncrementalAuthorizationSupport(self.requestIncrementalAuthorizationSupport)

        if manualPreferredEnabled {
            cardPresentParamsBuilder.setCaptureMethod(CardPresentCaptureMethod.manualPreferred)
        }

        if requestedPriority == "Domestic" {
            cardPresentParamsBuilder.setRequestedPriority(CardPresentRouting.domestic)
        }

        if requestedPriority == "International" {
            cardPresentParamsBuilder.setRequestedPriority(CardPresentRouting.international)
        }

        do {
            return try PaymentMethodOptionsParametersBuilder(cardPresentParameters: try cardPresentParamsBuilder.build()).build()
        } catch {
            fatalError("Error building PaymentMethodOptionsParameters: \(error.localizedDescription)")
        }
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

    private func makeSimulatedTipAmountSection() -> Section? {
        if Terminal.shared.connectedReader?.simulated == true {
            return Section(
                header: "SIMULATED TIP AMOUNT",
                footer: .autoLayoutView(simulatedTipAmountTextField))
        } else {
            return nil
        }
    }

    private func makePaymentMethodTypesSection() -> Section {
        let paymentMethodTypesSection = Section(header: Section.Extremity.title("Payment Methods"), rows: paymentMethodTypes.map({ (key: String) in
            return if key == "card_present" {
                Row(text: "Enable \(key)", accessory: .none)
            } else {
                Row(text: "Enable \(key)", accessory: .switchToggle(value: self.selectedPaymentMethodTypes.contains(key), { [unowned self] _ in
                    if let index = selectedPaymentMethodTypes.firstIndex(of: key) {
                        selectedPaymentMethodTypes.remove(at: index)
                    } else {
                        selectedPaymentMethodTypes.append(key)
                    }
                    self.updateContent()
                }))
            }
        }))
        return paymentMethodTypesSection
    }

    private func makePaymentMethodSection() -> Section {
        // TERMINAL-34013: Simulated TTP reader has simulated set to false
        let shouldShowTestCardPickerView = Terminal.shared.connectedReader?.simulated == true || (Terminal.shared.connectedReader?.serialNumber == "APPLEBUILTINSIMULATOR-1")

        let paymentMethodSection = Section(header: Section.Extremity.title("Payment Method Options"), rows: [
            Row(text: "Enable Automatic Capture", accessory: .switchToggle(value: self.automaticCaptureEnabled) { [unowned self] _ in
                self.automaticCaptureEnabled.toggle()
                self.updateContent()
            }),
            Row(text: "Enable Manual Preferred", accessory: .switchToggle(value: self.manualPreferredEnabled) { [unowned self] _ in
                self.manualPreferredEnabled.toggle()
                self.updateContent()
            }),
            Row(text: "Requested Routing Priority",
                detailText: requestedPriority ?? "None",
                selection: { [unowned self] in
                    self.presentValuePicker(options: ["Domestic", "International", "None"]) { picked in
                        self.requestedPriority = (picked == "None") ? nil : picked
                        self.updateContent()
                    }
            }, accessory: .disclosureIndicator, cellClass: Value1Cell.self),
            Row(text: "Request Extended Authorization", accessory: .switchToggle(value: self.requestExtendedAuthorization) { [unowned self] _ in
                self.requestExtendedAuthorization.toggle()
                self.updateContent()
            }),
            Row(text: "Request Incremental Authorization Support", accessory: .switchToggle(value: self.requestIncrementalAuthorizationSupport) { [unowned self] _ in
                self.requestIncrementalAuthorizationSupport.toggle()
                self.updateContent()
            }),
            Row(text: "Skip Capture (if available)", accessory: .switchToggle(value: self.skipCapture) { [unowned self] _ in
                self.skipCapture.toggle()
                self.updateContent()
            }),
        ], footer: shouldShowTestCardPickerView ? Section.Extremity.autoLayoutView(TestCardPickerView()) : nil)

        return paymentMethodSection
    }

    // Makes the UPDATE PAYMENT INTENT section
    private func makeUpdatePaymentIntentSection() -> Section? {
        let switchRow: [Row] = [
            Row(text: "Update PaymentIntent", accessory: .switchToggle(value: self.updatePaymentIntent) { [unowned self] _ in
                self.updatePaymentIntent.toggle()
                self.updateContent()
                self.declineCardBrand = nil
                self.recollectAfterCardBrandDecline = false
            })
        ]
        let contentRows: [Row] = [
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
            Row(text: "Recollect After Card Brand Decline", accessory: .switchToggle(value: recollectAfterCardBrandDecline) { [unowned self] _ in
                recollectAfterCardBrandDecline.toggle()
                self.updateContent()
            }),
        ]
        let rows = self.updatePaymentIntent ? (switchRow + contentRows) : switchRow

        return Section(header: "UPDATE PAYMENT INTENT", rows: rows)
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

    private func makeOfflineTransactionLimitSection() -> Section {
        let offlineTransactionLimitSection = Section(header: .title("Offline Mode Transaction Limit"), rows: [], footer: .autoLayoutView(offlineTransactionLimitTextField))
        return offlineTransactionLimitSection
    }

    private func makeOfflineStoredTransactionLimitSection() -> Section {
        let offlineStoredTransactionLimitSection = Section(header: .title("Offline Mode Stored Transaction Limit"), rows: [], footer: .autoLayoutView(offlineStoredTransactionLimitTextField))
        return offlineStoredTransactionLimitSection
    }

    private func makeOfflineBehaviorSection() -> Section {
        let rows: [Row] = [
            Row(accessory: .segmentedControl(
                    items: ["prefer online", "require online", "force offline"],
                    selectedIndex: 0) { [unowned self] newIndex, _ in
                        switch newIndex {
                        case 0: self.offlineBehavior = .preferOnline
                        case 1: self.offlineBehavior = .requireOnline
                        case 2: self.offlineBehavior = .forceOffline
                        default:
                            fatalError("Unknown option selected")
                        }
                    }
               )
        ]

        return Section(header: "OFFLINE BEHAVIOR", rows: rows)
    }

    /// Makes the "DCC" section.
    private func makeRequestDccSection() -> Section {
        let rows: [Row] = [
            Row(text: "Dynamic Currency Conversion", accessory: .switchToggle(value: self.requestDcc) { [unowned self] _ in
                if !updatePaymentIntent {
                    self.updatePaymentIntent.toggle()
                }
                self.requestDcc.toggle()
                self.updateContent()
            })
        ]
        return Section(header: "Request Dynamic Currency Conversion", rows: rows)
    }

    /// Makes the "Surcharge notice" section.
    private func makeSurchargeNoticeSection() -> Section {
        let offlineTransactionLimitSection = Section(header: .title("Surcharge Notice"), rows: [], footer: .autoLayoutView(surchargeNoticeTextField))
        return offlineTransactionLimitSection
    }

    /// Makes the "Amount Surcharge" section.
    private func makeAmountSurchargeSection() -> Section {
        let offlineTransactionLimitSection = Section(header: .title("Amount Surcharge"), rows: [], footer: .autoLayoutView(amountSurchargeTextField))
        return offlineTransactionLimitSection
    }

    private func updateContent() {

        let sections: [Section?] = [
            self.makeAmountSection(),
            self.makeCurrencySection(),
            self.makeTippingSection(),
            self.makeTransactionSection(),
            self.makeSimulatedTipAmountSection(),
            self.makePaymentMethodTypesSection(),
            self.makePaymentMethodSection(),
            self.makeRequestDccSection(),
            self.makeSurchargeNoticeSection(),
            self.makeAmountSurchargeSection(),
            self.makeUpdatePaymentIntentSection(),
            self.makeDestinationPaymentSection(),
            self.makeApplicationFeeAmountSection(),
            self.makeOfflineTransactionLimitSection(),
            self.makeOfflineStoredTransactionLimitSection(),
            self.makeOfflineBehaviorSection(),
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

// MARK: - PaymentIntent Metadata Helpers
extension PaymentIntent {
    public static let offlineIdMetadataKey = "offlineId"

    public var offlineId: String? {
        return metadata?[PaymentIntent.offlineIdMetadataKey]
    }
}
