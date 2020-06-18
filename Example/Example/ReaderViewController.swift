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

class ReaderViewController: TableViewController, TerminalDelegate, CancelingViewController {
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

    deinit {
        TerminalDelegateAnnouncer.shared.removeListener(self)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()

        TerminalDelegateAnnouncer.shared.addListener(self)

        ReaderViewController.readerConfiguration = ReaderConfiguration.loadFromUserDefaults()
        updateContent()
    }

    // MARK: - Private

    private func presentModalInNavigationController(_ vc: UIViewController) {
        let navController = LargeTitleNavigationController(rootViewController: vc)
        navController.presentationController?.delegate = self
        self.present(navController, animated: true, completion: nil)
    }

    private func showDiscoverReaders() {
        let simulated = ReaderViewController.readerConfiguration.deviceType != .wisePad3 ? ReaderViewController.readerConfiguration.simulated : false
        let config = DiscoveryConfiguration(
            deviceType: ReaderViewController.readerConfiguration.deviceType,
            discoveryMethod: ReaderViewController.readerConfiguration.discoveryMethod,
            simulated: simulated
        )
        let discoveryVC = ReaderDiscoveryViewController(discoveryConfig: config)

        discoveryVC.onConnectedToReader = { [weak discoveryVC] reader in
            self.onReaderConnectFrom(viewController: discoveryVC, reader: reader)
        }

        self.presentModalInNavigationController(discoveryVC)
    }

    private func showRegisterReader() {
        let registerVC = ReaderRegistrationViewController()

        registerVC.onConnectedToReader = { [weak registerVC] reader in
            self.onReaderConnectFrom(viewController: registerVC, reader: reader)
        }

        self.presentModalInNavigationController(registerVC)
    }

    private func onReaderConnectFrom(viewController: UIViewController?, reader: Reader) {
        guard let viewController = viewController else { return }

        self.connectedReader = reader

        viewController.dismiss(animated: true) {
            self.updateContent()
        }
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

    internal func showStartRefund() {
        let vc = StartRefundViewController()
        self.navigationController?.pushViewController(vc, animated: true)
    }

    internal func showReadReusableCard() {
        if let connectReader = self.connectedReader, connectReader.deviceType != .chipper2X {
            self.presentAlert(title: "Error", message: "This device type does not support readReusableCard.")
            return
        }
        self.presentModalInNavigationController(ReadReusableCardViewController())
    }

    internal func showUpdateReader() {
        self.presentModalInNavigationController(UpdateReaderViewController())
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
        if let connectedReader = self.connectedReader {
            var workflowRows = [
                Row(text: "Collect card payment", detailText: "Collect a payment by reading a card", selection: { [unowned self] in
                    self.showStartPayment()
                    }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self),
                Row(text: "Store card for future use", detailText: "Create a payment method by reading a card.", selection: { [unowned self] in
                    self.showReadReusableCard()
                    }, accessory: .none, cellClass: SubtitleCell.self)
            ]

            switch connectedReader.deviceType {
            case .chipper2X, .wisePad3:
                workflowRows.append(Row(text: "Update reader software", detailText: "Check if a software update is available for the reader.", selection: { [unowned self] in
                self.showUpdateReader()
                }, accessory: .none, cellClass: SubtitleCell.self))
            case .verifoneP400:
                workflowRows.append(Row(text: "In-Person Refund", detailText: "Refund a charge made by an Interac debit card.", selection: { [unowned self] in
                self.showStartRefund()
                }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self))
            @unknown default:
                break
            }

            dataSource.sections = [
                Section(header: "", rows: [], footer: Section.Extremity.view(headerView)),
                Section(header: rdrConnectionTitle, rows: [
                    Row(text: "Disconnect", selection: { [unowned self] in
                        self.disconnectFromReader()
                        }, cellClass: RedButtonCell.self)
                ]),
                Section(header: "COMMON WORKFLOWS", rows: workflowRows)
            ]
        } else {
            dataSource.sections = [
                Section(header: "", rows: [], footer: Section.Extremity.view(headerView)),
                Section(header: rdrConnectionTitle, rows: [
                    Row(text: "Discover Readers", selection: { [unowned self] in
                        self.showDiscoverReaders()
                        }, cellClass: ButtonCell.self),
                    Row(text: "Register Internet Reader", selection: { [unowned self] in
                        self.showRegisterReader()
                        }, cellClass: ButtonCell.self)
                ]),
                Section(header: "Device Type", rows: [
                    Row(text: ReaderViewController.readerConfiguration.deviceType.description, selection: { [unowned self] in
                        self.showDeviceTypes()
                        }, accessory: .disclosureIndicator)
                ]),
                Section(header: "Discovery Method", rows: [
                    Row(text: ReaderViewController.readerConfiguration.discoveryMethod.description, selection: { [unowned self] in
                        self.showDiscoveryMethods()
                        }, accessory: .disclosureIndicator)
                ]),
                Section(header: "", rows: [
                    Row(text: "Simulated", accessory: .switchToggle(value: ReaderViewController.readerConfiguration.simulated) { enabled in
                        ReaderViewController.readerConfiguration.simulated = enabled
                        })
                    ], footer: """
                    The SDK comes with the ability to simulate behavior \
                    without using physical hardware. This makes it easy to quickly \
                    test your integration end-to-end, from connecting a reader to \
                    taking payments.
                    """)
                ].compactMap({ $0})
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

    // MARK: - UIAdaptivePresentationControllerDelegate

    // See comment in `CancelingViewController` for why we're canceling during `ShouldDismiss` instead of `DidDismiss`
    func presentationControllerShouldDismiss(_ presentationController: UIPresentationController) -> Bool {
        performCancel(presentationController: presentationController)
        return true
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
