//
//  ReaderHeaderView.swift
//  Example
//
//  Created by Ben Guo on 9/6/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import StripeTerminal

class ReaderHeaderView: UIView {

    var connectedReader: Reader? = nil {
        didSet {
            updateContent()
        }
    }

    var connectionStatus: ConnectionStatus = .notConnected {
        didSet {
            updateContent()
        }
    }

    private let imageView = UIImageView()
    private let titleLabel = UILabel()
    private let subtitleLabel = UILabel()
    private let spacerLabel = UILabel()
    private let titleFont = UIFont.systemFont(ofSize: UIFont.labelFontSize,
                                              weight: UIFont.Weight.medium)
    private let subtitleFont = UIFont.systemFont(ofSize: 14)
    private let titleColor = UIColor.darkText
    private let subtitleColor = UIColor.gray

    override init(frame: CGRect = .zero) {
        super.init(frame: frame)

        imageView.contentMode = .scaleAspectFit

        titleLabel.textAlignment = .center
        titleLabel.font = titleFont
        titleLabel.textColor = titleColor

        subtitleLabel.textAlignment = .center
        subtitleLabel.textColor = subtitleColor
        subtitleLabel.font = subtitleFont

        spacerLabel.font = titleFont
        spacerLabel.text = "      "

        let stack = UIStackView(arrangedSubviews: [
            imageView,
            titleLabel,
            subtitleLabel,
            spacerLabel
        ])
        stack.spacing = 5
        stack.axis = .vertical

        addSubview(stack)

        stack.translatesAutoresizingMaskIntoConstraints = false
        let insets = UIEdgeInsets(top: 14, left: 16, bottom: 10, right: 16)
        if #available(iOS 11.0, *) {
            stack.anchor(to: safeAreaLayoutGuide, withInsets: insets)
        } else {
            stack.anchorToSuperviewAnchors(withInsets: insets)
        }

        bounds.size.height = 110
        let hardcodedImageViewHeight: CGFloat = 38
        imageView.heightAnchor.constraint(equalToConstant: hardcodedImageViewHeight).isActive = true

        updateContent()

        BluetoothReaderDelegateAnnouncer.shared.addListener(self)
    }

    deinit {
        BluetoothReaderDelegateAnnouncer.shared.removeListener(self)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    func updateContent() {
        func setUIForReader(_ reader: Reader) {
            titleLabel.text = "\(Terminal.stringFromDeviceType(reader.deviceType)) \(reader.label ?? reader.serialNumber)"

            switch reader.deviceType {
            case .stripeM2:
                imageView.image = UIImage(named: "stripe_m2")
            case .chipper1X, .chipper2X, .wiseCube:
                imageView.image = UIImage(named: "chipper")
            case .verifoneP400:
                imageView.image = UIImage(named: "verifone")
            case .wisePad3:
                imageView.image = UIImage(named: "wisepad")
            case .wisePosE:
                imageView.image = UIImage(named: "verifone")
            @unknown default:
                imageView.image = nil
            }
        }

        func displayConnectionStatus(inLabel label: UILabel, reader: Reader?, status: ConnectionStatus) {
            var subtitleStrings = [String]()
            switch status {
            case .notConnected:
                // handled above when connectedReader == nil
                break
            case .connecting:
                subtitleStrings.append("Connecting")
            case .connected where connectedReader?.simulated ?? false:
                subtitleStrings.append("Connected, simulated")
            case .connected:
                subtitleStrings.append("Connected")
                if let locationName = reader?.location?.displayName {
                    subtitleStrings.append(locationName)
                } else if let locationId = reader?.locationId, !locationId.isEmpty {
                    subtitleStrings.append(locationId)
                }
            @unknown default:
                subtitleStrings.append("\(status)")
            }

            if let battery = reader?.batteryLevel, let isCharging = reader?.isCharging?.boolValue {
                subtitleStrings.append("\(isCharging ? "🔌" : "🔋") \(Int(battery.doubleValue * 100.0))%")
            }

            label.text = subtitleStrings.joined(separator: " – ")
        }

        if let reader = connectedReader {
            titleLabel.isHidden = false
            spacerLabel.isHidden = true
            setUIForReader(reader)
        } else {
            subtitleLabel.text = "No reader connected"
            titleLabel.isHidden = true
            spacerLabel.isHidden = false
            imageView.image = UIImage(named: "chipper_empty")
        }

        displayConnectionStatus(inLabel: subtitleLabel, reader: connectedReader, status: connectionStatus)
    }
}

extension ReaderHeaderView: BluetoothReaderDelegate {
    func reader(_ reader: Reader, didReportBatteryLevel batteryLevel: Float, status: BatteryStatus, isCharging: Bool) {
        updateContent()
    }

    // Intentionally blank - only interested in battery status changes
    func reader(_ reader: Reader, didReportAvailableUpdate update: ReaderSoftwareUpdate) {}
    func reader(_ reader: Reader, didStartInstallingUpdate update: ReaderSoftwareUpdate, cancelable: Cancelable?) {}
    func reader(_ reader: Reader, didReportReaderSoftwareUpdateProgress progress: Float) {}
    func reader(_ reader: Reader, didFinishInstallingUpdate update: ReaderSoftwareUpdate?, error: Error?) {}
    func reader(_ reader: Reader, didRequestReaderInput inputOptions: ReaderInputOptions = []) {}
    func reader(_ reader: Reader, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {}
}
