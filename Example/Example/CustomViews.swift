//
//  CustomViews.swift
//  Example
//
//  Created by Ben Guo on 9/8/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

open class RedButtonCell: ButtonCell {
    // MARK: - Initializers
    public override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        tintColor = UIColor.red
    }

    public required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        tintColor = UIColor.red
    }
}

open class DisabledCell: UITableViewCell, Cell {
    public override init(style: UITableViewCell.CellStyle = .default, reuseIdentifier: String?) {
        super.init(style: .default, reuseIdentifier: reuseIdentifier)
        self.textLabel?.textColor = UIColor.lightGray
        self.selectionStyle = .none
        self.isUserInteractionEnabled = false
    }

    public required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
}

open class DisabledSubtitleCell: UITableViewCell, Cell {
    public override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: .subtitle, reuseIdentifier: reuseIdentifier)
        self.textLabel?.textColor = UIColor.lightGray
        self.selectionStyle = .none
        self.isUserInteractionEnabled = false
    }

    public required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
}

open class MethodStartCell: UITableViewCell, Cell {
    public override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: .subtitle, reuseIdentifier: reuseIdentifier)
        self.textLabel?.font = UIFont(name: "Menlo", size: UIFont.smallSystemFontSize)
        self.backgroundColor = UIColor.groupTableViewBackground
    }

    public required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
}

open class LogEventCell: UITableViewCell, Cell {
    public override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: .subtitle, reuseIdentifier: reuseIdentifier)
        self.detailTextLabel?.textColor = UIColor.gray
        if let size = self.detailTextLabel?.font.pointSize {
            self.detailTextLabel?.font = UIFont(name: "Menlo", size: size)
        }
    }

    public required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }
}

class AmountInputView: TextFieldView, UITextFieldDelegate {
    var amount: UInt {
        if let text = textField.text,
            let amount = UInt(text) {
            return amount
        }
        return 0
    }
    var amountString: String {
        var doubleAmount = Double(amount)
        if !StripeCurrencies.isNoDecimalCurrency(currency: self.numberFormatter.currencyCode) {
            doubleAmount = Double(amount)/Double(100)
        }
        return numberFormatter.string(from: NSNumber(value: doubleAmount)) ?? ""
    }
    var onAmountUpdated: (String) -> Void = { _ in }

    var numberFormatter = NumberFormatter()
    private let defaultAmount: UInt = 100

    convenience init() {
        self.init(text: "Amount", footer: "")
        textField.text = String(defaultAmount)
        textField.delegate = self
        textField.keyboardType = .numberPad
        numberFormatter.currencyCode = "usd"
        numberFormatter.numberStyle = .currency
    }

    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {
        if let text = textField.text,
            let textRange = Range(range, in: text) {
            let newText = text.replacingCharacters(in: textRange, with: string)
            if newText.count < 9 {
                textField.text = newText
            }
        }
        onAmountUpdated(amountString)
        return false
    }

    func textFieldDidEndEditing(_ textField: UITextField) {
        textField.text = String(amount)
    }
}

class CurrencyInputView: TextFieldView, UIPickerViewDelegate, UIPickerViewDataSource {

    /// A lowercased representation of the currently selected currency code.
    ///
    /// "usd" or "cad" would both be possible values here; "GBP" or
    /// "Singapore Dollars" would not be.
    var currency: String {
        if let text = textField.text {
            return text.lowercased()
        }
        return "usd"
    }
    var onCurrencyUpdated: (String) -> Void = { _ in }

    let pickerView = UIPickerView(frame: CGRect.zero)

    convenience init() {
        self.init(text: "Currency", footer: "")
        textField.text = StripeCurrencies.supported.first
        textField.keyboardType = .alphabet
        pickerView.dataSource = self
        pickerView.delegate = self
        pickerView.backgroundColor = UIColor.white
        textField.inputView = pickerView
    }

    func initialize() {
        textField.inputView = pickerView
    }

    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }

    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return StripeCurrencies.supported.count
    }

    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        let currencyCode = StripeCurrencies.supported[row]
        var title = currencyCode
        if let localizedString = NSLocale.current.localizedString(forCurrencyCode: currencyCode.uppercased()) {
            title = "\(title) – \(localizedString)"
        }
        return title
    }

    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        let currency = StripeCurrencies.supported[row]
        onCurrencyUpdated(currency)
        textField.text = currency
    }
}


class CountryInputView: TextFieldView, UIPickerViewDelegate, UIPickerViewDataSource {

