//
//  UIViewController+Presentation.swift
//  Example
//
//  Created by Brian Cooke on 10/18/24.
//  Copyright © 2024 Stripe. All rights reserved.
//

import UIKit

extension UIViewController {
    func topViewController() -> UIViewController? {
        guard
            let keyWindow = UIApplication.shared.connectedScenes
                .filter({ $0.activationState == .foregroundActive })
                .compactMap({ $0 as? UIWindowScene })
                .first?.windows
                .filter({ $0.isKeyWindow }).first
        else {
            return nil
        }

        guard var topViewController = keyWindow.rootViewController else {
            return nil
        }

        while let presentedViewController = topViewController.presentedViewController {
            topViewController = presentedViewController
        }
        return topViewController
    }
}
