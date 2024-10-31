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
    private var allowRedisplay: AllowRedisplay = AllowRedisplay.always
    private var moto = false
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
                .setPaymentMethodTypes([PaymentMethodType.card, PaymentMethodType.cardPresent])
                .build()
            let setupIntentConfig = try SetupIntentConfigurationBuilder()
                .setEnableCustomerCancellation(enableCustomerCancellation)
                .setMoto(moto)
                .build()
            let vc = SetupIntentViewController(setupParams: setupIntentParams, setupConfig: setupIntentConfig, allowRedisplay: allowRedisplay)
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
        var rows = [
            Row(text: "Allow Redisplay", accessory: .segmentedControl(
                items: ["always", "limited", "unspecified"], selectedIndex: 0) { [unowned self] newIndex, _ in
                    switch newIndex {
                    case 0: self.allowRedisplay = AllowRedisplay.always
                    case 1: self.allowRedisplay = AllowRedisplay.limited
                    case 2: self.allowRedisplay = AllowRedisplay.unspecified
                    default:
                        fatalError("Unknown option selected")
                    }
                }
            )
        ]
        if self.isSposReader {
            rows.append(Row(text: "Customer cancellation", accessory: .switchToggle(value: self.enableCustomerCancellation) { [unowned self] _ in
                self.enableCustomerCancellation.toggle()
                self.updateContent()
            }))
            rows.append(Row(text: "Mail Order / Telephone Order", accessory: .switchToggle(value: moto, { [unowned self] _ in
                self.moto.toggle()
                self.updateContent()
            })))
        }
        return Section(header: "TRANSACTION_FEATURES", rows: rows)
    }
}
