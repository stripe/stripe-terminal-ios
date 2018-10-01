//
//  ReaderDiscoveryViewController.swift
//  Dev
//
//  Created by Ben Guo on 7/18/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class ReaderDiscoveryViewController: TableViewController, DiscoveryDelegate {

    var onConnectedToReader: (Reader) -> () = { _ in }
    private let terminal: Terminal
    private let config: DiscoveryConfiguration
    private var discoverCancelable: Cancelable? = nil
    private weak var cancelButton: UIBarButtonItem?
    private let activityIndicatorView = ActivityIndicatorHeaderView(title: "NEARBY READERS")

    init(terminal: Terminal, discoveryConfig: DiscoveryConfiguration) {
        self.terminal = terminal
        self.config = discoveryConfig
        super.init(style: .grouped)
        self.title = "Discovery"
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        let cancelButton = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(dismissAction))
        self.cancelButton = cancelButton
        navigationItem.leftBarButtonItem = cancelButton

        updateContent(readers: [])
        activityIndicatorView.activityIndicator.startAnimating()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        // 1. discover readers
        discoverCancelable = terminal.discoverReaders(config, delegate: self) { error in
            if let error = error {
                print("discoverReaders failed: \(error)")
                self.presentAlert(error: error) { _ in
                    self.dismiss(animated: true, completion: nil)
                }
            }
        }
    }

    private func updateContent(readers: [Reader]) {
        let rows = readers.map { reader in
            Row(text: reader.serialNumber, selection: { [unowned self] in
                self.connect(to: reader)
            })
        }
        dataSource.sections = [
            Section(header: Section.Extremity.view(activityIndicatorView),
                    rows: rows)
        ]
    }

    // 2. connect to a selected reader
    private func connect(to reader: Reader) {
        self.terminal.connectReader(reader) { reader, error in
            if let reader = reader {
                self.onConnectedToReader(reader)
            }
            else if let error = error {
                self.presentAlert(error: error)
                self.discoverCancelable = nil
            }
        }
    }

    @objc func dismissAction() {
        if let cancelable = discoverCancelable {
            cancelable.cancel { error in
                if let error = error {
                    print("cancel discoverReaders failed: \(error)")
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

    // MARK: SCPDiscoveryDelegate
    func terminal(_ terminal: Terminal, didUpdateDiscoveredReaders readers: [Reader]) {
        updateContent(readers: readers)
    }
}


