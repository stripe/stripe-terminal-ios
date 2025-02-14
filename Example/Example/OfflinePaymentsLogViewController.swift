//
//  OfflinePaymentsLogViewController.swift
//  Example
//
//  Created by Mindy Lou on 7/12/22.
//  Copyright © 2022 Stripe. All rights reserved.
//

import Static
import StripeTerminal

class OfflinePaymentsLogViewController: TableViewController {

    static let directoryURL = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)[0]
    static let dictionaryURL = URL(fileURLWithPath: "offlineIntentsLog", relativeTo: directoryURL)
        .appendingPathExtension("plist")

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "Offline Logs"
        navigationItem.rightBarButtonItems = [
            UIBarButtonItem(title: "Clear", style: .plain, target: self, action: #selector(clearLogs)),
            UIBarButtonItem(title: "Export", style: .plain, target: self, action: #selector(exportLogs)),
        ]
        updateContent()
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        updateContent()
    }

    private func updateContent() {
        do {
            let data = try Data(contentsOf: OfflinePaymentsLogViewController.dictionaryURL)
            let offlineLogDictionary =
                try NSKeyedUnarchiver.unarchivedObject(ofClasses: [NSDictionary.self, NSString.self], from: data)
                as! [String: String]
            var rows = [Row]()
            let sortedKeys = offlineLogDictionary.keys.sorted(by: <)
            sortedKeys.forEach {
                rows.append(rowForKey($0, value: offlineLogDictionary[$0]))
            }
            dataSource.sections = [Section(rows: rows)]
        } catch {
            dataSource.sections = [
                Section(rows: [
                    Row(
                        text: "Error accessing offline payment logs from disk (logs may be empty)",
                        cellClass: Value1MultilineCell.self
                    )
                ])
            ]
        }
    }

    private func rowForKey(_ key: String, value: String?) -> Row {
        return Row(
            text: key,
            detailText: value,
            selection: { [unowned self] in
                if let stringValue = value, !stringValue.isEmpty {
                    let vc = OfflinePaymentsLogDetailViewController(string: stringValue)
                    self.navigationController?.pushViewController(vc, animated: true)
                }
            },
            accessory: !(value?.isEmpty ?? true) ? .disclosureIndicator : .none,
            cellClass: Value1MultilineCell.self
        )
    }

    @objc
    func clearLogs() {
        do {
            try FileManager.default.removeItem(at: OfflinePaymentsLogViewController.dictionaryURL)
        } catch {
            print("‼️ Error removing log url from disk: \(error)")
        }
        updateContent()
    }

    @objc
    func exportLogs() {
        let activityController = UIActivityViewController(
            activityItems: [OfflinePaymentsLogViewController.dictionaryURL],
            applicationActivities: nil
        )
        activityController.completionWithItemsHandler = { (_, _, _, error) in
            if let e = error {
                self.presentAlert(error: e)
            }
        }
        present(activityController, animated: true, completion: nil)
    }

    static func writeLogToDisk(_ logString: String, details: PaymentIntent? = nil) {
        var offlineLogDictionary: NSDictionary = [:]
        do {
            let data = try Data(contentsOf: OfflinePaymentsLogViewController.dictionaryURL)
            offlineLogDictionary =
                try NSKeyedUnarchiver.unarchivedObject(ofClasses: [NSDictionary.self, NSString.self], from: data)
                as! NSDictionary
            let mutableOfflineLogDictionary = NSMutableDictionary(dictionary: offlineLogDictionary)
            if let originalJSON = details?.originalJSON,
                !originalJSON.isEmpty,
                let data = try? JSONSerialization.data(withJSONObject: originalJSON, options: .prettyPrinted),
                let jsonString = String(data: data, encoding: .utf8)
            {
                mutableOfflineLogDictionary[logString] = jsonString
            } else {
                mutableOfflineLogDictionary[logString] = ""
            }
            offlineLogDictionary = mutableOfflineLogDictionary
        } catch {
            print("‼️ Error accessing offline payment logs from disk: \(error.localizedDescription)")
            offlineLogDictionary = [logString: details?.description ?? ""]
        }
        do {
            let newData = try NSKeyedArchiver.archivedData(
                withRootObject: offlineLogDictionary,
                requiringSecureCoding: true
            )
            try newData.write(to: OfflinePaymentsLogViewController.dictionaryURL)
        } catch {
            print("‼️ Error archiving and writing data to offline payment logs to disk: \(error.localizedDescription)")
        }
    }

}
