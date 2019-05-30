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

class UpdateReaderViewController: TableViewController, TerminalDelegate, ReaderSoftwareUpdateDelegate {

    private let headerView = ReaderHeaderView()
    private weak var doneButton: UIBarButtonItem?
    private weak var cancelButton: UIBarButtonItem?

    private var update: ReaderSoftwareUpdate? = nil
    private var updateProgress: Float? = nil
    private var checkForUpdateCancelable: Cancelable? = nil {
        didSet {
            updateContent()
        }
    }
    private var installUpdateCancelable: Cancelable? = nil {
        didSet {
            updateContent()
        }
    }

    init() {
        super.init(style: .grouped)
        self.title = "Update Reader"
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        let doneButton = UIBarButtonItem(barButtonSystemItem: .done, target: self, action: #selector(doneAction))
        doneButton.isEnabled = false
        self.doneButton = doneButton
        let cancelButton = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(cancelAction))
        cancelButton.isEnabled = true
        self.cancelButton = cancelButton
        navigationItem.leftBarButtonItem = cancelButton
        navigationItem.rightBarButtonItem = doneButton

        Terminal.shared.delegate = self
        headerView.connectedReader = Terminal.shared.connectedReader
        headerView.connectionStatus = Terminal.shared.connectionStatus
        updateContent()
    }

    private func checkForUpdate() {
        checkForUpdateCancelable = Terminal.shared.checkForUpdate({ (update, error) in
            if let error = error {
                self.presentAlert(error: error)
            }

            if update == nil {
                self.presentAlert(title: "No update necessary.", message: "Your reader is already up to date!")
            }

            self.update = update
            self.checkForUpdateCancelable = nil
        })
    }

    private func installUpdate() {
        guard let update = self.update else { return }
        installUpdateCancelable = Terminal.shared.installUpdate(update, delegate: self, completion: { error in
            if let e = error {
                self.presentAlert(error: e)
            }
            self.updateProgress = nil
            if self.installUpdateCancelable != nil {
                if error == nil {
                    self.presentAlert(title: "Update successful", message: "The reader may restart at the end of the update. If this happens, reconnect the app to the reader.")
                    self.cancelButton?.isEnabled = false
                    self.doneButton?.isEnabled = true
                    self.update = nil
                }
                self.installUpdateCancelable = nil
            }
        })
    }

    private func updateContent() {
        let currentVersion = Terminal.shared.connectedReader?.deviceSoftwareVersion ?? "unknown"
        let canInstallUpdate = update != nil
        let updateButtonText: String
        let updateFooter: String
        let updateRow: Row
        if canInstallUpdate {
            guard let update = update else { return }
            let updateVersion = update.deviceSoftwareVersion
            if let progress = updateProgress {
                let percent = Int(progress*100)
                updateFooter = "Update progress: \(percent)%\n\n⚠️ The reader will temporarily become unresponsive. Do not leave this page, and keep the reader in range and powered on until the update is complete."
                updateRow = Row(text: "⏱ Update in progress")
            }
            else if installUpdateCancelable != nil {
                updateFooter = "Starting to install update..."
                updateRow = Row(text: "Installing Update")
            }
            else {
                updateButtonText = "Install update"
                let updateEstimate = ReaderSoftwareUpdate.string(from: update.estimatedUpdateTime)
                updateFooter = "Target version:\n\(updateVersion)\n\nThe reader will become unresponsive until the update is complete. Estimated update time: \(updateEstimate)"
                updateRow = Row(text: updateButtonText, selection: { [unowned self] in
                    self.installUpdate()
                }, cellClass: ButtonCell.self)
            }
        }
        else {
            updateButtonText = "Check for update"
            if checkForUpdateCancelable != nil {
                updateFooter = "Checking for update..."
                updateRow = Row(text: updateButtonText)
            }
            else {
                updateFooter = "Check if a reader software update is available."
                updateRow = Row(text: updateButtonText, selection: { [unowned self] in
                    self.checkForUpdate()
                    }, cellClass: ButtonCell.self)
            }
        }
        dataSource.sections = [
            Section(header: "", rows: [], footer: Section.Extremity.view(headerView)),
            Section(header: "Current Version", rows: [
                Row(text: currentVersion, cellClass: Value1Cell.self)
                ]),
            Section(header: "", rows: [updateRow], footer: Section.Extremity.title(updateFooter)),
        ]
    }

    @objc func cancelAction() {
        if let cancelable = checkForUpdateCancelable ?? installUpdateCancelable {
            self.cancelButton?.isEnabled = false
            cancelable.cancel { error in
                self.cancelButton?.isEnabled = true
                if let error = error {
                    self.presentAlert(error: error)
                }
            }
        } else {
            dismiss(animated: true, completion: nil)
        }
    }

    @objc func doneAction() {
        dismiss(animated: true, completion: nil)
    }

    // MARK: TerminalDelegate
    func terminal(_ terminal: Terminal, didChangeConnectionStatus status: ConnectionStatus) {
        headerView.connectionStatus = status
    }

    func terminal(_ terminal: Terminal, didReportUnexpectedReaderDisconnect reader: Reader) {
        presentAlert(title: "Reader disconnected!", message: "\(reader.serialNumber)") { _ in
            self.dismiss(animated: true, completion: nil)
        }
        headerView.connectedReader = nil
    }

    // MARK: ReaderSoftwareUpdateDelegate

    func terminal(_ terminal: Terminal, didReportReaderSoftwareUpdateProgress progress: Float) {
        updateProgress = progress
        updateContent()
    }
}
