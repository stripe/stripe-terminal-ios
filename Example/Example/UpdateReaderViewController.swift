//
//  UpdateReaderViewController.swift
//  Example
//
//  Created by Ben Guo on 9/29/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class UpdateReaderViewController: TableViewController, CancelableViewController {
    // This VC is used in two slightly different instances.
    //
    // 1. To view details about an optional update that is available and optionally start installing it
    // 2. To report the progress and allow canceling a required update that has started installing during connect.
    //
    // This enum is to make it easier to read in the few places where we show some more information when its a required
    // update being installed.
    private enum UpdateType {
        case available
        case required
    }
    private let updateType: UpdateType

    private let headerView = ReaderHeaderView()
    private weak var doneButton: UIBarButtonItem?
    internal weak var cancelButton: UIBarButtonItem?

    private var update: ReaderSoftwareUpdate?
    private var updateProgress: Float?
    private var updateInstalledCompletion: () -> Void

    internal var cancelable: Cancelable? = nil {
        didSet {
            updateContent()
        }
    }

    /// Initializer to use when an update is available and can optionally be installed
    convenience init(update: ReaderSoftwareUpdate, updateInstalledCompletion: @escaping () -> Void) {
        self.init(update: update, type: .available, updateInstalledCompletion: updateInstalledCompletion)
        self.title = "Update Reader"
    }

    /// Initializer to use  when a required update has started installing to provide the cancelable for that update.
    convenience init(updateBeingInstalled: ReaderSoftwareUpdate, cancelable: Cancelable?, updateInstalledCompletion: @escaping () -> Void) {
        self.init(update: updateBeingInstalled, type: .required, updateInstalledCompletion: updateInstalledCompletion)
        self.cancelable = cancelable
        setAllowedCancelMethods(cancelable == nil ? [] : [.button])
        self.updateProgress = 0.0
        self.title = "Installing Update"
    }

    private init(update: ReaderSoftwareUpdate, type: UpdateType, updateInstalledCompletion: @escaping () -> Void) {
        self.update = update
        self.updateInstalledCompletion = updateInstalledCompletion
        self.updateType = type
        super.init(style: .grouped)
        TerminalDelegateAnnouncer.shared.addListener(self)
        BluetoothReaderDelegateAnnouncer.shared.addListener(self)
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

        let doneButton = UIBarButtonItem(barButtonSystemItem: .done, target: self, action: #selector(doneAction))
        doneButton.isEnabled = false
        self.doneButton = doneButton
        let cancelButton = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(cancelAction))
        self.cancelButton = cancelButton
        navigationItem.leftBarButtonItem = cancelButton
        navigationItem.rightBarButtonItem = doneButton

        headerView.connectedReader = Terminal.shared.connectedReader
        headerView.connectionStatus = Terminal.shared.connectionStatus
        updateContent()
    }

    private func installUpdate() {
        // Don't allow swiping away during an install to prevent accidentally canceling the update.
        setAllowedCancelMethods([.button])
        Terminal.shared.installAvailableUpdate()
    }

    private func updateContent() {
        let currentVersion = Terminal.shared.connectedReader?.deviceSoftwareVersion ?? "unknown"
        let updateButtonText: String
        let updateFooter: String
        let updateRow: Row
        if let progress = updateProgress {
            let percent = Int(progress*100)
            var footerStrings = [
                "Update progress: \(percent)%",
                updateVersionText(),
                "⚠️ The reader will temporarily become unresponsive. Do not leave this page, and keep the reader in range and powered on until the update is complete."
            ]
            if updateType == .required {
                footerStrings.append("⚠️ This update is required for this reader to be used. Canceling the update will cancel the connection to the reader.")
            }
            updateFooter = footerStrings.joined(separator: "\n\n")
            updateRow = Row(text: "⏱ \(updateType == .required ? "Required update" : "Update") in progress")
        } else if cancelable != nil {
            updateFooter = "Starting to install update..."
            updateRow = Row(text: "Installing Update")
        } else if update != nil {
            updateFooter = updateVersionText()
            updateButtonText = "Install update"
            updateRow = Row(text: updateButtonText, selection: { [unowned self] in
                self.installUpdate()
                }, cellClass: ButtonCell.self)
        } else {
            // The update has been installed
            updateRow = Row(text: "✅ Update Installed")
            updateFooter = ""
        }

        // Build out the target section
        var downArrow: Section.Extremity?
        var targetSection: Section?
        if update?.deviceSoftwareVersion != nil {
            targetSection = Section(header: "Target Version", rows: [
                Row(text: update?.deviceSoftwareVersion, cellClass: Value1MultilineCell.self)
            ])

            if #available(iOS 13.0, *) {
                // Cram a nice down arrow in between the two versions to clarify what's being installed
                let imageView = UIImageView(image: UIImage(systemName: "arrow.down.circle.fill"))
                imageView.contentMode = .scaleAspectFit
                let spacer = UIView()
                let stack = UIStackView(arrangedSubviews: [spacer, imageView])
                stack.axis = .vertical
                stack.spacing = 20
                downArrow = .autoLayoutView(stack)
            }
        }

        dataSource.sections = [
            Section(header: "", rows: [], footer: Section.Extremity.view(headerView)),
            Section(header: "Current Version", rows: [
                Row(text: currentVersion, cellClass: Value1MultilineCell.self),
            ], footer: downArrow),
            targetSection,
            Section(header: "", rows: [updateRow], footer: Section.Extremity.title(updateFooter))
        ].compactMap { $0 }

        // Prevent cancel to dismiss during a required update that doesn't have a cancelable
        setAllowedCancelMethods(updateType == .required && cancelable == nil ? [] : [.button])
    }

    @objc
    func cancelAction() {
        if let cancelable = cancelable {
            setAllowedCancelMethods([])
            cancelable.cancel { error in
                self.setAllowedCancelMethods(.all)

                if self.updateType == .required && (error as NSError?)?.code == ErrorCode.cancelFailedAlreadyCompleted.rawValue {
                    // Required updates auto dismiss on success, so if the cancel failed because install finished
                    // so for now, drop the error and let the dismiss happen.
                    return
                } else if let error = error {
                    self.presentAlert(error: error)
                }
            }
        } else {
            dismiss(animated: true, completion: nil)
        }
    }

    @objc
    func doneAction() {
        dismiss(animated: true, completion: nil)
    }

    func updateVersionText() -> String {
        guard let update = update else {
            return ""
        }
        let updateEstimate = ReaderSoftwareUpdate.string(from: update.estimatedUpdateTime)
        var components = [String]()
        if update.components.contains(.config) {
            components.append("Config")
        }
        if update.components.contains(.firmware) {
            components.append("Firmware")
        }
        if update.components.contains(.keys) {
            components.append("Keys")
        }
        if update.components.contains(.incremental) {
            components.append("Incremental")
        }

        return "Components to update: \(components.joined(separator: ","))\n\nEstimated update time: \(updateEstimate)"
    }
}

