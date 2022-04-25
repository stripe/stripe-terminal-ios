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

class ReaderViewController: TableViewController, CancelingViewController {
    internal var connectedReader: Reader? {
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

    internal let headerView = ReaderHeaderView()
    /// Will be set during connect from the DiscoveryViewController if an update is reported
    private var pendingUpdate: ReaderSoftwareUpdate?

    init() {
        super.init(style: .grouped)
        self.title = "Terminal"
        Terminal.shared.simulatorConfiguration.availableReaderUpdate = .random
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    deinit {
        TerminalDelegateAnnouncer.shared.removeListener(self)
        BluetoothReaderDelegateAnnouncer.shared.removeListener(self)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()

        headerView.addGestureRecognizer(UITapGestureRecognizer(target: self, action: #selector(didTapReaderHeaderView)))

        TerminalDelegateAnnouncer.shared.addListener(self)
        BluetoothReaderDelegateAnnouncer.shared.addListener(self)

        ReaderViewController.readerConfiguration = ReaderConfiguration.loadFromUserDefaults()
        updateContent()
    }

    // MARK: - Private

    private func presentModalInNavigationController(_ vc: UIViewController) {
        let navController = LargeTitleNavigationController(rootViewController: vc)
        navController.presentationController?.delegate = self
        self.present(navController, animated: true, completion: nil)
    }

    internal func showDiscoverReaders() {
        let config = DiscoveryConfiguration(
            discoveryMethod: ReaderViewController.readerConfiguration.discoveryMethod,
            simulated: ReaderViewController.readerConfiguration.simulated
        )

        let discoveryVC = ReaderDiscoveryViewController(discoveryConfig: config)

        discoveryVC.onConnectedToReader = { [weak discoveryVC] reader in
            self.onReaderConnectFrom(viewController: discoveryVC, reader: reader)
        }
        discoveryVC.onCanceled = {[unowned self] in
            self.dismiss(animated: true, completion: nil)
        }

        self.presentModalInNavigationController(discoveryVC)
    }

    internal func showRegisterReader() {
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

    internal func disconnectFromReader() {
        Terminal.shared.disconnectReader { error in
            if let error = error {
                print("Disconnect failed: \(error)")
                self.presentAlert(error: error)
            } else {
                self.connectedReader = nil
                self.pendingUpdate = nil
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
        self.presentModalInNavigationController(ReadReusableCardViewController())
    }

    internal func showSetupIntent() {
        self.presentModalInNavigationController(SetupIntentViewController())
    }

    internal func showUpdateReader(update: ReaderSoftwareUpdate) {
        self.presentModalInNavigationController(UpdateReaderViewController(update: update) {[weak self] in
            guard let self = self else { return }
            self.pendingUpdate = nil
            self.updateContent()
        })
    }

    internal func showDiscoveryMethods() {
        let vc = DiscoveryMethodViewController(method: ReaderViewController.readerConfiguration.discoveryMethod)
        vc.onSelectedMethod = { method in
            guard ReaderViewController.readerConfiguration.discoveryMethod != method else { return }
            ReaderViewController.readerConfiguration.discoveryMethod = method
            self.updateContent()
        }
        self.navigationController?.pushViewController(vc, animated: true)
    }

    internal func showStartSetReaderDisplay() {
        let vc = StartSetReaderDisplayViewController()
        self.navigationController?.pushViewController(vc, animated: true)
    }

    internal func updateContent() {
        let rdrConnectionTitle = Section.Extremity.title("Reader Connection")
        let buildNameString = Bundle.main.object(forInfoDictionaryKey: kCFBundleNameKey as String) ?? "??"
        let buildNumberString = Bundle.main.object(forInfoDictionaryKey: kCFBundleVersionKey as String) ?? "??"
        let versions = "SDK Version: \(StripeTerminal.SCPSDKVersion) \nTest Flight Build: \(buildNameString) - \(buildNumberString)"
        if let connectedReader = self.connectedReader {
            var workflowRows = [
                Row(text: "Collect card payment", detailText: "Collect a payment by reading a card", selection: { [unowned self] in
                self.showStartPayment()
            }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self),
                Row(text: "Store card via readReusableCard", detailText: "Create a payment method for future use.", selection: { [unowned self] in
                self.showReadReusableCard()
            }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self),
                Row(text: "Store card via Setup Intents", detailText: "Create a SetupIntent for future payments.", selection: { [unowned self] in
                self.showSetupIntent()
            }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self)
            ]

            switch connectedReader.deviceType {
            case .stripeM2, .chipper1X, .chipper2X, .wisePad3, .wiseCube:
                if let pendingUpdate = pendingUpdate {
                    workflowRows.append(
                        Row(text: "Update reader software", detailText: "Install an available software update for the reader.", selection: { [unowned self] in
                            self.showUpdateReader(update: pendingUpdate)
                            }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self)
                    )
                }
            case .verifoneP400, .wisePosE:
                workflowRows.append(Row(text: "Set reader display", detailText: "Display an itemized cart on the reader", selection: { [unowned self] in
                    self.showStartSetReaderDisplay()
                }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self))
            @unknown default:
                break
            }

            if connectedReader.deviceType != .chipper2X || connectedReader.deviceType != .stripeM2 {
                workflowRows.append(Row(text: "In-Person Refund", detailText: "Refund a charge made by an Interac debit card.", selection: { [unowned self] in
                self.showStartRefund()
                }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self))
            }

            dataSource.sections = [
                Section(header: "", rows: [], footer: Section.Extremity.view(headerView)),
                Section(header: rdrConnectionTitle, rows: [
                    Row(text: "Disconnect", selection: { [unowned self] in
                        self.disconnectFromReader()
                        }, cellClass: RedButtonCell.self)
                ]),
                Section(header: "COMMON WORKFLOWS", rows: workflowRows, footer: .title(versions))
            ]
        } else {
            let footerTitle = """
                The SDK comes with the ability to simulate behavior \
                without using physical hardware. This makes it easy to quickly \
                test your integration end-to-end, from connecting a reader to \
                taking payments.\n
                \(versions)
                """
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
                Section(header: "Discovery Method", rows: [
                    Row(text: ReaderViewController.readerConfiguration.discoveryMethod.description, selection: { [unowned self] in
                        self.showDiscoveryMethods()
                        }, accessory: .disclosureIndicator)
                ]),
                Section(header: "", rows: [
                    Row(text: "Simulated", accessory: .switchToggle(value: ReaderViewController.readerConfiguration.simulated) { enabled in
                        ReaderViewController.readerConfiguration.simulated = enabled
                        self.updateContent()
                    })
                ], footer: .title(footerTitle))
            ].compactMap({ $0})
        }
    }

    @objc
    func didTapReaderHeaderView() {
        guard let reader = self.connectedReader, let version = reader.deviceSoftwareVersion else {
            return
        }

        self.presentAlert(title: reader.label ?? reader.serialNumber, message: version)
    }

    // MARK: - UIAdaptivePresentationControllerDelegate

    // See comment in `CancelingViewController` for why we're canceling during `ShouldDismiss` instead of `DidDismiss`
    func presentationControllerShouldDismiss(_ presentationController: UIPresentationController) -> Bool {
        performCancel(presentationController: presentationController)
        return true
    }
}

// MARK: TerminalDelegate
extension ReaderViewController: TerminalDelegate {
    func terminal(_ terminal: Terminal, didChangeConnectionStatus status: ConnectionStatus) {
        headerView.connectionStatus = status

        if status == .notConnected {
            connectedReader = nil
            pendingUpdate = nil
        }
    }

    func terminal(_ terminal: Terminal, didReportUnexpectedReaderDisconnect reader: Reader) {
        presentAlert(title: "Reader disconnected!", message: "\(reader.serialNumber)")
        connectedReader = nil
    }
}

// MARK: TerminalAndBluetoothReaderDelegate
extension ReaderViewController: BluetoothReaderDelegate {
    func reader(_ reader: Reader, didReportAvailableUpdate update: ReaderSoftwareUpdate) {
        pendingUpdate = update
        updateContent()
    }

    func reader(_ reader: Reader, didStartInstallingUpdate update: ReaderSoftwareUpdate, cancelable: Cancelable?) {
        // Prevent idle lock while updates are installing
        // Doing this in the root ReaderVC since it catches both required updates as well as optional updates.
        UIApplication.shared.isIdleTimerDisabled = true
    }

    func reader(_ reader: Reader, didReportReaderSoftwareUpdateProgress progress: Float) {
    }

    func reader(_ reader: Reader, didFinishInstallingUpdate update: ReaderSoftwareUpdate?, error: Error?) {
        UIApplication.shared.isIdleTimerDisabled = false
    }

    func reader(_ reader: Reader, didRequestReaderInput inputOptions: ReaderInputOptions = []) {
    }

    func reader(_ reader: Reader, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {
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
