//
//  StartSetupIntentViewController.swift
//  Example
//
//  Created by Michael Shafrir on 8/28/23.
//  Copyright © 2023 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class StartSetupIntentViewController: TableViewController {
    private let isSposReader: Bool
    private var enableCustomerCancellation: Bool = false

    private var startSection: Section?

    init(isSposReader: Bool) {
        self.isSposReader = isSposReader
        super.init(style: .grouped)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()
        title = "Collect SetupIntent"

        self.startSection = Section(rows: [
            Row(text: "Collect SetupIntent", selection: { [unowned self] in
                self.startSetupIntent()
            }, cellClass: ButtonCell.self),
        ])

        updateContent()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        // pop if no reader is connected
        guard Terminal.shared.connectedReader != nil else {
            navigationController?.popViewController(animated: true)
            return
        }
    }

    internal func startSetupIntent() {
        do {
            let setupIntentParams = try SetupIntentParametersBuilder()
                .build()
            let setupIntentConfig = try SetupIntentConfigurationBuilder()
                .setEnableCustomerCancellation(enableCustomerCancellation)
                .build()
            let vc = SetupIntentViewController(setupParams: setupIntentParams, setupConfig: setupIntentConfig)
            let navController = LargeTitleNavigationController(rootViewController: vc)
            self.present(navController, animated: true, completion: nil)
        } catch {
            self.presentAlert(error: error)
        }
    }

    private func updateContent() {
        var sections: [Section] = [
            makeTransactionSection()
        ].compactMap { $0 }

        if let startSection = self.startSection {
            sections.append(startSection)
        }

        dataSource.sections = sections
    }

    private func makeTransactionSection() -> Section? {
        if self.isSposReader {
            return Section(
                header: "TRANSACTION FEATURES",
                rows: [Row(text: "Customer cancellation", accessory: .switchToggle(value: self.enableCustomerCancellation) { [unowned self] _ in
                    self.enableCustomerCancellation.toggle()
                    self.updateContent()
                })])
        } else {
            return nil
        }
    }
}
