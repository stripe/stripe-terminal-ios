//
//  UpdateEnvironmentViewController.swift
//  Example
//
//  Created by Ben Guo on 9/29/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import Foundation
import StripeTerminal
import Static

class UpdateEnvironmentViewController: TableViewController {

    var onSelectedEnvironment: (UpdateReaderSoftwareEnvironment) -> () = { _ in }
    let environment: UpdateReaderSoftwareEnvironment

    init(environment: UpdateReaderSoftwareEnvironment) {
        self.environment = environment
        super.init(style: .grouped)
        title = "Environment"
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        updateContent()
    }

    private func updateContent() {
        dataSource.sections = [
            Section(header: "", rows: [
                Row(text: "Production", selection: { [unowned self] in
                    self.onSelectedEnvironment(.production)
                    self.navigationController?.popViewController(animated: true)
                    }, accessory: (environment == .production ? .checkmark : .none)),
                ], footer: "The production update environment. Use this environment if you received your reader as part of the Stripe Terminal Beta program."),
            Section(header: "", rows: [
                Row(text: "Test", selection: { [unowned self] in
                    self.onSelectedEnvironment(.test)
                    self.navigationController?.popViewController(animated: true)
                    }, accessory: (environment == .test ? .checkmark : .none)),
                ], footer: "The test update environment. If you received readers as part of the Stripe Terminal alpha program, you may need to use this environment in order to update your reader.\n\nIf this is the case, please contact your account manager to arrange exchanging this test device."),
        ]
    }

}
