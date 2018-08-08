//
//  UIViewController+TextViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/12/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit

extension UIViewController {

    /**
     Presents the given object in a TextViewController
     */
    func present(object: CustomStringConvertible) {
        let viewController = TextViewController(object: object)
        let navController = UINavigationController(rootViewController: viewController)
        navController.navigationBar.isTranslucent = false
        present(navController, animated: true, completion: nil)
    }
    
}
