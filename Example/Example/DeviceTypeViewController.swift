//
//  DeviceTypeViewController.swift
//  Example
//
//  Created by Ben Guo on 9/13/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import Foundation
import StripeTerminal
import Static

class DeviceTypeViewController: TableViewController {

    var onSelectedDevice: (DeviceType) -> () = { _ in }
    let deviceType: DeviceType

    init(deviceType: DeviceType) {
        self.deviceType = deviceType
        super.init(style: .grouped)
        title = "Device Type"
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
                Row(text: "Chipper 2X", selection: { [unowned self] in
                    self.onSelectedDevice(.chipper2X)
                    self.navigationController?.popViewController(animated: true)
                }, accessory: (deviceType == .chipper2X ? .checkmark : .none)),
                ], footer: "Discover the BBPOS Chipper 2X BT.\n\nNote: the Stripe Terminal SDK can discover supported card readers automatically – you don't need to connect to the reader in the iOS Settings > Bluetooth page."),
            Section(header: "", rows: [
                Row(text: "Verifone P400", selection: { [unowned self] in
                    self.onSelectedDevice(.verifoneP400)
                    self.navigationController?.popViewController(animated: true)
                    }, accessory: (deviceType == .verifoneP400 ? .checkmark : .none)),
                ], footer: "Discover the Verifone P400.\n\nNote: Readers must be registered to your account via the Stripe API or Dashboard before they're discoverable."),
        ]
    }

}
