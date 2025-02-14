//
//  RootViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/7/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import StripeTerminal
import UIKit

class RootViewController: LargeTitleNavigationController {
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

    func toastView(viewToToast: UIView) {
        view.addSubview(viewToToast)

        viewToToast.alpha = 0.0
        UIView.animate(
            withDuration: 0.25,
            animations: {
                viewToToast.alpha = 1.0
            }
        )
        DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + .seconds(3)) {
            UIView.animate(
                withDuration: 0.25,
                animations: {
                    viewToToast.alpha = 0.0
                },
                completion: { _ in
                    viewToToast.removeFromSuperview()
                }
            )
        }
    }
}
