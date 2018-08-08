//
//  MeterView.swift
//  Example
//
//  Created by Ben Guo on 6/15/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit

class MeterView: UIView {

    var value: Float {
        get {
            return progressView.progress
        }
        set {
            progressView.progress = newValue
        }
    }

    private let stackView = UIStackView.buildDefaultVerticalStack()
    private let titleLabel = UILabel()
    private let progressView = UIProgressView(progressViewStyle: .default)
    private let borderSpacing: CGFloat = 10

    init(title: String, color: UIColor? = nil, value: Float = 0.0) {
        super.init(frame: .zero)

        titleLabel.text = title
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

        progressView.backgroundColor = .clear
        progressView.progress = value
        progressView.trackTintColor = UIColor.stripeOffWhite
        if let color = color {
            progressView.tintColor = color
        }
        stackView.addArrangedSubview(progressView)
    }

    required init(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

}
