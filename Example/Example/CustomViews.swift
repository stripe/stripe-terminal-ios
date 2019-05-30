//
//  CustomViews.swift
//  Example
//
//  Created by Ben Guo on 9/8/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static

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
    var onAmountUpdated: (String) -> () = { _ in }

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

    var currency: String {
        if let text = textField.text {
            return text.lowercased()
        }
        return "usd"
    }
    var onCurrencyUpdated: (String) -> () = { _ in }

    let pickerView = UIPickerView(frame: CGRect.zero)

    convenience init() {
        self.init(text: "Currency", footer: "")
        textField.text = StripeCurrencies.all.first
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
        return StripeCurrencies.all.count
    }

    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
        let currencyCode = StripeCurrencies.all[row]
        var title = currencyCode
        if let localizedString = NSLocale.current.localizedString(forCurrencyCode: currencyCode.uppercased()) {
            title = "\(title) – \(localizedString)"
        }
        return title
    }

    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        let currency = StripeCurrencies.all[row]
        onCurrencyUpdated(currency)
        textField.text = currency
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

    init(text: String, footer: String) {
        super.init(frame: .zero)

        backgroundColor = UIColor.white
        addSubview(textField)
        footerLabel.text = footer
        addSubview(footerLabel)

        let stack = UIStackView(arrangedSubviews: [
            textField,
            footerLabel,
            ])
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
    private lazy var label: UILabel = {
        let label = UILabel()
        label.font = UIFont(name: "Menlo", size: UIFont.systemFontSize)
        label.numberOfLines = 0
        label.textColor = UIColor.darkGray
        label.translatesAutoresizingMaskIntoConstraints = false
        return label
    }()

    init(text: String) {
        super.init(frame: .zero)

        layoutMargins = UIEdgeInsets(top: 20, left: 16, bottom: 20, right: 16)
        addSubview(label)
        label.text = text
        label.leadingAnchor.constraint(equalTo: layoutMarginsGuide.leadingAnchor).isActive = true
        label.trailingAnchor.constraint(equalTo: layoutMarginsGuide.trailingAnchor).isActive = true
        label.topAnchor.constraint(equalTo: layoutMarginsGuide.topAnchor).isActive = true
        label.bottomAnchor.constraint(equalTo: layoutMarginsGuide.bottomAnchor).isActive = true
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
            activityIndicator,
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
    open var inset : UIEdgeInsets = UIEdgeInsets() {
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
