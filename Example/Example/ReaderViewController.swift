//
//  ReaderViewController.swift
//  Example
//
//  Created by Ben Guo on 9/6/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class ReaderViewController: TableViewController, TerminalDelegate {

    private var connectedReader: Reader? = nil {
        didSet {
            headerView.connectedReader = connectedReader
            updateContent()
        }
    }
    
    static var readerConfiguration = ReaderConfiguration() {
        didSet {
            _ = ReaderViewController.readerConfiguration.saveToUserDefaults()
        }
    }

    private let headerView = ReaderHeaderView()

    init() {
        super.init(style: .grouped)
        self.title = "Terminal"
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        ReaderViewController.readerConfiguration = ReaderConfiguration.loadFromUserDefaults()
        updateContent()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        Terminal.shared.delegate = self
        connectedReader = Terminal.shared.connectedReader
        headerView.connectionStatus = Terminal.shared.connectionStatus
        updateContent()
    }

    // MARK: - Private

    private func showDiscoverReaders() {
        let simulated = ReaderViewController.readerConfiguration.deviceType != .wisePad3 ? ReaderViewController.readerConfiguration.simulated : false
        let config = DiscoveryConfiguration(deviceType: ReaderViewController.readerConfiguration.deviceType,
                                            discoveryMethod: ReaderViewController.readerConfiguration.discoveryMethod,
                                            simulated: simulated)
        let discoveryVC = ReaderDiscoveryViewController(discoveryConfig: config)
        discoveryVC.onConnectedToReader = { [weak discoveryVC] reader in
            guard let discoveryVC = discoveryVC else { return }

            self.connectedReader = reader
            if let _ = discoveryVC.presentedViewController {
                discoveryVC.dismiss(animated: true) {
                    discoveryVC.dismiss(animated: true) {
                        self.updateContent()
                    }
                }
            } else {
                discoveryVC.dismiss(animated: true) {
                    self.updateContent()
                }
            }
        }
        let navController = LargeTitleNavigationController(rootViewController: discoveryVC)
        self.present(navController, animated: true, completion: nil)
    }

    private func disconnectFromReader() {
        Terminal.shared.disconnectReader { error in
            if let error = error {
                print("Disconnect failed: \(error)")
                self.presentAlert(error: error)
            } else {
                self.connectedReader = nil
                self.updateContent()
            }
        }
    }

    internal func showStartPayment() {
        let vc = StartPaymentViewController()
        self.navigationController?.pushViewController(vc, animated: true)
    }

    internal func showReadReusableCard() {
        if let connectReader = self.connectedReader, connectReader.deviceType != .chipper2X {
            self.presentAlert(title: "Error", message: "This device type does not support readReusableCard.")
            return
        }
        let vc = ReadReusableCardViewController()
        let navController = LargeTitleNavigationController(rootViewController: vc)
        self.present(navController, animated: true, completion: nil)
    }

    internal func showUpdateReader() {
        let vc = UpdateReaderViewController()
        let navController = LargeTitleNavigationController(rootViewController: vc)
        self.present(navController, animated: true, completion: nil)
    }

    internal func showDeviceTypes() {
        let vc = DeviceTypeViewController(deviceType: ReaderViewController.readerConfiguration.deviceType)
        vc.onSelectedDevice = { type in
            guard ReaderViewController.readerConfiguration.deviceType != type else { return }
            ReaderViewController.readerConfiguration.deviceType = type
            // for changed deviceType: update discovery method, since the previous selection is incompatible
            switch type {
            case .verifoneP400:
                ReaderViewController.readerConfiguration.discoveryMethod = .internet
            case .chipper2X:
                ReaderViewController.readerConfiguration.discoveryMethod = .bluetoothProximity // not bothering to see which they last used
            case .wisePad3:
                // Update this in future once we support both bluetooth methods.
                ReaderViewController.readerConfiguration.discoveryMethod = .bluetoothScan
            @unknown default:
                print("No discovery method so device types cannot be determined.")
            }

            self.updateContent()
        }
        self.navigationController?.pushViewController(vc, animated: true)
    }
    
    internal func showDiscoveryMethods() {
        let vc = DiscoveryMethodViewController(method: ReaderViewController.readerConfiguration.discoveryMethod)
        vc.onSelectedMethod = { method in
            guard ReaderViewController.readerConfiguration.discoveryMethod != method else { return }
            ReaderViewController.readerConfiguration.discoveryMethod = method
            // make sure deviceType is set to a compatible device for this discovery method
            switch method {
            case .bluetoothProximity, .bluetoothScan:
                ReaderViewController.readerConfiguration.deviceType = .chipper2X
            case .internet:
                ReaderViewController.readerConfiguration.deviceType = .verifoneP400
            @unknown default:
                print("No device type so discovery methodssg cannot be determined.")
            }
            self.updateContent()
        }
        self.navigationController?.pushViewController(vc, animated: true)
    }

    private func updateContent() {
        let rdrConnectionTitle = Section.Extremity.title("Reader Connection")
        if connectedReader == nil {
            dataSource.sections = [
                Section(header: "", rows: [], footer: Section.Extremity.view(headerView)),
                Section(header: rdrConnectionTitle, rows: [
                    Row(text: "Discover Readers", selection: { [unowned self] in
                        self.showDiscoverReaders()
                        }, cellClass: ButtonCell.self),
                    ]),
                Section(header: "Device Type", rows: [
                    Row(text: ReaderViewController.readerConfiguration.deviceType.description, selection: { [unowned self] in
                        self.showDeviceTypes()
                        }, accessory: .disclosureIndicator),
                    ]),
                Section(header: "Discovery Method", rows: [
                    Row(text: ReaderViewController.readerConfiguration.discoveryMethod.description, selection: { [unowned self] in
                        self.showDiscoveryMethods()
                        }, accessory: .disclosureIndicator),
                    ]),
                Section(header: "", rows: [
                    Row(text: "Simulated", accessory: .switchToggle(value: ReaderViewController.readerConfiguration.simulated) { enabled in
                        ReaderViewController.readerConfiguration.simulated = enabled
                        }),
                    ], footer: """
                    The SDK comes with the ability to simulate behavior \
                    without using physical hardware. This makes it easy to quickly \
                    test your integration end-to-end, from connecting a reader to \
                    taking payments.
                    """),
                ].compactMap({ $0})
        } else {
            dataSource.sections = [
                Section(header: "", rows: [], footer: Section.Extremity.view(headerView)),
                Section(header: rdrConnectionTitle, rows: [
                    Row(text: "Disconnect", selection: { [unowned self] in
                        self.disconnectFromReader()
                        }, cellClass: RedButtonCell.self),
                    ]),
                Section(header: "COMMON WORKFLOWS", rows: [
                    Row(text: "Collect card payment", detailText: "Collect a payment by reading a card", selection: { [unowned self] in
                        self.showStartPayment()
                        }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self),
                    Row(text: "Store card for future use", detailText: "Create a payment method by reading a card.", selection: { [unowned self] in
                        self.showReadReusableCard()
                        }, accessory: .none, cellClass: SubtitleCell.self),
                    Row(text: "Update reader software", detailText: "Check if a software update is available for the reader.", selection: { [unowned self] in
                        self.showUpdateReader()
                        }, accessory: .none, cellClass: SubtitleCell.self),
                    ]),
            ]
        }
    }

    // MARK: SCPTerminalDelegate
    func terminal(_ terminal: Terminal, didChangeConnectionStatus status: ConnectionStatus) {
        headerView.connectionStatus = status
    }

    func terminal(_ terminal: Terminal, didReportUnexpectedReaderDisconnect reader: Reader) {
        presentAlert(title: "Reader disconnected!", message: "\(reader.serialNumber)")
        connectedReader = nil
    }

}

extension DeviceType: CustomStringConvertible {
    public var description: String {
        return Terminal.stringFromDeviceType(self)
    }
}

extension DiscoveryMethod: CustomStringConvertible {
    public var description: String {
        return Terminal.stringFromDiscoveryMethod(self)
    }
}
