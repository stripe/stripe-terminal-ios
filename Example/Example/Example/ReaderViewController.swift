//
//  ReaderViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/7/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit
import StripePOS

extension SCPReader {
    override open var description: String {
        return self.serialNumber
    }
}

class ReaderViewController: StackViewController, SCPTerminalDelegate {

    weak var terminal: SCPTerminal? {
        didSet {
            updateViews()
        }
    }

    let connectionView = StatusView<String>(title: "Connection Status", value: "")
    let discoverButton = ColoredButton(title: "Discover", color: UIColor.stripeGreen)
    let disconnectButton = ColoredButton(title: "Disconnect", color: UIColor.stripeRed)

    override func viewDidLoad() {
        super.viewDidLoad()

        discoverButton.onTap = {
            guard let terminal = self.terminal else { return }

            let config = SCPDiscoveryConfiguration()
            let discoveryVC = ReaderDiscoveryViewController(configuration: config, terminal: terminal)
            discoveryVC.onConnect = { reader in
                if let _ = discoveryVC.presentedViewController {
                    discoveryVC.dismiss(animated: true) {
                        discoveryVC.dismiss(animated: true) {
                            self.updateViews()
                        }
                    }
                }
                else {
                    discoveryVC.dismiss(animated: true) {
                        self.updateViews()
                    }
                }
            }
            let navController = UINavigationController(rootViewController: discoveryVC)
            self.present(navController, animated: true, completion: nil)
        }
        disconnectButton.onTap =  {
            self.terminal?.disconnect { error in
                if let error = error {
                    print("Disconnect failed: \(error)")
                    self.presentAlert(error: error)
                }
                else {
                    self.showNotification(title: "Disconnected")
                }
                self.updateViews()
            }
        }

        stack = [
            [connectionView],
            [discoverButton],
            [disconnectButton],
        ]
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        guard let terminal = self.terminal else { return }
        terminal.terminalDelegate = self

        updateViews()
    }

    func updateViews() {
        guard let terminal = self.terminal else { return }
        let status = terminal.connectionStatus
        switch status {
        case .notConnected, .busy:
            connectionView.value = SCPTerminal.string(from: status)
            break
        case .connected:
            if let serial = terminal.connectedReader?.serialNumber {
                connectionView.value = serial
            }
            else {
                // should not happen
                connectionView.value = "Connected"
            }
        }
    }

    // MARK: SCPTerminalDelegate
    func terminal(_ terminal: SCPTerminal, didChange connectionStatus: SCPConnectionStatus) {
        updateViews()
    }

    func terminalDidReportLowBatteryWarning(_ terminal: SCPTerminal) {
        self.showNotification(title: "Reader battery is low")
    }

}
