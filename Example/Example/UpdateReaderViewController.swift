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
    private var checkingForUpdate: Bool = false {
        didSet {
            updateContent()
        }
    }

    private var installUpdateBlock: ((Bool) -> ())? = nil {
        didSet {
            updateContent()
        }
    }
    private var update: ReaderSoftwareUpdate? = nil
    private var updateProgress: Float? = nil
    private var updateCancelable: Cancelable? = nil

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
        checkingForUpdate = true
        updateCancelable = Terminal.shared.checkForReaderSoftwareUpdate(delegate: self) { error in
            if let error = error {
                self.updateCancelable = nil
                self.presentAlert(error: error)
            }
            self.checkingForUpdate = false
        }
    }

    private func installUpdate() {
        installUpdateBlock?(true)
    }

    private func updateContent() {
        let currentVersion = Terminal.shared.connectedReader?.deviceSoftwareVersion ?? "unknown"
        let canInstallUpdate = installUpdateBlock != nil
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
            else {
                updateButtonText = "Install update"
                let updateEstimate = ReaderSoftwareUpdate.string(fromUpdateTimeExtimate: update.estimatedUpdateTime)
                updateFooter = "Target version:\n\(updateVersion)\n\nThe reader will become unresponsive until the update is complete. Estimated update time: \(updateEstimate)"
                updateRow = Row(text: updateButtonText, selection: { [unowned self] in
                    self.installUpdate()
                }, cellClass: ButtonCell.self)
            }
        }
        else {
            updateButtonText = "Check for update"
            if checkingForUpdate {
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
        if installUpdateBlock != nil {
            dismiss(animated: true, completion: nil)
        }
        else if let cancelable = updateCancelable {
            cancelable.cancel { error in
                if let error = error {
                    self.presentAlert(error: error)
                }
            }
        }
        else {
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

    // MARK: ReaderSoftwareUpdateDelegate
    func terminal(_ terminal: Terminal, readerSoftwareUpdateAvailable update: ReaderSoftwareUpdate, installUpdate: @escaping InstallUpdateBlock) {
        self.update = update
        self.installUpdateBlock = installUpdate
        updateContent()
    }

    func terminal(_ terminal: Terminal, didReportReaderSoftwareUpdateProgress progress: Float) {
        updateProgress = progress
        updateContent()
    }

    func terminal(_ terminal: Terminal, didCompleteReaderSoftwareUpdate error: Error?) {
        if let e = error {
            presentAlert(error: e)
        }
        else {
            presentAlert(title: "Update successful", message: "If the reader is still unresponsive, you may need to restart or reconnect to the reader.")
        }
        installUpdateBlock = nil
        updateProgress = nil
        updateCancelable = nil
        updateContent()
        cancelButton?.isEnabled = false
        doneButton?.isEnabled = true
    }

}
