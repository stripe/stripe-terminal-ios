//
//  ColoredButton.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/7/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit

class ColoredButton: UIButton {
    var textColor = UIColor.black {
        didSet {
            setTitleColor(textColor, for: .normal)
        }
    }

    var onTap: (()->())?

    fileprivate let buttonColor: UIColor
    fileprivate let disabledColor = UIColor.stripeGrey
    fileprivate var unhighlightedColor: UIColor {
        return isEnabled ? buttonColor : disabledColor
    }

    fileprivate var highlightColor: UIColor {
        return buttonColor.withAlphaComponent(0.5)
    }

    private let borderSpacing: CGFloat = 10

    init(title: String = "",
         color: UIColor = UIColor.stripeBlue,
         onTap: (()->())? = nil) {
        buttonColor = color
        self.onTap = onTap
        super.init(frame: .zero)

        backgroundColor = buttonColor
        setTitle(title, for: .normal)
        setTitleColor(textColor, for: .normal)
        titleLabel?.font = UIFont.preferredFont(forTextStyle: .headline)
        contentEdgeInsets = UIEdgeInsets(top: borderSpacing, left: borderSpacing, bottom: borderSpacing, right: borderSpacing)
        addTarget(self, action: #selector(buttonTapped), for: .touchUpInside)

        layer.cornerRadius = 15
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    @objc func buttonTapped() {
        if let handler = onTap {
            handler()
        }
    }

    override var isEnabled: Bool {
        didSet {
            backgroundColor = unhighlightedColor
        }
    }

    override var isHighlighted: Bool {
        didSet {
            if isHighlighted {
                backgroundColor = highlightColor
            } else {
                backgroundColor = unhighlightedColor
            }
        }
    }
}
