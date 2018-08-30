//
//  ReaderDiscoveryViewController.swift
//  Dev
//
//  Created by Ben Guo on 7/18/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import StripePOS
import ExternalAccessory

class ReaderDiscoveryViewController: UpdatingResultsViewController<SCPReader>, SCPDiscoveryDelegate {

    var onConnect: (SCPReader) -> () = { _ in }
    var discoverCancelable: SCPCancelable? = nil {
        didSet {
            let switchTitle = (discoverCancelable != nil) ? "Stop" : "Start"
            self.discoverSwitch?.title = switchTitle
        }
    }

    init(configuration: SCPDiscoveryConfiguration, terminal: SCPTerminal) {
        self.configuration = configuration
        self.terminal = terminal
        super.init(title: "Nearby Readers")
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    private let terminal: SCPTerminal
    private let configuration: SCPDiscoveryConfiguration
    private weak var cancelButton: UIBarButtonItem?
    private weak var discoverSwitch: UIBarButtonItem?
    private weak var timeoutButton: UIBarButtonItem?

    override func viewDidLoad() {
        super.viewDidLoad()
        let cancelButton = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(dismissAction))
        self.cancelButton = cancelButton
        let discoverSwitch = UIBarButtonItem(title: "Stop", style: .plain, target: self, action: #selector(discoverSwitchAction))
        self.discoverSwitch = discoverSwitch
        let timeoutButton = UIBarButtonItem(title: "Timeout: None", style: .plain, target: self, action: #selector(timeoutButtonAction))
        self.timeoutButton = timeoutButton;
        navigationItem.leftBarButtonItem = cancelButton
        navigationItem.rightBarButtonItem = discoverSwitch
        navigationController?.isToolbarHidden = false
        setToolbarItems([timeoutButton], animated: false)

        onSelectResult = { reader in
            self.terminal.connect(reader) { reader, error in
                if let reader = reader {
                    self.onConnect(reader)
                }
                else if let error = error {
                    self.presentAlert(error: error)
                    self.discoverCancelable = nil
                }
            }
        }
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        self.discoverCancelable = terminal.discoverReaders(self.configuration, delegate: self) { error in
            if let error = error {
                self.presentAlert(error: error)
            }
        }
    }

    @objc func discoverSwitchAction() {
        if let cancelable = discoverCancelable {
            cancelable.cancel { error in
                if let error = error {
                    self.presentAlert(error: error)
                    self.discoverCancelable = nil
                }
            }
        }
        else {
            self.discoverCancelable = terminal.discoverReaders(self.configuration, delegate: self) { error in
                if let error = error {
                    self.presentAlert(error: error)
                    self.discoverCancelable = nil
                }
            }
        }
    }

    @objc func dismissAction() {
        if let cancelable = discoverCancelable {
            cancelable.cancel { error in
                if let error = error {
                    self.presentAlert(error: error)
                }
                else {
                    self.dismiss(animated: true, completion: nil)
                }
            }
        }
        else {
            dismiss(animated: true, completion: nil)
        }
    }

    @objc func timeoutButtonAction() {
        presentValueInput(title: "Timeout", currentValue: configuration.timeout) { value in
            if let value = value {
                self.configuration.timeout = value
                if value == 0 {
                    self.timeoutButton?.title = "Timeout: None"
                }
                else {
                    self.timeoutButton?.title = "Timeout: \(value)s"
                }
            }
        }
    }

    // MARK: SCPDiscoveryDelegate
    func terminal(_ terminal: SCPTerminal, didUpdateDiscoveredReaders readers: [SCPReader]) {
        self.results = readers
    }

}
