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
    private var reconnectionAlertController = UIAlertController(title: "Reconnecting...", message: "Reader has disconnected", preferredStyle: .alert)

    private lazy var discoveryTimeoutTextField: UITextField = {
        let textField = UITextField(frame: CGRect(x: 0, y: 0, width: 50, height: 20))
        textField.translatesAutoresizingMaskIntoConstraints = true
        textField.autocorrectionType = .no
        textField.autocapitalizationType = .none
        textField.keyboardType = .numberPad
        textField.clearButtonMode = .whileEditing
        textField.placeholder = "0"
        textField.textAlignment = .right
        let timeout = ReaderViewController.readerConfiguration.discoveryTimeout
        textField.text = timeout > 0 ? String(timeout) : nil
        return textField
    }()

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
        MobileReaderDelegateAnnouncer.shared.removeListener(self)
        InternetReaderDelegateAnnouncer.shared.removeListener(self)
        TapToPayReaderDelegateAnnouncer.shared.removeListener(self)
        OfflineDelegateAnnouncer.shared.removeListener(self)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()

        headerView.addGestureRecognizer(UITapGestureRecognizer(target: self, action: #selector(didTapReaderHeaderView)))

        TerminalDelegateAnnouncer.shared.addListener(self)
        MobileReaderDelegateAnnouncer.shared.addListener(self)
        InternetReaderDelegateAnnouncer.shared.addListener(self)
        TapToPayReaderDelegateAnnouncer.shared.addListener(self)
        OfflineDelegateAnnouncer.shared.addListener(self)
        navigationItem.rightBarButtonItem = UIBarButtonItem(customView: OfflineUIHandler.shared.rightBarButtonItemView)

        ReaderViewController.readerConfiguration = ReaderConfiguration.loadFromUserDefaults()

        updateContent()
    }

    // MARK: - Private

    internal func presentModalInNavigationController(_ vc: UIViewController) {
        let navController = LargeTitleNavigationController(rootViewController: vc)
        navController.presentationController?.delegate = self
        self.present(navController, animated: true, completion: nil)
    }

    internal func showDiscoverReaders() throws {
        let config: DiscoveryConfiguration = try {
            let simulated = ReaderViewController.readerConfiguration.simulated
            // Cache the timeout value now that its being used
            let timeout = UInt(discoveryTimeoutTextField.text ?? "0") ?? 0
            ReaderViewController.readerConfiguration.discoveryTimeout = timeout
            switch ReaderViewController.readerConfiguration.discoveryMethod {
            case .bluetoothScan:
                return try BluetoothScanDiscoveryConfigurationBuilder()
                    .setSimulated(simulated)
                    .setTimeout(timeout)
                    .build()
            case .bluetoothProximity:
                return try BluetoothProximityDiscoveryConfigurationBuilder().setSimulated(simulated).build()
            case .internet:
                return try InternetDiscoveryConfigurationBuilder()
                    .setSimulated(simulated)
                    .setTimeout(timeout)
                    .build()
            case .tapToPay:
                return try TapToPayDiscoveryConfigurationBuilder().setSimulated(simulated).build()
            case .usb:
                return try UsbDiscoveryConfigurationBuilder()
                    .setTimeout(timeout)
                    .setSimulated(simulated).build()
            @unknown default:
                // This could happen if we introduced a new discovery method and the user downgrades to a
                // version of the app that doesn't know about it.
                print("⚠️Unknown discovery method! Defaulting to Bluetooth Scan.️")
                return try BluetoothScanDiscoveryConfigurationBuilder().setSimulated(simulated).build()
            }
        }()

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

    internal func onReaderConnectFrom(viewController: UIViewController?, reader: Reader) {
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

    internal func rebootReader() {
        Terminal.shared.rebootReader { error in
            if let error = error {
                self.presentAlert(error: error)
            } // else, the reader will have disconnected
        }
    }

    internal func showStartPayment() {
        let vc = StartPaymentViewController(isSposReader: isSposReader())
        self.navigationController?.pushViewController(vc, animated: true)
    }

    internal func showStartRefund() {
        let vc = StartRefundViewController(isSposReader: isSposReader())
        self.navigationController?.pushViewController(vc, animated: true)
    }

    internal func showSetupIntent() {
        let vc = StartSetupIntentViewController(isSposReader: isSposReader())
        self.navigationController?.pushViewController(vc, animated: true)
    }

    private func isSposReader() -> Bool {
        let isSposReader = [DeviceType.stripeS700, DeviceType.stripeS700DevKit, DeviceType.wisePosE, DeviceType.wisePosEDevKit, DeviceType.etna].contains(Terminal.shared.connectedReader?.deviceType)
        return isSposReader
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

    internal func showStartReaderSettings() {
        let vc = StartReaderSettingsViewController()
        self.navigationController?.pushViewController(vc, animated: true)
    }

    internal func showOfflinePaymentLogs() {
        let vc = OfflinePaymentsLogViewController()
        self.navigationController?.pushViewController(vc, animated: true)
    }

    internal func showCollectInputs() {
        let vc = StartCollectInputsViewController()
        self.navigationController?.pushViewController(vc, animated: true)
    }

    internal func showCollectData() {
        let vc = StartCollectDataViewController()
        navigationController?.pushViewController(vc, animated: true)
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
                Row(text: "Store card via Setup Intents", detailText: "Create a SetupIntent for future payments.", selection: { [unowned self] in
                self.showSetupIntent()
            }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self)
            ]

            workflowRows.append(
                Row(text: "View stored offline payment logs", detailText: "View offline payment logs stored on this device.", selection: { [unowned self] in
                    self.showOfflinePaymentLogs()
                }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self)
            )

            var rebootRow: Row?
            let deviceType = connectedReader.deviceType
            switch deviceType {
            case .stripeM2, .chipper1X, .chipper2X, .wisePad3, .wiseCube:
                rebootRow = Row(text: "Reboot Reader", selection: { [unowned self] in
                    self.rebootReader()
                }, cellClass: ButtonCell.self)

                if let pendingUpdate = pendingUpdate {
                    workflowRows.append(
                        Row(text: "Update reader software", detailText: "Install an available software update for the reader.", selection: { [unowned self] in
                            self.showUpdateReader(update: pendingUpdate)
                            }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self)
                    )
                }
            case .verifoneP400, .wisePosE, .wisePosEDevKit, .etna, .stripeS700, .stripeS700DevKit:
                workflowRows.append(Row(text: "Set reader display", detailText: "Display an itemized cart on the reader", selection: { [unowned self] in
                    self.showStartSetReaderDisplay()
                }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self))
                workflowRows.append(Row(text: "Reader settings", detailText: "View and change reader settings", selection: { [unowned self] in
                    self.showStartReaderSettings()
                }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self))
            case .tapToPay:
                fallthrough
            @unknown default:
                break
            }

            if deviceType != .chipper2X && deviceType != .stripeM2 {
                workflowRows.append(Row(text: "In-Person refund", detailText: "Refund a charge made by an Interac debit card.", selection: { [unowned self] in
                self.showStartRefund()
                }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self))
            }

            if deviceType == .wisePosE || deviceType == .wisePosEDevKit || deviceType == .stripeS700 || deviceType == .stripeS700DevKit {
                workflowRows.append(Row(text: "Collect inputs", detailText: "Collect information with forms", selection: { [unowned self] in
                self.showCollectInputs()
                }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self))
            }

            if deviceType == .chipper2X || deviceType == .stripeM2 || deviceType == .chipper1X {
                workflowRows.append(Row(text: "Collect data", detailText: "Collect non-payment data using the reader hardware.", selection: { [unowned self] in
                    self.showCollectData()
                }, accessory: .disclosureIndicator, cellClass: SubtitleCell.self))
            }

            dataSource.sections = [
                Section(header: "", rows: [], footer: Section.Extremity.view(headerView)),
                Section(header: rdrConnectionTitle, rows: [
                    Row(text: "Disconnect", selection: { [unowned self] in
                        self.disconnectFromReader()
                        }, cellClass: RedButtonCell.self),
                    rebootRow,
                ].compactMap { $0 }),
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
                        do {
                            try self.showDiscoverReaders()
                        } catch {
                            self.presentAlert(error: error)
                        }
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
                    [.bluetoothScan, .usb, .internet].contains(ReaderViewController.readerConfiguration.discoveryMethod) != true ? nil :
                        Row(text: "Discovery Timeout", accessory: .view(discoveryTimeoutTextField), cellClass: Value1Cell.self),
                    Row(text: "Simulated", accessory: .switchToggle(value: ReaderViewController.readerConfiguration.simulated) { enabled in
                        ReaderViewController.readerConfiguration.simulated = enabled
                        self.updateContent()
                    }),
                ].compactMap { $0 }, footer: .title(footerTitle))
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

    func presentationControllerDidDismiss(_ presentationController: UIPresentationController) {
        performCancel(presentationController: presentationController)
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
}

// MARK: ReaderDelegate
extension ReaderViewController: ReaderDelegate {
    func reader(_ reader: Reader, didDisconnect reason: DisconnectReason) {
        // Ignore if user requested (no need to advertise that)
        if reason == .disconnectRequested {
            return
        }
        presentAlert(title: "Reader disconnected!", message: "\(reader.serialNumber) disconnected with reason \(Terminal.stringFromDisconnectReason(reason))")
        connectedReader = nil
    }

    func reader(_ reader: Reader, didStartReconnect cancelable: Cancelable, disconnectReason: DisconnectReason) {
        self.reconnectionAlertController = UIAlertController(title: "Reconnecting...", message: "Reader \(reader.serialNumber) has disconnected: \(Terminal.stringFromDisconnectReason(disconnectReason))", preferredStyle: .alert)
        let cancelAction = UIAlertAction(title: "Cancel", style: .default) { _ in cancelable.cancel { error in
            // If terminalDidFailReaderReconnect did not present anything, present results of cancel and clear alert
            if self.reconnectionAlertController.isBeingPresented {
                self.reconnectionAlertController.dismiss(animated: true) {
                    if let error = error {
                        self.presentAlert(title: "Cancellation failed", message: error.localizedDescription)
                    } else {
                        self.presentAlert(title: "Cancelled", message: "Reconnection has been cancelled.")
                    }
                }
            }
        }}
        reconnectionAlertController.addAction(cancelAction)
        topViewController()?.present(reconnectionAlertController, animated: true, completion: nil)
    }

    func readerDidFailReconnect(_ reader: Reader) {
        self.reconnectionAlertController.dismiss(animated: true) {
            self.presentAlert(title: "Reader Disconnected", message: "Reader reconnection failed!")
        }
        connectedReader = nil

    }
    func readerDidSucceedReconnect(_ reader: Reader) {
        self.reconnectionAlertController.dismiss(animated: true) {
            self.presentAlert(title: "Reconnected!", message: "We were able to reconnect to the reader.")
        }
    }
}

// MARK: InternetReaderDelegate
extension ReaderViewController: InternetReaderDelegate {
    // ReaderDelegate above implements the common didDisconnect method.
}

// MARK: TerminalAndMobileReaderDelegate
extension ReaderViewController: MobileReaderDelegate {
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

// MARK: TapToPayReaderDelegate
extension ReaderViewController: TapToPayReaderDelegate {
    func tapToPayReader(_ reader: Reader, didStartInstallingUpdate update: ReaderSoftwareUpdate, cancelable: Cancelable?) {
    }

    func tapToPayReader(_ reader: Reader, didReportReaderSoftwareUpdateProgress progress: Float) {
    }

    func tapToPayReader(_ reader: Reader, didFinishInstallingUpdate update: ReaderSoftwareUpdate?, error: Error?) {
    }

    func tapToPayReader(_ reader: Reader, didRequestReaderInput inputOptions: ReaderInputOptions = []) {
    }

    func tapToPayReader(_ reader: Reader, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {
    }
}

extension ReaderViewController: OfflineDelegate {
    func terminal(_ terminal: Terminal, didChange offlineStatus: OfflineStatus) {
        switch offlineStatus.sdk.networkStatus {
        case .offline:
            OfflinePaymentsLogViewController.writeLogToDisk("\(NSDate()) Transitioned state to offline.")
        case .online:
            OfflinePaymentsLogViewController.writeLogToDisk("\(NSDate()) Transitioned state to online.")
        case .unknown:
            OfflinePaymentsLogViewController.writeLogToDisk("\(NSDate()) Transitioned state to unknown.")
        @unknown default:
            fatalError()
        }
    }

    func terminal(_ terminal: Terminal, didForwardPaymentIntent intent: PaymentIntent, error: Error?) {
        if let error = error {
            OfflinePaymentsLogViewController.writeLogToDisk("\(NSDate()) Error forwarding offline payment intent \(intent.offlineId ?? intent.description) \(error.localizedDescription)", details: intent)
            return
        }
        OfflinePaymentsLogViewController.writeLogToDisk("\(NSDate()) Successfully forwarded offline payment intent \(intent.stripeId ?? "N/A") with offline id \(intent.offlineId ?? "nil offline id") status: \(Terminal.stringFromPaymentIntentStatus(intent.status))", details: intent)
        if intent.status == .requiresCapture, let id = intent.stripeId {
            AppDelegate.apiClient?.capturePaymentIntent(id, completion: { error in
                if let error = error {
                    OfflinePaymentsLogViewController.writeLogToDisk("\(NSDate()) Error capturing offline payment intent for \(id): \(error.localizedDescription)", details: intent)
                } else {
                    OfflinePaymentsLogViewController.writeLogToDisk("\(NSDate()) Successfully captured offline payment intent for \(id): \(intent.amount)\(intent.currency)", details: intent)
                }
            })
        }
    }

    func terminal(_ terminal: Terminal, didReportForwardingError error: Error) {
        OfflinePaymentsLogViewController.writeLogToDisk("\(NSDate()) Did report forwarding error: \(error.localizedDescription)")
    }
}

extension DeviceType: @retroactive CustomStringConvertible {
    public var description: String {
        return Terminal.stringFromDeviceType(self)
    }
}

extension DiscoveryMethod: @retroactive CustomStringConvertible {
    public var description: String {
        if self == .usb {
            return "USB (Private Beta)"
        }
        return Terminal.stringFromDiscoveryMethod(self)
    }
}
