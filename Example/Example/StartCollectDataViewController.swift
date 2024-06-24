//
//  StartCollectDataViewController.swift
//  Example
//
//  Created by Mindy Lou on 5/9/24.
//  Copyright © 2024 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class StartCollectDataViewController: TableViewController {

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

    internal func startCollectMagstripeData() {
        do {
            let collectDataConfig = try CollectDataConfigurationBuilder().setCollectDataType(.magstripe).build()
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
            Row(text: "Collect magstripe data", selection: { [unowned self] in
                startCollectMagstripeData()
            }, cellClass: ButtonCell.self),
        ])

        sections.append(dataCollectionForms)
        dataSource.sections = sections
    }
}
