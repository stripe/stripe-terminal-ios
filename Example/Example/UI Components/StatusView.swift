//
//  StatusView.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/8/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit

class StatusView<T>: UIView where T: CustomStringConvertible {

    var onValueChanged: (T?)->() = { _ in }

    var value: T? {
        didSet {
            valueLabel.text = value?.description
            self.onValueChanged(value)
        }
    }

    var valueColor: UIColor = .white {
        didSet {
            valueLabel.backgroundColor = valueColor
        }
    }

    private let stackView = UIStackView.buildDefaultVerticalStack()
    private let titleLabel = UILabel()
    private let valueLabel = UILabel()
    private let borderSpacing: CGFloat = 10

    init(title: String, value: T? = nil) {
        self.value = value
        super.init(frame: .zero)

        titleLabel.text = title
        valueLabel.text = value?.description
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

        valueLabel.textAlignment = .center
        valueLabel.backgroundColor = valueColor
        valueLabel.sizeToFit()
        stackView.addArrangedSubview(valueLabel)
    }

    required init(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

}