    /// An uppercased  representation of the currently selected country code, e.g. "us"
    var country: String = "US"
    var onCountryUpdated: (String) -> Void = { _ in }

    let pickerView = UIPickerView(frame: CGRect.zero)

    convenience init() {
        self.init(text: "Country")
        textField.text = generateLabel(forCountryCode: StripeCountries.supportedByTerminal.first ?? "US")
        textField.keyboardType = .alphabet
        pickerView.dataSource = self
        pickerView.delegate = self
        pickerView.backgroundColor = UIColor.white
        textField.inputView = pickerView
    }

    convenience init(header: String) {
        self.init(text: "Country", header: header)
        textField.text = generateLabel(forCountryCode: StripeCountries.supportedByTerminal.first ?? "US")
        textField.keyboardType = .alphabet
        pickerView.dataSource = self
        pickerView.delegate = self
        pickerView.backgroundColor = UIColor.white
        textField.inputView = pickerView
    }

    func initialize() {
        textField.inputView = pickerView
    }

    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        return 1
    }

    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        return StripeCountries.supportedByTerminal.count
    }

    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        let countryCode = StripeCountries.supportedByTerminal[row]
        return generateLabel(forCountryCode: countryCode)
    }

    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        let countryCode = StripeCountries.supportedByTerminal[row]
        onCountryUpdated(countryCode)
        country = countryCode
        textField.text = generateLabel(forCountryCode: countryCode)
    }

    private func generateLabel(forCountryCode countryCode: String) -> String {
        if let countryName = StripeCountries.countryName(forRegionCode: countryCode) {
            return "\(countryName) (\(countryCode))"
        } else {
            return countryCode
        }
    }
}

class ReaderUpdatePicker: TextFieldView, UIPickerViewDelegate, UIPickerViewDataSource {

    let pickerView = UIPickerView(frame: CGRect.zero)

    let updateTypesInDisplayOrder: [SimulateReaderUpdate] = [
        .available,
        .none,
        .required,
        .lowBattery,
        .random
    ]

    let updateTypeDescriptions: [SimulateReaderUpdate: String] = [
        .available: "Update Available",
        .none: "No Update",
        .required: "Update Required",
        .lowBattery: "Update required; reader has low battery",
        .random: "Random"
    ]

    convenience init() {
        self.init(text: "")
        let initialSelectedReaderUpdate = Terminal.shared.simulatorConfiguration.availableReaderUpdate
        textField.text = updateTypeDescriptions[initialSelectedReaderUpdate]
        textField.keyboardType = .alphabet
        pickerView.dataSource = self
        pickerView.delegate = self
        pickerView.backgroundColor = UIColor.white
        textField.inputView = pickerView
        pickerView.selectRow(updateTypesInDisplayOrder.firstIndex(of: initialSelectedReaderUpdate) ?? 0, inComponent: 0, animated: false)
    }

    func initialize() {
        textField.inputView = pickerView
    }

    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        1
    }

    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        updateTypesInDisplayOrder.count
    }

    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return updateTypeDescriptions[updateTypesInDisplayOrder[row]]
    }

    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        Terminal.shared.simulatorConfiguration.availableReaderUpdate = updateTypesInDisplayOrder[row]
        textField.text = updateTypeDescriptions[updateTypesInDisplayOrder[row]]
    }
}

class TestCardPickerView: TextFieldView, UIPickerViewDelegate, UIPickerViewDataSource {

    let pickerView = UIPickerView(frame: CGRect.zero)

    let cardTypesInDisplayOrder: [SimulatedCardType] = [
        .visa,
        .visaDebit,
        .mastercard,
        .masterDebit,
        .mastercardPrepaid,
        .amex,
        .amex2,
        .discover,
        .discover2,
        .diners,
        .diners14Digit,
        .jcb,
        .unionPay,
        .interac,
        .chargeDeclined,
        .chargeDeclinedInsufficientFunds,
        .chargeDeclinedLostCard,
        .chargeDeclinedStolenCard,
        .chargeDeclinedExpiredCard,
        .chargeDeclinedProcessingError,
        .refundFailed
    ]

    convenience init() {
        self.init(text: "")
        textField.text = "\(Terminal.shared.simulatorConfiguration.simulatedCard)"
        textField.keyboardType = .alphabet
        pickerView.dataSource = self
        pickerView.delegate = self
        pickerView.backgroundColor = UIColor.white
        textField.inputView = pickerView
    }

