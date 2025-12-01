//
//  QrCodeViewController.swift
//  Stripe POS
//
//  Created by Stripe on 11/7/25.
//  Copyright © 2025 Stripe. All rights reserved.
//

import StripeTerminal
import UIKit

final class QrCodeViewController: UIViewController {
    private let qrData: QrCodeDisplayData

    init(qrData: QrCodeDisplayData) {
        self.qrData = qrData
        super.init(nibName: nil, bundle: nil)
    }

    @available(*, unavailable)
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        let paymentMethodName = qrData.paymentMethodType.displayName
        self.title = "\(paymentMethodName) QR Code"
        self.view.backgroundColor = .systemBackground

        let scrollView = UIScrollView()
        scrollView.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(scrollView)

        let contentView = UIView()
        contentView.translatesAutoresizingMaskIntoConstraints = false
        scrollView.addSubview(contentView)

        let imageView = UIImageView()
        imageView.translatesAutoresizingMaskIntoConstraints = false
        imageView.contentMode = .scaleAspectFit
        imageView.backgroundColor = .white
        contentView.addSubview(imageView)

        let instructionLabel = UILabel()
        instructionLabel.translatesAutoresizingMaskIntoConstraints = false
        instructionLabel.text = "Customer should scan this QR code with their \(paymentMethodName) app"
        instructionLabel.textAlignment = .center
        instructionLabel.numberOfLines = 0
        contentView.addSubview(instructionLabel)

        let expiresLabel = UILabel()
        expiresLabel.translatesAutoresizingMaskIntoConstraints = false
        expiresLabel.text = "Expires: \(Date(timeIntervalSince1970: qrData.expiresAtMs / 1000))"
        expiresLabel.textAlignment = .center
        expiresLabel.font = .systemFont(ofSize: 12)
        expiresLabel.textColor = .gray
        contentView.addSubview(expiresLabel)

        NSLayoutConstraint.activate([
            scrollView.topAnchor.constraint(equalTo: view.topAnchor),
            scrollView.leadingAnchor.constraint(equalTo: view.leadingAnchor),
            scrollView.trailingAnchor.constraint(equalTo: view.trailingAnchor),
            scrollView.bottomAnchor.constraint(equalTo: view.bottomAnchor),

            contentView.topAnchor.constraint(equalTo: scrollView.topAnchor),
            contentView.leadingAnchor.constraint(equalTo: scrollView.leadingAnchor),
            contentView.trailingAnchor.constraint(equalTo: scrollView.trailingAnchor),
            contentView.bottomAnchor.constraint(equalTo: scrollView.bottomAnchor),
            contentView.widthAnchor.constraint(equalTo: scrollView.widthAnchor),

            instructionLabel.topAnchor.constraint(equalTo: contentView.topAnchor, constant: 20),
            instructionLabel.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 20),
            instructionLabel.trailingAnchor.constraint(equalTo: contentView.trailingAnchor, constant: -20),

            imageView.topAnchor.constraint(equalTo: instructionLabel.bottomAnchor, constant: 20),
            imageView.centerXAnchor.constraint(equalTo: contentView.centerXAnchor),
            imageView.widthAnchor.constraint(equalToConstant: 300),
            imageView.heightAnchor.constraint(equalToConstant: 300),

            expiresLabel.topAnchor.constraint(equalTo: imageView.bottomAnchor, constant: 20),
            expiresLabel.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 20),
            expiresLabel.trailingAnchor.constraint(equalTo: contentView.trailingAnchor, constant: -20),
            expiresLabel.bottomAnchor.constraint(equalTo: contentView.bottomAnchor, constant: -20),
        ])

        // Close button
        let closeButton = UIBarButtonItem(
            title: "Close",
            style: .done,
            target: self,
            action: #selector(closeTapped)
        )
        navigationItem.rightBarButtonItem = closeButton

        // Load image
        let urlString = qrData.qrCodeImageUrlPng
        if let url = URL(string: urlString) {
            URLSession.shared.dataTask(with: url) { data, _, _ in
                DispatchQueue.main.async {
                    if let data = data, let image = UIImage(data: data) {
                        imageView.image = image
                    } else {
                        imageView.image = nil
                        instructionLabel.text = "Failed to load QR code image\n\nURL: \(urlString)"
                    }
                }
            }.resume()
        } else {
            instructionLabel.text = "Invalid QR code URL: \(urlString)"
        }
    }

    @objc
    private func closeTapped() {
        dismiss(animated: true, completion: nil)
    }
}
