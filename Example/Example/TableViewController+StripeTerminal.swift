//
//  TableViewController+StripeTerminal.swift
//  Terminal
//
//  Created by Catriona Scott on 4/16/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import Foundation
import Static
import UIKit

extension TableViewController {
    func addKeyboardDisplayObservers() {
        NotificationCenter.default.addObserver(
            self,
            selector: #selector(keyboardWillShow(notification:)),
            name: UIResponder.keyboardWillShowNotification,
            object: nil
        )

        NotificationCenter.default.addObserver(
            self,
            selector: #selector(keyboardWillHide(notification:)),
            name: UIResponder.keyboardWillHideNotification,
            object: nil
        )
    }

    @objc
    private func keyboardWillShow(notification: NSNotification) {
        if let keyboardSize = (notification.userInfo?[UIResponder.keyboardFrameEndUserInfoKey] as? NSValue)?.cgRectValue
        {
            tableView.contentInset = UIEdgeInsets(top: 0, left: 0, bottom: keyboardSize.height, right: 0)
        }
    }

    @objc
    private func keyboardWillHide(notification: NSNotification) {
        tableView.contentInset = .zero
    }
}

extension Row.Accessory {
    /// A segmented control whose visible selection persists across cell reuse.
    ///
    /// The built-in `.segmentedControl` accessory builds a fresh control from its initial
    /// `selectedIndex` every time a cell is configured, so scrolling a row off-screen and
    /// back resets the visible selection to the default even though the underlying value is
    /// unchanged (TERMINAL-56817). Wrapping a single retained `SegmentedControlAccessory` in
    /// `.view` keeps the same control instance across reconfiguration, preserving the user's
    /// selection.
    static func persistentSegmentedControl(
        items: [Any],
        selectedIndex: Int,
        _ valueChange: @escaping SegmentedControlValueChange
    ) -> Row.Accessory {
        .view(SegmentedControlAccessory(items: items, selectedIndex: selectedIndex, valueChange: valueChange))
    }
}