    func initialize() {
        textField.inputView = pickerView
    }

    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        1
    }

    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        cardTypesInDisplayOrder.count
    }

    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        return SimulatedCard.init(type: cardTypesInDisplayOrder[row]).description
    }

    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        let type = cardTypesInDisplayOrder[row]
        let simulatedCard = SimulatedCard.init(type: type)
        Terminal.shared.simulatorConfiguration.simulatedCard = simulatedCard
        textField.text = simulatedCard.description
    }
}


class TextFieldView: UIView {
    lazy var textField: InsetTextField = {
        let textField = InsetTextField()
        textField.translatesAutoresizingMaskIntoConstraints = false
        textField.font = UIFont.systemFont(ofSize: UIFont.labelFontSize)
        textField.inset = UIEdgeInsets(top: 8, left: 16, bottom: 8, right: 16)
        textField.backgroundColor = UIColor.white
        return textField
    }()

    lazy var headerLabel: InsetLabel = {
        let label = InsetLabel()
        label.font = UIFont.systemFont(ofSize: UIFont.systemFontSize)
        label.numberOfLines = 0
        label.translatesAutoresizingMaskIntoConstraints = false
        label.inset = UIEdgeInsets(top: 8, left: 16, bottom: 8, right: 16)
        label.backgroundColor = UIColor.groupTableViewBackground
        label.textColor = UIColor.gray
        label.isUserInteractionEnabled = true
        return label
    }()

    lazy var footerLabel: InsetLabel = {
        let label = InsetLabel()
        label.font = UIFont.systemFont(ofSize: UIFont.systemFontSize)
        label.numberOfLines = 0
        label.translatesAutoresizingMaskIntoConstraints = false
        label.inset = UIEdgeInsets(top: 8, left: 16, bottom: 8, right: 16)
        label.backgroundColor = UIColor.groupTableViewBackground
        label.textColor = UIColor.gray
        label.isUserInteractionEnabled = true
        return label
    }()

    init(text: String? = nil, header: String? = nil, footer: String? = nil) {
        super.init(frame: .zero)
        buildTextView(header: header, footer: footer)
    }

    private func buildTextView(header: String?, footer: String?) {
        backgroundColor = UIColor.white
        addSubview(textField)
        footerLabel.text = footer
        headerLabel.text = header
        addSubview(footerLabel)

        let stack = UIStackView(arrangedSubviews: [
            header != nil ? headerLabel : nil,
            textField,
            footer != nil ? footerLabel : nil
        ].compactMap { return $0 })
        stack.axis = .vertical
        stack.distribution = .equalSpacing

        addSubview(stack)

        stack.translatesAutoresizingMaskIntoConstraints = false
        let insets = UIEdgeInsets.zero
        if #available(iOS 11.0, *) {
            stack.anchor(to: safeAreaLayoutGuide, withInsets: insets)
        } else {
            stack.anchorToSuperviewAnchors(withInsets: insets)
        }
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

class MonospaceTextView: UIView {
    private lazy var textView: UITextView = {
        let textView = UITextView()
        textView.font = UIFont(name: "Menlo", size: UIFont.systemFontSize)
        textView.textColor = UIColor.darkGray
        textView.isEditable = false
        textView.isScrollEnabled = false
        textView.textContainerInset = UIEdgeInsets.zero
        textView.textContainer.lineFragmentPadding = 0
        textView.translatesAutoresizingMaskIntoConstraints = false
        return textView
    }()

