//
//  StartReaderSettingsViewController.swift
//  Example
//
//  Created by Max Afonov on 12/6/23.
//  Copyright © 2023 Stripe. All rights reserved.
//

import Foundation
import Static
import StripeTerminal
import UIKit

extension BuzzerVolumeLevel: @retroactive CustomStringConvertible {
    public var description: String {
        switch self {
        case .low: return "Low"
        case .high: return "High"
        case .custom: return "Custom"
        @unknown default: return "Unknown"
        }
    }
}

class StartReaderSettingsViewController: TableViewController {
    enum ReaderSettingsError: Error {
        case noResponse
    }

    private var error: Error?
    private var readerSettings: ReaderSettings?
    private var textToSpeechSpeakers: Bool = false
    private var buzzerVolumeLevel: BuzzerVolumeLevel = .low
    private var customVolume: Int = 1

    convenience init() {
        self.init(style: .grouped)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "Reader settings"
        retrieveReaderSettings()
    }

    private func updateState(withSettings readerSettings: ReaderSettings) {
        error = nil
        self.readerSettings = readerSettings
        textToSpeechSpeakers = readerSettings.accessibility.textToSpeechStatus == .speakers

        if let volume = readerSettings.buzzerVolume.volume {
            if volume.currentVolume == 1 {
                buzzerVolumeLevel = .low
            } else if volume.currentVolume == volume.maxVolume {
                buzzerVolumeLevel = .high
            } else {
                buzzerVolumeLevel = .custom
                customVolume = volume.currentVolume
            }
        }
    }

    private func updateState(withError error: Error) {
        self.error = error
        self.readerSettings = nil
    }

    private func detailRowAccessory(text: String, _ detailText: String?) -> Row.Accessory {
        return if let detailText = detailText {
            .detailButton {
                self.presentAlert(title: text, message: detailText, okButtonTitle: "OK") { _ in }
            }
        } else {
            .none
        }
    }

    private func detailRow(text: String, detailText: String? = nil) -> Row {
        return Row(
            text: text,
            detailText: detailText,
            accessory: detailRowAccessory(text: text, detailText)
        )
    }

    private func renderError(_ error: Error) -> [Row] {
        [
            Row(text: "Domain", detailText: "\(error.domain)"),
            Row(text: "Code", detailText: "\(error.code)"),
            detailRow(text: "Description", detailText: "\(error.localizedDescription)"),
        ]
            + error.scp_userInfo.map {
                detailRow(text: "\($0)", detailText: "\($1)")
            }
    }

    private func updateContent() {
        let tryAgainSection = Section(
            rows: [
                Row(
                    text: "Try again",
                    selection: { [unowned self] in
                        self.retrieveReaderSettings()
                    },
                    cellClass: ButtonCell.self
                )
            ]
        )

        let sections: [Section?] =
            if let error = error {
                [
                    Section(
                        header: "Something went wrong",
                        rows: renderError(error)
                    ),
                    tryAgainSection,
                ]
            } else {
                [
                    makeAccessibilitySection(),
                    makeBuzzerVolumeSection(),
                    tryAgainSection,
                ]
            }

        dataSource.sections = sections.compactMap { $0 }
    }

    private func makeAccessibilitySection() -> Section? {
        if let error = readerSettings?.accessibility.error {
            return Section(
                header: "Accessibility error",
                rows: renderError(error),
                footer: "Accessibility settings could not be loaded."
            )
        } else if readerSettings?.accessibility != nil {
            return Section(
                header: "Accessibility",
                rows: [
                    Row(
                        text: "Enable text-to-speech via speakers",
                        accessory: .switchToggle(value: self.textToSpeechSpeakers) { [unowned self] _ in
                            self.textToSpeechSpeakers.toggle()
                            self.updateContent()
                        }
                    ),
                    Row(
                        text: "Save accessibility settings",
                        selection: { [unowned self] in
                            self.setAccessibilitySettings()
                        },
                        cellClass: ButtonCell.self
                    ),
                ]
            )
        } else {
            return nil
        }
    }

