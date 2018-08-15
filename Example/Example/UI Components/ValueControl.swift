//
//  ValueControl.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/7/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit

extension UIView {
    fileprivate var parentViewController: UIViewController? {
        var parentResponder: UIResponder? = self
        while let responder = parentResponder {
            parentResponder = responder.next
            if let vc = responder as? UIViewController {
                return vc
            }
        }
        return nil
    }
}

class BaseValueControl: UIView {
    fileprivate let stackView = UIStackView.buildDefaultVerticalStack()
    fileprivate var title: String? {
        return self.titleLabel.text
    }
    fileprivate let titleLabel = UILabel()
    fileprivate let valueButton = ColoredButton(color: UIColor.stripeOffWhite)
    fileprivate let borderSpacing: CGFloat = 10

    override init(frame: CGRect) {
        super.init(frame: frame)
        backgroundColor = UIColor.stripeLightGrey

        stackView.layoutMargins = UIEdgeInsets(top: borderSpacing, left: borderSpacing, bottom: borderSpacing, right: borderSpacing)
        stackView.isLayoutMarginsRelativeArrangement = true
        stackView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        stackView.translatesAutoresizingMaskIntoConstraints = true
        addSubview(stackView)

        titleLabel.textAlignment = .center
        titleLabel.backgroundColor = .clear
        titleLabel.font = UIFont.preferredFont(forTextStyle: .headline)
        titleLabel.sizeToFit()
        stackView.addArrangedSubview(titleLabel)

        valueButton.backgroundColor = .white
        valueButton.layer.cornerRadius = 15
        stackView.addArrangedSubview(valueButton)
    }

    required init(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

class ValueControl<T>: BaseValueControl where T: LosslessStringConvertible {

    var onValueChanged: (T)->() = { _ in }

    var value: T {
        didSet {
            valueButton.setTitle(value.description, for: .normal)
            self.onValueChanged(value)
            if persistValue {
                PasteboardStore.shared[pasteboardKey] = value.description
            }
        }
    }

    var isEnabled: Bool = true {
        didSet {
            valueButton.isEnabled = isEnabled
        }
    }

    fileprivate var pasteboardKey: String {
        var key = String(describing: type(of: self))
        if let title = self.title {
            key = "\(key).\(title)"
        }
        return key
    }

    fileprivate let persistValue: Bool

    /// Creates a value control that can be edited by entering text
    init(title: String,
         value: T,
         persistValue: Bool = true,
         onValueChanged: ((T)->())? = nil) {

        self.value = value
        self.persistValue = persistValue
        if let handler = onValueChanged {
            self.onValueChanged = handler
        }
        super.init(frame: .zero)
        titleLabel.text = title
        valueButton.onTap = {
            self.parentViewController?.presentValueInput(title: self.titleLabel.text,
                                                         currentValue: value,
                                                         handler: { value in
                                                            if let v = value {
                                                                self.value = v
                                                            }
            })
        }

        if persistValue {
            self.loadSavedValue()
        }
        valueButton.setTitle(self.value.description, for: .normal)
    }

    /// Creates a value control that can be edited by selecting a picker option
    init(title: String,
         value: T,
         options: [T],
         persistValue: Bool = true,
         onValueChanged: ((T)->())? = nil) {

        self.value = value
        self.persistValue = persistValue
        if let handler = onValueChanged {
            self.onValueChanged = handler
        }
        super.init(frame: .zero)
        titleLabel.text = title
        valueButton.onTap = { [weak valueButton] in
            self.parentViewController?.presentValuePicker(title: self.titleLabel.text,
                                                          options: options,
                                                          from: valueButton,
                                                          handler: { value in
                                                            if let v = value {
                                                                self.value = v
                                                            }
            })
        }

        if persistValue {
            self.loadSavedValue()
        }
        valueButton.setTitle(self.value.description, for: .normal)
    }

    required init(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    func loadSavedValue() {
        if let savedValueString = PasteboardStore.shared[pasteboardKey],
            let savedValue = T(savedValueString) {
            self.value = savedValue
        }
    }

}
