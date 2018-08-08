//
//  StackViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/12/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit

class StackViewController: UIViewController {

    let stackView = UIStackView.buildDefaultVerticalStack()

    var stack: [[UIView]] = [[UIView]]() {
        didSet {
            for view in self.stackView.arrangedSubviews {
                view.removeFromSuperview()
            }
            for column in self.stack {
                let view = UIStackView.buildDefaultHorizontalStack()
                for row in column {
                    view.addArrangedSubview(row)
                }
                self.stackView.addArrangedSubview(view)
            }
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .white
        view.addSubview(stackView)

        let topPadding = (navigationController == nil) ? 40 : 20
        let padding = 10
        view.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "V:|-t-[stackView]-p-|",
                                                           options: .alignAllLeading,
                                                           metrics: ["t": topPadding,
                                                                     "p": padding],
                                                           views: ["stackView": stackView]))
        view.addConstraints(NSLayoutConstraint.constraints(withVisualFormat: "H:|-p-[stackView]-p-|",
                                                           options: .alignAllLeading,
                                                           metrics: ["p": padding],
                                                           views: ["stackView": stackView]))
    }

}
