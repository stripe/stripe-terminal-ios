//
//  LabelOverlayView.swift
//  Example
//
//  Created by Brian Cooke on 08/17/23.
//  Copyright © 2023 Stripe. All rights reserved.
//

import UIKit

class LabelOverlayView: UIView {
    let label = UILabel()

    init(labelText: String) {
        super.init(frame: .zero)

        isUserInteractionEnabled = false
        backgroundColor = .init(white: 0, alpha: 0.8)
        layer.masksToBounds = true
        layer.cornerRadius = 5.0

        label.numberOfLines = 0
        label.textColor = .lightText
        label.textAlignment = .center
        label.text = labelText
        label.translatesAutoresizingMaskIntoConstraints = false
        self.translatesAutoresizingMaskIntoConstraints = false
        self.addSubview(label)
    }

    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }

    override func didMoveToSuperview() {
        guard let superview = superview else { return }

        let padding: CGFloat = 25.0
        NSLayoutConstraint.activate([
            // Self, height == label's height and bind to the bottom
            heightAnchor.constraint(equalTo: label.heightAnchor, constant: padding),
            bottomAnchor.constraint(equalTo: superview.bottomAnchor, constant: -padding),
            leadingAnchor.constraint(equalTo: superview.leadingAnchor, constant: padding),
            trailingAnchor.constraint(equalTo: superview.trailingAnchor, constant: -padding),

            // Center the label
            label.centerYAnchor.constraint(equalTo: centerYAnchor),
            label.leadingAnchor.constraint(equalTo: leadingAnchor, constant: padding),
            label.trailingAnchor.constraint(equalTo: trailingAnchor, constant: -padding)
        ])
    }
}