    init(text: String) {
        super.init(frame: .zero)

        layoutMargins = UIEdgeInsets(top: 20, left: 16, bottom: 20, right: 16)
        addSubview(textView)
        textView.text = text
        textView.leadingAnchor.constraint(equalTo: layoutMarginsGuide.leadingAnchor).isActive = true
        textView.trailingAnchor.constraint(equalTo: layoutMarginsGuide.trailingAnchor).isActive = true
        textView.topAnchor.constraint(equalTo: layoutMarginsGuide.topAnchor).isActive = true
        textView.bottomAnchor.constraint(equalTo: layoutMarginsGuide.bottomAnchor).isActive = true
        backgroundColor = UIColor.white
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

class LinkTextView: UIView {

    static func buildAttributedString(prefix: String, linkName: String, urlString: String) -> NSAttributedString {
        let font = UIFont.systemFont(ofSize: UIFont.systemFontSize)
        let aString = NSMutableAttributedString(string: prefix + linkName)
        let fullRange = NSRange(location: 0, length: aString.string.count)
        let prefixRange = NSRange(location: 0, length: prefix.count)
        aString.addAttribute(.foregroundColor, value: UIColor.gray, range: prefixRange)
        aString.addAttribute(.font, value: font, range: fullRange)
        let linkRange = NSRange(location: prefix.count, length: linkName.count)
        aString.addAttribute(.link, value: urlString, range: linkRange)
        return aString
    }

    private lazy var textView: UITextView = {
        let view = UITextView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.backgroundColor = UIColor.clear
        view.isScrollEnabled = false
        view.isEditable = false
        return view
    }()

    init(prefix: String, linkName: String, urlString: String) {
        super.init(frame: CGRect.zero)

        layoutMargins = UIEdgeInsets(top: 0, left: 16, bottom: 0, right: 16)
        addSubview(textView)
        textView.leadingAnchor.constraint(equalTo: layoutMarginsGuide.leadingAnchor).isActive = true
        textView.trailingAnchor.constraint(equalTo: layoutMarginsGuide.trailingAnchor).isActive = true
        textView.topAnchor.constraint(equalTo: layoutMarginsGuide.topAnchor).isActive = true
        textView.bottomAnchor.constraint(equalTo: layoutMarginsGuide.bottomAnchor).isActive = true
        textView.setContentOffset(CGPoint.zero, animated: false)

        textView.attributedText = LinkTextView.buildAttributedString(prefix: prefix, linkName: linkName, urlString: urlString)
        textView.sizeToFit()
        frame = CGRect(x: 0, y: 0, width: 0, height: textView.bounds.height)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

class ActivityIndicatorHeaderView: UIView {

    let activityIndicator = UIActivityIndicatorView(style: .gray)
    var title: String {
        didSet {
            label.text = title.uppercased()
        }
    }

    private lazy var label: UILabel = {
        let label = UILabel()
        label.font = UIFont.systemFont(ofSize: UIFont.systemFontSize)
        label.textColor = UIColor(red: 0.42, green: 0.42, blue: 0.44, alpha: 1.0)
        label.numberOfLines = 0
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()

    init(title: String) {
        self.title = title
        super.init(frame: .zero)

        label.text = title.uppercased()
        // https://useyourloaf.com/blog/stack-views-and-multi-line-labels/
        activityIndicator.setContentHuggingPriority(.required - 1, for: .horizontal)
        let stack = UIStackView(arrangedSubviews: [
            label,
            activityIndicator
        ])
        stack.axis = .horizontal
        stack.distribution = .fill

        addSubview(stack)

        stack.translatesAutoresizingMaskIntoConstraints = false
        let insets = UIEdgeInsets(top: 14, left: 16, bottom: 6, right: 16)
        if #available(iOS 11.0, *) {
            stack.anchor(to: safeAreaLayoutGuide, withInsets: insets)
        } else {
            stack.anchorToSuperviewAnchors(withInsets: insets)
        }

        bounds.size.height = 50
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

open class InsetTextField: UITextField {
    public var inset = UIEdgeInsets(top: 0, left: 0, bottom: 0, right: 0) {
        didSet { setNeedsDisplay() }
    }

    public override init(frame: CGRect) {
        super.init(frame: frame)
    }

    convenience init() {
        self.init(frame: .zero)
    }

    public required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }

    open override func textRect(forBounds bounds: CGRect) -> CGRect {
        return bounds.inset(by: inset)
    }

    open override func editingRect(forBounds bounds: CGRect) -> CGRect {
        return bounds.inset(by: inset)
    }

    open override func placeholderRect(forBounds bounds: CGRect) -> CGRect {
        return bounds.inset(by: inset)
    }

    open override func drawText(in rect: CGRect) {
        super.drawText(in: rect.inset(by: inset))
    }
}

open class InsetLabel: UILabel {
    open var inset: UIEdgeInsets = UIEdgeInsets() {
        didSet {
            super.invalidateIntrinsicContentSize()
        }
    }

    open override var intrinsicContentSize: CGSize {
        var size = super.intrinsicContentSize
        size.width += inset.left + inset.right
        size.height += inset.top + inset.bottom
        return size
    }

    override open func drawText(in rect: CGRect) {
        return super.drawText(in: rect.inset(by: inset))
    }
}

open class LargeTitleNavigationController: UINavigationController {
    open override func viewDidLoad() {
        super.viewDidLoad()

        navigationBar.isTranslucent = false

        if #available(iOS 11.0, *) {
            navigationBar.prefersLargeTitles = true
        }

        if #available(iOS 13.0, *) {
            navigationBar.isTranslucent = true
        }
    }
}
