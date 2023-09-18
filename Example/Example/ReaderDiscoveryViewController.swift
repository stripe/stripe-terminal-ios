//
//  ReaderDiscoveryViewController.swift
//  Example
//
//  Created by Ben Guo on 7/18/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class ReaderDiscoveryViewController: TableViewController, CancelableViewController, CancelingViewController {

    private var selectedLocation: Location?
    private var autoReconnectOnUnexpectedDisconnect: Bool = false
    var onCanceled: () -> Void = {}
    var onConnectedToReader: (Reader) -> Void = { _ in }
    private let discoveryConfig: DiscoveryConfiguration
    internal var cancelable: Cancelable?
    internal weak var cancelButton: UIBarButtonItem?
    private let activityIndicatorView = ActivityIndicatorHeaderView(title: "HOLD READER NEARBY")
    private var readers: [Reader] = []
    private enum ViewState {
        /// Have not started discovering Readers yet
        case preDiscovery
        /// Actively discovering readers
        case discovering
        /// Actively connecting to a reader
        case connecting
        /// Done actively discovering readers
        case doneDiscovering
    }
    private var viewState = ViewState.preDiscovery
    private var updateReaderVC: UpdateReaderViewController? // Displayed when a required update is being installed
    private var shouldShowBTConnectionConfigSection: Bool {
        return discoveryConfig.discoveryMethod != .internet
    }
    private let onBehalfOfTextField = TextFieldView(placeholderText: "On behalf of account ID (optional)")

    init(discoveryConfig: DiscoveryConfiguration) {
        self.discoveryConfig = discoveryConfig
        super.init(style: .grouped)
        self.title = "Discovery"
        TerminalDelegateAnnouncer.shared.addListener(self)
        BluetoothReaderDelegateAnnouncer.shared.addListener(self)
        LocalMobileReaderDelegateAnnouncer.shared.addListener(self)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    deinit {
        TerminalDelegateAnnouncer.shared.removeListener(self)
        BluetoothReaderDelegateAnnouncer.shared.removeListener(self)
        LocalMobileReaderDelegateAnnouncer.shared.removeListener(self)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()

        let cancelButton = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(dismissAction))
        self.cancelButton = cancelButton
        navigationItem.leftBarButtonItem = cancelButton
        activityIndicatorView.activityIndicator.hidesWhenStopped = true

        updateContent()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)

        if viewState == .preDiscovery {
            // 1. discover readers
            cancelable = Terminal.shared.discoverReaders(discoveryConfig, delegate: self) { [weak self] error in
                guard let self = self else { return }

                if let error = error {
                    print("discoverReaders failed: \(error)")
                    self.presentAlert(error: error) { _ in
                        self.presentingViewController?.dismiss(animated: true, completion: nil)
                    }
                }
                self.cancelable = nil
                self.viewState = .doneDiscovering
                self.updateContent()
            }
            viewState = .discovering
            updateContent()
        }
    }

    // 2. connect to a selected reader
    // swiftlint:disable:next cyclomatic_complexity
    private func connect(to reader: Reader, failIfInUse: Bool = false) {
        setAllowedCancelMethods([])
        viewState = .connecting
        updateContent()

        let connectCompletion: ReaderCompletionBlock = { connectedReader, error in
            if let connectedReader = connectedReader {
                self.cancelable = nil
                if let vc = self.updateReaderVC {
                    vc.dismiss(animated: true) {
                        self.onConnectedToReader(connectedReader)
                    }
                } else {
                    self.onConnectedToReader(connectedReader)
                }
                return
            } else if let error = error as NSError?,
                error.code == ErrorCode.connectFailedReaderIsInUse.rawValue {
                self.presentAlert(
                    title: "\(reader.label ?? reader.serialNumber) in use",
                    message: "Reader is already collecting a payment. Interrupt the in-progress transaction?",
                    okButtonTitle: "Interrupt",
                    handler: { (shouldInterrupt) in
                        if shouldInterrupt {
                            self.connect(to: reader, failIfInUse: false)
                        } else {
                            self.viewState = .discovering
                            self.updateContent()
                        }
                    })
            } else if let error = error {
                let showError = {
                    self.presentAlert(error: error)
                    self.viewState = .discovering
                    self.updateContent()
                }

                // Dismiss the update VC if needed so the error presents correctly
                if let vc = self.updateReaderVC {
                    vc.dismiss(animated: true) {
                        showError()
                    }
                } else {
                    showError()
                }
            }
            self.setAllowedCancelMethods(.all)
        }

        switch reader.deviceType {
        case .chipper1X, .chipper2X, .stripeM2, .wisePad3, .wiseCube:
            let locationId = selectedLocation?.stripeId ?? reader.locationId
            if let presentLocationId = locationId {
                let connectionConfig = BluetoothConnectionConfiguration(locationId: presentLocationId, autoReconnectOnUnexpectedDisconnect: autoReconnectOnUnexpectedDisconnect, autoReconnectionDelegate: ReconnectionDelegateAnnouncer.shared)
                Terminal.shared.connectBluetoothReader(reader, delegate: BluetoothReaderDelegateAnnouncer.shared, connectionConfig: connectionConfig, completion: connectCompletion)
            } else {
                self.presentLocationRequiredAlert()
            }
        case .verifoneP400, .wisePosE, .wisePosEDevKit, .etna, .stripeS700, .stripeS700DevKit:
            let connectionConfig = InternetConnectionConfiguration(failIfInUse: failIfInUse, allowCustomerCancel: true)
            Terminal.shared.connectInternetReader(reader, connectionConfig: connectionConfig, completion: connectCompletion)
        case .appleBuiltIn:
            let locationId = selectedLocation?.stripeId ?? reader.locationId
            if let presentLocationId = locationId {
                let useOBO = !(onBehalfOfTextField.textField.text?.isEmpty ?? false)
                let connectionConfig = LocalMobileConnectionConfiguration(locationId: presentLocationId,
                                                                          merchantDisplayName: nil, // use the location name
                                                                          onBehalfOf: useOBO ? onBehalfOfTextField.textField.text : nil)
                Terminal.shared.connectLocalMobileReader(reader, delegate: LocalMobileReaderDelegateAnnouncer.shared, connectionConfig: connectionConfig, completion: connectCompletion)
            } else {
                self.presentLocationRequiredAlert()
            }
        @unknown default:
            fatalError()
        }
    }

    @objc
    func dismissAction() {
        if let cancelable = cancelable {
            cancelable.cancel { error in
                if let error = error {
                    print("cancel discoverReaders failed: \(error)")
                } else {
                    self.onCanceled()
                }
                self.cancelable = nil
            }
        } else {
            self.onCanceled()
        }
    }

    // MARK: - updateContent & helpers

    private func updateContent() {
        updateActivityIndicatorView()
        dataSource.sections = [
            shouldShowBTConnectionConfigSection ? bluetoothConnectionConfigurationSection() : nil,
            discoveryConfig.simulated && discoveryConfig.discoveryMethod != .internet ? simulatedUpdateSection() : nil,
            discoveryConfig.discoveryMethod == .localMobile ? onBehalfOfSection() : nil,
            readerListSection()
        ].compactMap({ $0 })
    }

    // swiftlint:disable:next cyclomatic_complexity
    private func updateActivityIndicatorView() {
        if viewState == .discovering || viewState == .connecting {
            activityIndicatorView.activityIndicator.startAnimating()
        } else {
            activityIndicatorView.activityIndicator.stopAnimating()
        }

        switch (discoveryConfig.discoveryMethod, readers.count, viewState) {
        case (_, _, .connecting):
            activityIndicatorView.title = "Connecting..."

        case (.bluetoothProximity, 0, _):
            activityIndicatorView.title = "HOLD READER NEARBY"
        case (.bluetoothProximity, _, _):
            activityIndicatorView.title = "DISCOVERED READER"

        case (.bluetoothScan, _, _):
            activityIndicatorView.title = "NEARBY READERS"

        case (.internet, 0, .doneDiscovering):
            activityIndicatorView.title = "NO REGISTERED READERS FOUND"
        case (.internet, _, .doneDiscovering):
            activityIndicatorView.title = "REGISTERED READERS"
        case (.internet, _, _):
            activityIndicatorView.title = "LOOKING UP REGISTERED READERS"

        case (.localMobile, 0, .doneDiscovering):
            activityIndicatorView.title = "NO SUPPORTED READERS FOUND"
        case (.localMobile, _, _):
            activityIndicatorView.title = "LOCAL MOBILE READERS"

        @unknown default:
            activityIndicatorView.title = "READERS"
        }
    }

    internal func presentModalInNavigationController(_ vc: UIViewController) {
        let navController = LargeTitleNavigationController(rootViewController: vc)
        navController.presentationController?.delegate = self
        self.present(navController, animated: true, completion: nil)
    }

    private func onBehalfOfSection() -> Section {
        return Section(header: "Destination charges", rows: [],
                       footer: Section.Extremity.autoLayoutView(onBehalfOfTextField))
    }


    // MARK: - Location Selection UI

    private func bluetoothConnectionConfigurationSection() -> Section {
        if discoveryConfig.simulated {
            return Section(
                header: Section.Extremity.title("Select location"),
                rows: [
                    Row(
                        text: "Mock simulated reader location",
                        accessory: .disclosureIndicator,
                        cellClass: discoveryConfig.simulated ? DisabledCell.self : nil
                    )
                ],
                footer: Section.Extremity.title("Simulated readers are always registered to the mock simulated location.")
            )
        } else {
            return Section(
                header: Section.Extremity.title("Connection Configuration"),
                rows: [
                    Row(text: "Enable Auto-Reconnect", accessory: .switchToggle(value: autoReconnectOnUnexpectedDisconnect, { _ in
                        self.autoReconnectOnUnexpectedDisconnect.toggle()
                    })),
                    Row(
                        text: selectedLocation != nil ? selectedLocation?.displayString : "No location selected",
                        selection: { [unowned self] in self.showLocationSelector() },
                        accessory: .disclosureIndicator
                    )
                ],
                footer: Section.Extremity.title("Bluetooth readers must be registered to a location during the connection process. If you do not select a location, the reader will attempt to register to the same location it was registered to during the previous connection.")
            )
        }
    }

    internal func showLocationSelector() {
        let selectLocationVC = SelectLocationViewController()
        selectLocationVC.onSelectLocation = { [unowned selectLocationVC] location in
            self.onLocationSelect(viewController: selectLocationVC, location: location)
        }
        self.presentModalInNavigationController(selectLocationVC)
    }

    internal func onLocationSelect(viewController: SelectLocationViewController, location: Location) {
        self.selectedLocation = location

        viewController.dismiss(animated: true) {
            self.updateContent()
        }
    }

    private func presentLocationRequiredAlert() {
        self.presentAlert(
            title: "Please select a location",
            message: "This reader does not have a previously registered location. Please select a location to register it to."
        )
    }

    private func buildLocationDescription(forReader reader: Reader, usingDiscoveryMethod discoveryMethod: DiscoveryMethod) -> String {
        return {
            switch discoveryMethod {
            case .internet:
                return buildLocationDescription(forInternetReader: reader)
            case .bluetoothProximity, .bluetoothScan:
                return buildLocationDescription(forBlueoothReader: reader)
            case .localMobile:
                return buildLocationDescription(forLocalMobileReader: reader)
            case _:
                return "Unknown location status"
            }
        }()
    }

    private func buildLocationDescription(forInternetReader reader: Reader) -> String {
        // It's currently not possible to change an Internet reader's location directly via the SDK
        // so we only need to switch on the current locationStatus
        switch reader.locationStatus {
        case (.notSet):
            return "Not registered to a location"
        case (.set):
            guard let readerLocation = reader.location else { fatalError() }
            return "Registered to: \(readerLocation.displayString)"
        case _:
            return "Unknown location status"
        }
    }

    private func buildLocationDescription(forBlueoothReader reader: Reader) -> String {
        let isLocationSelected = selectedLocation != nil

        switch (reader.locationStatus, isLocationSelected) {
        case (.set, false):
            guard let readerLocation = reader.location else { fatalError() }
            return "Will register to last location: \(readerLocation.displayString)"
        case (.set, true):
            guard let readerLocation = reader.location, let selectedLocation = selectedLocation else { fatalError() }
            return readerLocation.stripeId == selectedLocation.stripeId ?
             "Will register to last location: \(selectedLocation.displayString)" :
             "Will change location from \(readerLocation.displayString) to \(selectedLocation.displayString)"
        case (.notSet, false):
            return "❗️No last registered location, please select one first"
        case (.notSet, true),
             (.unknown, true):
            guard let selectedLocation = selectedLocation else { fatalError() }
            return "Will register to location: \(selectedLocation.displayString)"
        case (.unknown, false):
            return "❗️Unknown last location, please select one first"
        case (_, _):
            fatalError("Crash in buildLocationDescription. Reader is \(reader.debugDescription)")
        }
    }

    private func buildLocationDescription(forLocalMobileReader reader: Reader) -> String {
        switch reader.locationStatus {
        case (.notSet):
            return "Not registered to a location"
        case (.set):
            guard let readerLocation = reader.location else { fatalError() }
            return "Registered to: \(readerLocation.displayString)"
        case _:
            return "Unknown location status"
        }
    }

    private func readerRequiresLocationToHaveBeenSelected(reader: Reader) -> Bool {
        return discoveryConfig.discoveryMethod != .internet && reader.locationStatus == .notSet
    }

    // MARK: - Simulated Update Plan

    private func simulatedUpdateSection() -> Section {
        return Section(header: "Simulated Update Plan", rows: [],
                       footer: Section.Extremity.autoLayoutView(ReaderUpdatePicker()))
    }

    // MARK: - Reader List UI

    private func readerListSection() -> Section {
        let rows = readers.map { reader in
            row(forReader: reader,
                discoveryMethod: self.discoveryConfig.discoveryMethod,
                selection: { [unowned self] in
                    if readerRequiresLocationToHaveBeenSelected(reader: reader) && self.selectedLocation == nil {
                        self.presentLocationRequiredAlert()
                    } else {
                        self.connect(to: reader)
                    }
                })
        }

        return Section(header: Section.Extremity.view(activityIndicatorView),
                       rows: rows,
                       footer: (readers.isEmpty
                                    ? nil
                                    : readerListFooter(for: readers, discoveryMethod: self.discoveryConfig.discoveryMethod))
        )
    }

    // swiftlint:disable cyclomatic_complexity
    /// Returns a Row with details about the reader.
    ///
    /// The row formatting depends on the current discoveryMethod, as there are
    /// different things we choose to show our users.
    ///
    /// - Parameters:
    ///   - reader: the reader that the row should display
    ///   - discoveryMethod: how the reader was discovered
    ///   - selection: action to take when row is selected
    /// - Returns: A Row (from Static library) for this reader
    private func row(forReader reader: Reader, discoveryMethod: DiscoveryMethod, selection: @escaping Selection) -> Row {
        var cellClass: Cell.Type = SubtitleCell.self
        var details = [String]()

        if discoveryMethod == .internet {
            if reader.status == .online, let ipAddress = reader.ipAddress {
                details.append("🌐 \(ipAddress)")
            } else {
                details.append("🌐 (offline)")
            }
        } else {
            if let battery = reader.batteryLevel {
                details.append("🔋 \(String(format: "%.0f", battery.floatValue * 100))%")
            }
        }

        let locationMessage = self.buildLocationDescription(forReader: reader, usingDiscoveryMethod: discoveryMethod)
        details.append("📍 \(locationMessage)")

        if discoveryConfig.discoveryMethod != .internet && reader.locationStatus != .set && selectedLocation == nil {
            // Prevent connecting to a Bluetooth reader that doesn't have a previous location
            // and the user hasn't selected a new location to register to
            cellClass = DisabledSubtitleCell.self
        }

        var image: UIImage?
        switch reader.deviceType {
        case .stripeM2:
            image = UIImage(named: "stripe_m2")
        case .chipper1X, .chipper2X, .wiseCube:
            image = UIImage(named: "chipper")
        case .verifoneP400:
            image = UIImage(named: "verifone")
        case .wisePad3:
            image = UIImage(named: "wisepad")
        case .wisePosE, .wisePosEDevKit, .etna, .stripeS700, .stripeS700DevKit:
            image = UIImage(named: "wisepose")
        case .appleBuiltIn:
            image = nil
        @unknown default:
            image = nil
        }

        // prefer reader's label, fall back to serial number
        return Row(text: reader.label ?? reader.serialNumber,
                   detailText: details.joined(separator: " • "),
                   selection: selection,
                   image: image,
                   cellClass: cellClass
        )
    }
    // swiftlint:enable cyclomatic_complexity

    /// Optionally return footer for this discovery method & readers.
    ///
    /// In `.bluetoothProximity` mode, there's only one reader discovered, and
    /// this displays it's current software version.
    /// In `.internet` mode, we display the iOS device's wifi IP address.
    ///
    /// - Parameters:
    ///   - readers: the readers being displayed in the table
    ///   - discoveryMethod: how those readers were discovered
    /// - Returns: optional footer to display on screen
    private func readerListFooter(for readers: [Reader], discoveryMethod: DiscoveryMethod) -> Section.Extremity? {
        if discoveryMethod == .bluetoothProximity, let softwareVersion = readers.first?.deviceSoftwareVersion {
            return Section.Extremity.title("Reader software: \(softwareVersion)")
        } else if self.discoveryConfig.discoveryMethod == .internet {
            // This is not dynamic: doesn't detect & update when network changes.
            // It's not the right solutions for store clerks, who shouldn't need to know
            // the network config, but may be a useful sanity check for developers
            // w/connectivity problems
            return Section.Extremity.title("Device IP: \(Ifaddrs_h.getWifiIPAddress() ?? "unknown")")
        } else {
            return nil
        }
    }
}

