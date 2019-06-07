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
            spacerLabel,
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

        updateContent()
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    func updateContent() {
        if let reader = connectedReader {
            titleLabel.text = "Chipper 2X \(reader.serialNumber)"
            titleLabel.isHidden = false
            spacerLabel.isHidden = true
            imageView.image = UIImage(named: "chipper")
        } else {
            subtitleLabel.text = "No reader connected"
            titleLabel.isHidden = true
            spacerLabel.isHidden = false
            imageView.image = UIImage(named: "chipper_empty")
        }
        switch connectionStatus {
        case .notConnected:
            // handled above when connectedReader == nil
            break;
        case .connecting:
            subtitleLabel.text = "Connecting"
        case .connected where connectedReader?.simulated ?? false:
            subtitleLabel.text = "Connected, simulated"
        case .connected:
            subtitleLabel.text = "Connected"
        @unknown default:
            subtitleLabel.text = "\(connectionStatus)"
        }
    }

}
