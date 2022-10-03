//
//  UIViewController+UIAlertController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/7/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit

extension UIViewController {

    private func canPresentViewController() -> Bool {
        return isViewLoaded
            && view.window != nil
            && presentedViewController == nil
            && !isBeingDismissed
            && !isMovingToParent
    }

    private func canPresentAlert() -> Bool {
        return isViewLoaded
            && view.window != nil
            && presentedViewController == nil
            && !isBeingDismissed
    }

    /**
     Requests a value by presenting an action sheet with the given options.
     If "Cancel" is selected, `handler` will be called with nil.
     */
    func presentValuePicker<T>(title: String? = nil, options: [T], from sourceView: UIView? = nil, handler: @escaping (T?) -> Void) where T: CustomStringConvertible {
        guard canPresentViewController() else { return }

        let alertController = UIAlertController(title: title, message: nil, preferredStyle: sourceView == nil ? .alert : .actionSheet)
        for opt in options {
            let action = UIAlertAction(title: opt.description, style: .default, handler: { _ in
                handler(opt)
            })
            alertController.addAction(action)
        }
        let cancelAction = UIAlertAction(title: "Cancel", style: .cancel, handler: { _ in
            handler(nil)
        })
        alertController.addAction(cancelAction)
        alertController.popoverPresentationController?.sourceView = sourceView
        alertController.popoverPresentationController?.sourceRect = sourceView?.bounds ?? .zero
        present(alertController, animated: true, completion: nil)
    }

    /**
     Presents the given error using an alert view.
     */
    func presentAlert(error: Error) {
        presentAlert(title: "Error", message: error.localizedDescription)
    }

    /**
     Presents the given error using an alert view, with a handler.
     */
    func presentAlert(error: Error, handler: @escaping (Bool) -> Void) {
        presentAlert(title: "Error", message: error.localizedDescription, handler: handler)
    }

    /**
     Presents the given title and message using an alert view.
     */
    func presentAlert(title: String, message: String) {
        guard canPresentAlert() else {
            print("‼️ \(title)")
            print(message)
            print("Also, there was an error displaying this as an alert controller.")
            return
        }

        let alertController = UIAlertController(title: title, message: message, preferredStyle: .alert)
        let okAction = UIAlertAction(title: "OK", style: .default) { _ in }
        alertController.addAction(okAction)
        present(alertController, animated: true, completion: nil)
    }

    /**
     Presents the given title and message using an alert view with OK and cancel buttons.
     */
    func presentAlert(title: String, message: String, okButtonTitle: String = "OK", handler: @escaping (Bool) -> Void) {
        guard canPresentAlert() else {
            print("‼️ \(title)")
            print(message)
            print("Also, there was an error displaying this as an alert controller.")
            return
        }

        let alertController = UIAlertController(title: title, message: message, preferredStyle: .alert)
        let okAction = UIAlertAction(title: okButtonTitle, style: .default) { _ in
            handler(true)
        }
        let cancelAction = UIAlertAction(title: "Cancel", style: .cancel) { _ in
            handler(false)
        }
        alertController.addAction(okAction)
        alertController.addAction(cancelAction)
        present(alertController, animated: true, completion: nil)
    }

}
