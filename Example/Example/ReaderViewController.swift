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

    static var deviceType: DeviceType = .chipper2X
    static var discoveryMethod: DiscoveryMethod = .bluetoothProximity

    #if targetEnvironment(simulator)
    static var simulated: Bool = true
    #else
    static var simulated: Bool = false
    #endif


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
        let config = DiscoveryConfiguration(deviceType: ReaderViewController.deviceType,
                                            discoveryMethod: ReaderViewController.discoveryMethod,
                                            simulated: ReaderViewController.simulated)
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
            }
            else {
                discoveryVC.dismiss(animated: true) {
                    self.updateContent()
                }
            }
        }
        let navController = UINavigationController(rootViewController: discoveryVC)
        navController.navigationBar.isTranslucent = false
        if #available(iOS 11.0, *) {
            navController.navigationBar.prefersLargeTitles = true
        }
        self.present(navController, animated: true, completion: nil)
    }

    private func disconnectFromReader() {
        Terminal.shared.disconnectReader { error in
            if let error = error {
                print("Disconnect failed: \(error)")
                self.presentAlert(error: error)
            }
            else {
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
        let vc = ReadReusableCardViewController()
        let navController = UINavigationController(rootViewController: vc)
        navController.navigationBar.isTranslucent = false
        if #available(iOS 11.0, *) {
            navController.navigationBar.prefersLargeTitles = true
        }
        self.present(navController, animated: true, completion: nil)
    }

    internal func showUpdateReader() {
        let vc = UpdateReaderViewController()
        let navController = UINavigationController(rootViewController: vc)
        navController.navigationBar.isTranslucent = false
        if #available(iOS 11.0, *) {
            navController.navigationBar.prefersLargeTitles = true
        }
        self.present(navController, animated: true, completion: nil)
    }

    internal func showDeviceTypes() {
        let vc = DeviceTypeViewController(deviceType: ReaderViewController.deviceType)
        vc.onSelectedDevice = { type in
            ReaderViewController.deviceType = type
            self.updateContent()
        }
        self.navigationController?.pushViewController(vc, animated: true)
    }
    
    internal func showDiscoveryMethods() {
        let vc = DiscoveryMethodViewController(method: ReaderViewController.discoveryMethod)
        vc.onSelectedMethod = { method in
            ReaderViewController.discoveryMethod = method
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
                    Row(text: ReaderViewController.deviceType.description, selection: { [unowned self] in
                        self.showDeviceTypes()
                        }, accessory: .disclosureIndicator),
                    ]),
                Section(header: "Discovery Method", rows: [
                    Row(text: ReaderViewController.discoveryMethod.description, selection: { [unowned self] in
                        self.showDiscoveryMethods()
                        }, accessory: .disclosureIndicator),
                    ]),
                Section(header: "", rows: [
                    Row(text: "Simulated", accessory: .switchToggle(value: ReaderViewController.simulated) { enabled in
                        ReaderViewController.simulated = enabled
                        }),
                    ], footer: "The SDK comes with the ability to simulate behavior without using physical hardware. This makes it easy to quickly test your integration end-to-end, from connecting a reader to taking payments."),
            ]
        }
        else {
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
