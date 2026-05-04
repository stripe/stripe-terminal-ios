//
//  StartTapToPayAccountLinkedViewController.swift
//  Example
//
//  Created by Jamie Rollison on 3/27/26.
//  Copyright © 2026 Stripe. All rights reserved.
//

import Static
import StripeTerminal
import UIKit

class StartTapToPayAccountLinkedViewController: TableViewController {

    private let onBehalfOfView = TextFieldView(placeholderText: "On Behalf Of (optional)")

    init() {
        super.init(style: .grouped)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()
        title = "Check TTP Account Linked"

        onBehalfOfView.textField.autocorrectionType = .no
        onBehalfOfView.textField.autocapitalizationType = .none
        onBehalfOfView.textField.delegate = self
        onBehalfOfView.textField.clearButtonMode = .whileEditing

        updateContent()
    }

    private func updateContent() {
        let onBehalfOfSection = Section(
            header: "ON BEHALF OF",
            rows: [],
            footer: Section.Extremity.autoLayoutView(onBehalfOfView)
        )

        let checkSection = Section(
            header: "",
            rows: [
                Row(
                    text: "Check",
                    selection: { [unowned self] in
                        self.startCheck()
                    },
                    cellClass: ButtonCell.self
                )
            ]
        )

        dataSource.sections = [onBehalfOfSection, checkSection]
    }

    private func startCheck() {
        let onBehalfOf =
            onBehalfOfView.textField.text?.isEmpty == false
            ? onBehalfOfView.textField.text
            : nil
        if #available(iOS 16.4, *) {
            let vc = TapToPayAccountLinkedViewController(onBehalfOf: onBehalfOf)
            let navController = LargeTitleNavigationController(rootViewController: vc)
            present(navController, animated: true, completion: nil)
        } else {
            presentAlert(
                title: "Unsupported",
                message: "isTapToPayAccountLinked requires iOS 16.4 or later."
            )
        }
    }
}

extension StartTapToPayAccountLinkedViewController: UITextFieldDelegate {
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
    }
}