// MARK: - TerminalDelegate
extension ReaderDiscoveryViewController: TerminalDelegate {
    func terminal(_ terminal: Terminal, didReportUnexpectedReaderDisconnect reader: Reader) {}

    func terminal(_ terminal: Terminal, didChangeConnectionStatus status: ConnectionStatus) {
        updateContent()
    }
}

// MARK: - BluetoothReaderDelegate
extension ReaderDiscoveryViewController: BluetoothReaderDelegate {
    func reader(_ reader: Reader, didReportAvailableUpdate update: ReaderSoftwareUpdate) {
    }

    func reader(_ reader: Reader, didStartInstallingUpdate update: ReaderSoftwareUpdate, cancelable: Cancelable?) {
        updateReaderVC = UpdateReaderViewController(updateBeingInstalled: update, cancelable: cancelable, updateInstalledCompletion: { [unowned self] in
            self.updateReaderVC?.dismiss(animated: true, completion: nil)
        })
        if let vc = updateReaderVC {
            self.present(LargeTitleNavigationController(rootViewController: vc), animated: true, completion: nil)
        }
    }

    func reader(_ reader: Reader, didFinishInstallingUpdate update: ReaderSoftwareUpdate?, error: Error?) {
    }

    func reader(_ reader: Reader, didReportReaderSoftwareUpdateProgress progress: Float) {
    }