// MARK: TerminalDelegate
extension UpdateReaderViewController: TerminalDelegate {
    func terminal(_ terminal: Terminal, didChangeConnectionStatus status: ConnectionStatus) {
        // If we're in this VC and not connected we're doing a required install.
        // Transitioning from that to not connected should auto-dismiss (canceled the install)
        if headerView.connectionStatus != .connected && status == .notConnected {
            self.dismiss(animated: true, completion: nil)
            return
        }

        headerView.connectionStatus = status
    }

    func terminal(_ terminal: Terminal, didReportUnexpectedReaderDisconnect reader: Reader) {
        presentAlert(title: "Reader disconnected!", message: "\(reader.serialNumber)") { _ in
            self.dismiss(animated: true, completion: nil)
        }
        headerView.connectedReader = nil
    }
}

// MARK: BluetoothReaderDelegate
extension UpdateReaderViewController: BluetoothReaderDelegate {
    func reader(_ reader: Reader, didReportReaderSoftwareUpdateProgress progress: Float) {
        updateProgress = progress
        updateContent()
    }

    func reader(_ reader: Reader, didReportAvailableUpdate update: ReaderSoftwareUpdate) {
    }

    func reader(_ reader: Reader, didStartInstallingUpdate update: ReaderSoftwareUpdate, cancelable: Cancelable?) {
        self.cancelable = cancelable
    }

    func reader(_ reader: Reader, didFinishInstallingUpdate update: ReaderSoftwareUpdate?, error: Error?) {
        // Only present the error or show success if it was an available update. Required updates will also be
        // receiving the `connectBluetoothReader` completion with success or error and that completion dismisses
        // this VC and presents any errors if needed.
        guard updateType == .available else {
            return
        }

        if let e = error {
            self.presentAlert(error: e)
        }
        self.updateProgress = nil
        if error == nil {
            self.presentAlert(title: "Update successful", message: "The reader has been updated to \(update?.deviceSoftwareVersion ?? "no update available").")
            self.doneButton?.isEnabled = true
            self.setAllowedCancelMethods([.swipe])
            self.update = nil
            self.updateInstalledCompletion()
        }
        self.cancelable = nil
    }

    func reader(_ reader: Reader, didRequestReaderInput inputOptions: ReaderInputOptions = []) {
    }

    func reader(_ reader: Reader, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {
    }
}
