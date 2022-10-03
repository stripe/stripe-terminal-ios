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

    var onSelectedDevice: (DeviceType?) -> Void = { _ in }
    let deviceType: DeviceType?

    init(deviceType: DeviceType?) {
        self.deviceType = deviceType
        super.init(style: .grouped)
        title = "Device Type"
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()
        updateContent()
    }

    private func vendDeviceRow(label: String, deviceType: DeviceType?) -> Row {
        return Row(
            text: label,
            selection: { [unowned self] in
                self.onSelectedDevice(deviceType)
                self.navigationController?.popViewController(animated: true)
            },
            accessory: (self.deviceType == deviceType ? .checkmark : .none)
        )
    }

    private func updateContent() {
        dataSource.sections = [
            Section(rows: [
                vendDeviceRow(label: "Unspecified", deviceType: nil),
            ], footer: "The Stripe Terminal iOS SDK can discover multiple device types at once. Select the \"Unspecified\" option to discover all readers available with the current discovery method."),

            Section(header: "Mobile Readers", rows: [
                vendDeviceRow(label: "Chipper 2X", deviceType: .chipper2X),
                vendDeviceRow(label: "WisePad 3", deviceType: .wisePad3),
            ], footer: "The Stripe Terminal SDK can discover supported Bluetooth card readers automatically – you don't need to connect to the reader in the iOS Settings > Bluetooth page."),

            Section(header: "Countertop Readers", rows: [
                vendDeviceRow(label: "Verifone P400", deviceType: .verifoneP400),
                vendDeviceRow(label: "WisePOS E", deviceType: .wisePosE),
                vendDeviceRow(label: "S7", deviceType: .stripeS700),
            ], footer: "Countertop readers must be registered to your account via the Stripe API or Dashboard before they're discoverable."),
        ]
    }

}