    func reader(_ reader: Reader, didRequestReaderInput inputOptions: ReaderInputOptions = []) {
    }

    func reader(_ reader: Reader, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {
    }
}

// MARK: - LocalMobileReaderDelegate
extension ReaderDiscoveryViewController: LocalMobileReaderDelegate {
    func localMobileReader(_ reader: Reader, didStartInstallingUpdate update: ReaderSoftwareUpdate, cancelable: Cancelable?) {
        updateReaderVC = UpdateReaderViewController(updateBeingInstalled: update, cancelable: cancelable, updateInstalledCompletion: { [unowned self] in
            self.updateReaderVC?.dismiss(animated: true, completion: nil)
        })
        if let vc = updateReaderVC {
            self.present(LargeTitleNavigationController(rootViewController: vc), animated: true, completion: nil)
        }
    }

    func localMobileReader(_ reader: Reader, didReportReaderSoftwareUpdateProgress progress: Float) {
    }

    func localMobileReader(_ reader: Reader, didFinishInstallingUpdate update: ReaderSoftwareUpdate?, error: Error?) {
    }

    func localMobileReaderDidAcceptTermsOfService(_ reader: Reader) {
    }

    func localMobileReader(_ reader: Reader, didRequestReaderInput inputOptions: ReaderInputOptions = []) {
    }

    func localMobileReader(_ reader: Reader, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {
    }
}

// MARK: - DiscoveryDelegate
extension ReaderDiscoveryViewController: DiscoveryDelegate {
    func terminal(_ terminal: Terminal, didUpdateDiscoveredReaders readers: [Reader]) {
        self.readers = readers
        switch (self.discoveryConfig.discoveryMethod, readers.count) {
        case (.bluetoothProximity, 1) where readers.first?.batteryLevel != nil:
            // Once we've received battery level, don't expect further callbacks
            viewState = .doneDiscovering
        case (.internet, _):
            // internet only has one callback
            viewState = .doneDiscovering
        default:
            // If receiving `didUpdateDiscoveredReaders` calls, still actively discovering.
            // This also covers the case where the `.bluetoothProximity` Reader goes away.
            viewState = .discovering
        }
        updateContent()
    }
}

// MARK: - Location extension
extension Location {
    var displayString: String {
        return self.displayName ?? self.stripeId
    }
}
