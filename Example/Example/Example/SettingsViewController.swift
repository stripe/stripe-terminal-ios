//
//  SettingsViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 2/6/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import StripePOS

class SettingsViewController: StackViewController, SCPUpdateReaderDelegate {

    weak var terminal: SCPTerminal?

    let batteryView = MeterView(title: "Battery Level", color: UIColor.stripeGreen)
    let updateProgressView = MeterView(title: "Update Progress")
    let updateReaderButton = ColoredButton(title: "Update Reader", color: UIColor.stripeBlue)

    override func viewDidLoad() {
        super.viewDidLoad()

        updateReaderButton.onTap = {
            if let terminal = self.terminal {
                terminal.updateReader(self) { error in
                    if let error = error {
                        self.presentAlert(error: error)
                    }
                }
            }
        }
        stack = [
            [batteryView],
            [updateProgressView],
            [updateReaderButton],
            [UIView()],
        ]
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)

        if let reader = self.terminal?.connectedReader {
            batteryView.value = reader.batteryLevel
        }
    }

    // MARK: SCPUpdateReaderDelegate
    func terminal(_ terminal: SCPTerminal, readerUpdateAvailable readerUpdate: SCPReaderUpdate, installUpdate: @escaping SCPBoolCompletionBlock) {
        presentAlert(title: "Update available", message: readerUpdate.estimatedUpdateTime.description) { response in
            installUpdate(response)
        }
    }

    func terminal(_ terminal: SCPTerminal, didReportReaderUpdateProgress updateProgress: Float) {
        updateProgressView.value = updateProgress
    }

    func terminal(_ terminal: SCPTerminal, didCompleteReaderUpdate error: Error?) {
        if let error = error {
            print("Update reader failed: \(error)")
            presentAlert(error: error)
        }
        else {
            presentAlert(title: "Update succeeded", message: "")
        }
        updateProgressView.value = 0
    }

}
