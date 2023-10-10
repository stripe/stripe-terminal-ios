//
//  CancelableViewController.swift
//  Example
//
//  Created by Brian Cooke on 4/19/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import UIKit
import StripeTerminal

// Used to control whether swiping to dismiss is allowed independent of the state of the cancel button
// Used in `CancelableViewController`s `setAllowedCancelMethods`.
//
// Example usage is after installing an update the Cancel button is disabled (done is enabled) but you can still swipe
// to dismiss the view controller.
struct CancelableMethods: OptionSet {
    let rawValue: Int

    static let button   = CancelableMethods(rawValue: 1 << 0)
    static let swipe    = CancelableMethods(rawValue: 1 << 1)

    static let all: CancelableMethods = [.swipe, .button]
}

// Implement this on view controllers that host a cancelable. `ReaderViewController` checks for this when a
// view controller is dismissed and will call cancel. This is used as a way to handle swipe to dismiss.
protocol CancelableViewController: UIViewController {
    var cancelable: Cancelable? { get }
    var cancelButton: UIBarButtonItem? { get }

    func cancel(errorBlock: @escaping (Error) -> Void)
    func setAllowedCancelMethods(_ allowedMethods: CancelableMethods)
}

extension CancelableViewController {
    func cancel(errorBlock: @escaping (Error) -> Void) {
        guard let cancelable = cancelable,
            cancelable.completed == false else {
                return
        }
        // Dismissed without canceling, cancel it now to make sure we cleanup.
        cancelable.cancel({ error in
            guard let error = error else {
                return
            }
            errorBlock(error)
        })
    }

    func setAllowedCancelMethods(_ allowedMethods: CancelableMethods) {
        self.isModalInPresentation = !(allowedMethods.contains(.swipe))
        cancelButton?.isEnabled = allowedMethods.contains(.button)
    }
}

// Implement on a view controller and call `didDismiss` from `presentationControllerDidDismiss`.
protocol CancelingViewController: UIAdaptivePresentationControllerDelegate {}

extension CancelingViewController where Self: UIViewController {
    func performCancel(presentationController: UIPresentationController) {
        guard let presentedNavController = presentationController.presentedViewController as? UINavigationController,
            let cancelableVC = presentedNavController.viewControllers.first as? CancelableViewController else {
                return
        }

        cancelableVC.cancel { [weak self] error in
            guard let self = self else {
                return
            }
            self.presentAlert(title: "Error Canceling After Dismiss", message: error.localizedDescription)
        }
    }
}
