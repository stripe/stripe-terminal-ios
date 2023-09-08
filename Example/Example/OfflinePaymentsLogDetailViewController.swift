//
//  OfflinePaymentsLogDetailViewController.swift
//  AppStore
//
//  Created by Mindy Lou on 7/15/22.
//  Copyright © 2022 Stripe. All rights reserved.
//

import Static

class OfflinePaymentsLogDetailViewController: TableViewController {

    private var string: String

    init(string: String) {
        self.string = string
        super.init(style: .plain)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        updateContent()
    }

    func updateContent() {
        dataSource.sections = [
            Section(rows: [
                Row(text: string, cellClass: Value1MultilineCell.self)
            ])
        ]
    }

}