    private func makeBuzzerVolumeSection() -> Section? {
        guard let readerSettings = readerSettings else { return nil }
        guard let volume = readerSettings.buzzerVolume.volume else { return nil }

        var rows: [Row] = [
            Row(text: "Current volume", detailText: "\(volume.currentVolume) / \(volume.maxVolume)"),
            Row(
                text: "Volume level",
                detailText: buzzerVolumeLevel.description,
                selection: { [unowned self] in
                    self.presentValuePicker(
                        title: "Select volume level",
                        options: [BuzzerVolumeLevel.low, .high, .custom]
                    ) { [weak self] selected in
                        guard let self, let selected else { return }
                        if selected == .custom {
                            self.presentCustomVolumeEntry(maxVolume: volume.maxVolume)
                        } else {
                            self.buzzerVolumeLevel = selected
                            self.updateContent()
                        }
                    }
                },
                accessory: .disclosureIndicator
            ),
        ]

        if buzzerVolumeLevel == .custom {
            rows.append(
                Row(
                    text: "Custom volume",
                    detailText: "\(customVolume)",
                    selection: { [unowned self] in
                        self.presentCustomVolumeEntry(maxVolume: volume.maxVolume)
                    },
                    accessory: .disclosureIndicator
                )
            )
        }

        rows.append(
            Row(
                text: "Save buzzer volume",
                selection: { [unowned self] in
                    self.setBuzzerVolume()
                },
                cellClass: ButtonCell.self
            )
        )

        return Section(header: "Buzzer volume", rows: rows)
    }

    private func presentCustomVolumeEntry(maxVolume: Int) {
        let alert = UIAlertController(
            title: "Custom volume",
            message: "Enter a value from 1 to \(maxVolume)",
            preferredStyle: .alert
        )
        alert.addTextField { field in
            field.keyboardType = .numberPad
            field.placeholder = "1–\(maxVolume)"
            if self.buzzerVolumeLevel == .custom {
                field.text = "\(self.customVolume)"
            }
        }
        alert.addAction(
            UIAlertAction(title: "OK", style: .default) { [weak self, weak alert] _ in
                guard let self,
                    let text = alert?.textFields?.first?.text,
                    let value = Int(text)
                else { return }
                self.customVolume = value
                self.buzzerVolumeLevel = .custom
                self.updateContent()
            }
        )
        alert.addAction(UIAlertAction(title: "Cancel", style: .cancel))
        present(alert, animated: true)
    }

    private func setBuzzerVolume() {
        let params: BuzzerVolumeParameters
        switch buzzerVolumeLevel {
        case .low:
            params = BuzzerVolumeParameters(level: .low)
        case .high:
            params = BuzzerVolumeParameters(level: .high)
        case .custom:
            params = BuzzerVolumeParameters(volume: customVolume)
        @unknown default:
            return
        }
        Terminal.shared.setReaderSettings(params) { [weak self] readerSettings, error in
            guard let self else { return }
            if let error {
                self.presentAlert(error: error)
            } else if let readerSettings {
                self.updateState(withSettings: readerSettings)
                self.updateContent()
                let current = readerSettings.buzzerVolume.volume?.currentVolume
                self.presentAlert(
                    title: "Buzzer volume updated",
                    message: current.map { "Volume set to \($0)" } ?? "Done"
                )
            }
        }
    }

    private func readerSettingsCallback(readerSettings: ReaderSettings?, error: Error?) {
        if let readerSettings = readerSettings {
            updateState(withSettings: readerSettings)
        } else {
            updateState(withError: error ?? ReaderSettingsError.noResponse)
        }

        updateContent()
    }

    private func retrieveReaderSettings() {
        Terminal.shared.retrieveReaderSettings(readerSettingsCallback)
    }

    private func setAccessibilitySettings() {
        let params: ReaderSettingsParameters

        do {
            let builder = ReaderAccessibilityParametersBuilder()
            builder.setTextToSpeechViaSpeakers(textToSpeechSpeakers)
            params = try builder.build()
        } catch {
            presentAlert(error: error)
            return
        }

        Terminal.shared.setReaderSettings(params, completion: readerSettingsCallback)
    }
}
