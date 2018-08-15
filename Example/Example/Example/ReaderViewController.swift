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

class ReaderViewController: StackViewController, SCPTerminalDelegate, SCPDiscoveryDelegate {

    weak var terminal: SCPTerminal? {
        didSet {
            updateViews()
        }
    }

    var lastConnectedSerial: String?
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
        switch connectionStatus {
        case .busy:
            break
        case .connected:
            self.lastConnectedSerial = terminal.connectedReader?.serialNumber
            break
        case .notConnected:
            // attempt to re-connect to the last connected reader
            let config = SCPDiscoveryConfiguration()
            self.terminal?.discover(config, delegate: self) { error in
                if let error = error {
                    print("reconnect discover failed: \(error)")
                }
                else {
                    print("reconnect discover succeeded")
                }
            }
        }
        updateViews()
    }

    func terminalDidReportLowBatteryWarning(_ terminal: SCPTerminal) {
        self.showNotification(title: "Reader battery is low")
    }

    // MARK: SCPDiscoveryDelegate
    // Note: we call discover from this view controller when SCPTerminal's
    // connectionStatus changes to .notConnected (see above)
    func terminal(_ terminal: SCPTerminal, didUpdateDiscoveryResults readers: [SCPReader]) {
        guard let serial = lastConnectedSerial else { return }
        for reader in readers {
            if reader.serialNumber == serial {
                terminal.connect(reader) { reader, error in
                    if let error = error {
                        print("reconnect failed: \(error)")
                    }
                    else {
                        print("reconnect succeeded")
                    }
                }
            }
        }
    }

}
