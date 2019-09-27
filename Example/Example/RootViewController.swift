//
//  RootViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/7/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit
import StripeTerminal

class RootViewController: LargeTitleNavigationController  {
    init() {
        super.init(nibName: nil, bundle: nil)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        let vc = ReaderViewController()
        self.pushViewController(vc, animated: false)
    }

}

