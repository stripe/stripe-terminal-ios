//
//  StartCollectDataViewController.swift
//  Example
//
//  Created by Mindy Lou on 5/9/24.
//  Copyright © 2024 Stripe. All rights reserved.
//

import Static
import StripeTerminal
import UIKit

class StartCollectDataViewController: TableViewController {

    private var enableCustomerCancellation = false

    convenience init() {
        self.init(style: .grouped)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        addKeyboardDisplayObservers()
        title = "Collect Data"

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

    private func startCollectData(type: CollectDataType) {
        do {
            let collectDataConfig = try CollectDataConfigurationBuilder().setCollectDataType(type)
                .setEnableCustomerCancellation(enableCustomerCancellation).build()
            let viewController = CollectDataViewController(collectDataConfiguration: collectDataConfig)
            let navigationController = LargeTitleNavigationController(rootViewController: viewController)
            present(navigationController, animated: true)
        } catch {
            presentAlert(error: error)
        }
    }

    private func updateContent() {
        var sections = [Section]()
        let dataCollectionForms = Section(rows: [
            Row(
                text: "Enable customer cancellation",
                accessory: .switchToggle(value: enableCustomerCancellation) { [unowned self] _ in
                    enableCustomerCancellation.toggle()
                    updateContent()
                }
            ),
            Row(
                text: "Collect magstripe data",
                selection: { [unowned self] in
                    startCollectData(type: .magstripe)
                },
                cellClass: ButtonCell.self
            ),
            Row(
                text: "Collect NFC UID",
                selection: { [unowned self] in
                    startCollectData(type: .nfcUid)
                },
                cellClass: ButtonCell.self
            ),
        ])

        sections.append(dataCollectionForms)
        dataSource.sections = sections
    }
}
