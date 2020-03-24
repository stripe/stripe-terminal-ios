//
//  DiscoveryMethodViewController.swift
//  Example
//
//  Created by Ben Guo on 9/13/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import Foundation
import StripeTerminal
import Static

class DiscoveryMethodViewController: TableViewController {
    
    var onSelectedMethod: (DiscoveryMethod) -> () = { _ in }
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
        updateContent()
    }
    
    private func updateContent() {
        dataSource.sections = [
            Section(header: "", rows: [
                Row(text: "Bluetooth Scan", selection: { [unowned self] in
                    self.onSelectedMethod(.bluetoothScan)
                    self.navigationController?.popViewController(animated: true)
                    }, accessory: (method == .bluetoothScan ? .checkmark : .none)),
                ], footer: "Discover a reader by scanning for Bluetooth LE devices."),
            Section(header: "", rows: [
                Row(text: "Bluetooth Proximity", selection: { [unowned self] in
                    self.onSelectedMethod(.bluetoothProximity)
                    self.navigationController?.popViewController(animated: true)
                    }, accessory: (method == .bluetoothProximity ? .checkmark : .none)),
                ], footer: "Discover a reader by holding it next to the iOS device.\n\nNote: the Stripe Terminal SDK can discover supported readers automatically – you should not connect to the reader in the iOS Settings > Bluetooth page."),
            Section(header: "", rows: [
                Row(text: "Internet", selection: { [unowned self] in
                    self.onSelectedMethod(.internet)
                    self.navigationController?.popViewController(animated: true)
                    }, accessory: (method == .internet ? .checkmark : .none)),
                ], footer: "Discovers readers that have been registered to your account via the Stripe API or Dashboard."),
        ]
    }
    
}
