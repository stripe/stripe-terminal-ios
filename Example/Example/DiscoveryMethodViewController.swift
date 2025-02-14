//
//  DiscoveryMethodViewController.swift
//  Example
//
//  Created by Ben Guo on 9/13/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import Foundation
import Static
import StripeTerminal

class DiscoveryMethodViewController: TableViewController {

    var onSelectedMethod: (DiscoveryMethod) -> Void = { _ in }
    let method: DiscoveryMethod

    init(method: DiscoveryMethod) {
        self.method = method
        super.init(style: .grouped)
        title = "Discovery Method"
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()
        updateContent()
    }

    private func updateContent() {
        dataSource.sections = [
            Section(
                header: "",
                rows: [
                    Row(
                        text: DiscoveryMethod.bluetoothScan.description,
                        selection: { [unowned self] in
                            self.onSelectedMethod(.bluetoothScan)
                            self.navigationController?.popViewController(animated: true)
                        },
                        accessory: (method == .bluetoothScan ? .checkmark : .none)
                    )
                ],
                footer: "Discover a reader by scanning for Bluetooth LE devices."
            ),
            Section(
                header: "",
                rows: [
                    Row(
                        text: DiscoveryMethod.bluetoothProximity.description,
                        selection: { [unowned self] in
                            self.onSelectedMethod(.bluetoothProximity)
                            self.navigationController?.popViewController(animated: true)
                        },
                        accessory: (method == .bluetoothProximity ? .checkmark : .none)
                    )
                ],
                footer:
                    "Discover a reader by holding it next to the iOS device (only supported for the BBPOS Chipper 2X BT and Stripe M2).\n\nNote: the Stripe Terminal SDK can discover supported readers automatically – you should not connect to the reader in the iOS Settings > Bluetooth page."
            ),
            Section(
                header: "",
                rows: [
                    Row(
                        text: DiscoveryMethod.internet.description,
                        selection: { [unowned self] in
                            self.onSelectedMethod(.internet)
                            self.navigationController?.popViewController(animated: true)
                        },
                        accessory: (method == .internet ? .checkmark : .none)
                    )
                ],
                footer: "Discovers readers that have been registered to your account via the Stripe API or Dashboard."
            ),
            Section(
                header: "",
                rows: [
                    Row(
                        text: DiscoveryMethod.tapToPay.description,
                        selection: { [unowned self] in
                            self.onSelectedMethod(.tapToPay)
                            self.navigationController?.popViewController(animated: true)
                        },
                        accessory: (method == .tapToPay ? .checkmark : .none)
                    )
                ],
                footer: "Discovers readers local to this mobile device."
            ),
            Section(
                header: "",
                rows: [
                    Row(
                        text: DiscoveryMethod.usb.description,
                        selection: { [unowned self] in
                            self.onSelectedMethod(.usb)
                            self.navigationController?.popViewController(animated: true)
                        },
                        accessory: (method == .usb ? .checkmark : .none)
                    )
                ],
                footer: "Discovers readers connected over USB."
            ),
        ]
    }

}
