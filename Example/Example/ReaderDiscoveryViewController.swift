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
    private let config: DiscoveryConfiguration
    private var discoverCancelable: Cancelable? = nil
    private weak var cancelButton: UIBarButtonItem?
    private let activityIndicatorView = ActivityIndicatorHeaderView(title: "HOLD READER NEARBY")

    init(discoveryConfig: DiscoveryConfiguration) {
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
        discoverCancelable = Terminal.shared.discoverReaders(config, delegate: self) { error in
            if let error = error {
                print("discoverReaders failed: \(error)")
                self.presentAlert(error: error) { _ in
                    self.dismiss(animated: true, completion: nil)
                }
            }
            self.discoverCancelable = nil;
        }
    }

    private func updateContent(readers: [Reader]) {
        if readers.count == 0 {
            switch (self.config.method) {
            case .bluetoothProximity:
                activityIndicatorView.title = "HOLD READER NEARBY"
                break
            case .bluetoothScan:
                activityIndicatorView.title = "NEARBY READERS"
                break
            }
            dataSource.sections = [
                Section(header: Section.Extremity.view(activityIndicatorView),
                        rows: [])
            ]
        }
        else {
            switch (self.config.method) {
            case .bluetoothProximity:
                activityIndicatorView.title = "DISCOVERED READER"
                break
            case .bluetoothScan:
                activityIndicatorView.title = "NEARBY READERS"
                break
            }
            let rows = readers.map { reader -> Row in
                if let battery = reader.batteryLevel {
                    let detailText = "🔋 \(abs(battery.floatValue*100))%"
                    return Row(text: reader.serialNumber, detailText: detailText, selection: { [unowned self] in
                        self.connect(to: reader)
                    })
                }
                else {
                    return Row(text: reader.serialNumber, selection: { [unowned self] in
                        self.connect(to: reader)
                    })
                }
            }
            let footer: Section.Extremity?
            if let softwareVersion = readers.first?.deviceSoftwareVersion {
                footer = Section.Extremity.title("Reader software: \(softwareVersion)")
            }
            else {
                footer = nil
            }
            dataSource.sections = [
                Section(header: Section.Extremity.view(activityIndicatorView),
                        rows: rows,
                        footer: footer)
            ]
        }
    }

    // 2. connect to a selected reader
    private func connect(to reader: Reader) {
        Terminal.shared.connectReader(reader) { reader, error in
            if let reader = reader {
                self.discoverCancelable = nil
                self.onConnectedToReader(reader)
            }
            else if let error = error {
                self.presentAlert(error: error)
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
                self.discoverCancelable = nil
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


