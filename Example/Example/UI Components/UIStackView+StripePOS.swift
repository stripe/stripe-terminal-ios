//
//  UIStackView+StripePOS.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/7/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit

extension UIStackView {

    static func buildDefaultVerticalStack() -> UIStackView {
        let view = UIStackView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.alignment = .fill
        view.axis = .vertical
        view.distribution = .fillEqually
        view.spacing = 10
        return view
    }

    static func buildDefaultHorizontalStack() -> UIStackView {
        let view = UIStackView()
        view.translatesAutoresizingMaskIntoConstraints = false
        view.alignment = .fill
        view.axis = .horizontal
        view.distribution = .fillEqually
        view.spacing = 10
        return view
    }

}
