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

class StartReaderSettingsViewController: TableViewController {
    enum ReaderSettingsError: Error {
        case noResponse
    }

    private var error: Error?
    private var readerSettings: ReaderSettings?
    private var textToSpeechSpeakers: Bool = false

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
        let sections: [Section?] =
            if let error = error {
                [
                    Section(
                        header: "Something went wrong",
                        rows: renderError(error)
                    ),
                    Section(
                        rows: [
                            Row(
                                text: "Try again",
                                selection: { [unowned self] in
                                    self.retrieveReaderSettings()
                                },
                                cellClass: ButtonCell.self
                            )
                        ]
                    ),
                ]
            } else {
                [
                    makeAccessibilitySection()
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
