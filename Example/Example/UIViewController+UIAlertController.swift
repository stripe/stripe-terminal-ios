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
        return isViewLoaded &&
            view.window != nil &&
            presentedViewController == nil &&
            !isBeingDismissed &&
            !isMovingToParent
    }

    /**
     Requests a value by presenting an action sheet with the given options.
     If "Cancel" is selected, `handler` will be called with `currentValue`.
     */
    func presentValuePicker<T>(title: String?, options: [T], from sourceView: UIView?, handler: @escaping (T?)->()) where T: CustomStringConvertible {
        guard canPresentViewController() else { return }

        let alertController = UIAlertController(title: title, message: nil, preferredStyle: .actionSheet)
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
     Requests a value by presenting an alert view with a text field.
     `handler` may be called with nil if the entered text can't converted back
     to the original type. If "Cancel" is selected, `handler` will be called 
     with `currentValue`.
     TODO: try to remove currentValue in swift 4
     */
    func presentValueInput<T>(title: String?, currentValue: T, handler: @escaping (T?)->()) where T: LosslessStringConvertible {
        guard canPresentViewController() else { return }

        // need an instance of T to check its type
        let value = T("0")
        let alertController = UIAlertController(title: title, message: nil, preferredStyle: .alert)
        alertController.addTextField { textField in
            if value is Int || value is UInt {
                textField.keyboardType = .numberPad
            }
            else if value is Float || value is Double || value is CGFloat {
                textField.keyboardType = .decimalPad
            }
        }
        let okAction = UIAlertAction(title: "OK", style: .default) { _ in
            guard let text = alertController.textFields?.first?.text else {
                handler(nil)
                return
            }
            handler(T(text))
        }
        alertController.addAction(okAction)
        let cancelAction = UIAlertAction(title: "Cancel", style: .cancel, handler: { _ in
            handler(nil)
        })
        alertController.addAction(cancelAction)
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
    func presentAlert(error: Error, handler: @escaping (Bool) -> ()) {
        presentAlert(title: "Error", message: error.localizedDescription, handler: handler)
    }

    /**
     Presents the given title and message using an alert view.
     */
    func presentAlert(title: String, message: String) {
        guard canPresentViewController() else { return }

        let alertController = UIAlertController(title: title, message: message, preferredStyle: .alert)
        let okAction = UIAlertAction(title: "OK", style: .default) { _ in }
        alertController.addAction(okAction)
        present(alertController, animated: true, completion: nil)
    }

    /**
     Presents the given title and message using an alert view with OK and cancel buttons.
     */
    func presentAlert(title: String, message: String, okButtonTitle: String? = nil, handler: @escaping (Bool) -> ()) {
        guard canPresentViewController() else { return }

        let alertController = UIAlertController(title: title, message: message, preferredStyle: .alert)
        let okAction = UIAlertAction(title: okButtonTitle ?? "OK", style: .default) { _ in
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
