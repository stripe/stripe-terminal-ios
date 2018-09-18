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

class DeviceTypeViewController: TableViewController, TerminalDelegate {

    var onSelectedDevice: (DeviceType) -> () = { _ in }
    let deviceType: DeviceType

    init(selectedDeviceType: DeviceType) {
        deviceType = selectedDeviceType
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
                Row(text: "Reader Simulator", selection: { [unowned self] in
                    self.onSelectedDevice(.readerSimulator)
                    self.navigationController?.popViewController(animated: true)
                    }, accessory: (deviceType == .readerSimulator ? .checkmark : .none)),
                ], footer: "Discover a simulated reader provided by the Stripe Terminal SDK. Select this option to try out the SDK without connecting to a physical reader."),
            Section(header: "", rows: [
                Row(text: "Chipper 2X", selection: { [unowned self] in
                    self.onSelectedDevice(.chipper2X)
                    self.navigationController?.popViewController(animated: true)
                }, accessory: (deviceType == .chipper2X ? .checkmark : .none)),
                ], footer: "Discover card readers by scanning for nearby bluetooth devices. \n\nNote: the Stripe Terminal SDK can discover supported card readers automatically – you don't need to connect to the reader in the system Settings > Bluetooth page."),
        ]
    }

}
