//
//  StartPrintContentViewController.swift
//  Example
//
//  Created by Philip Zhang on 6/18/25.
//  Copyright © 2025 Stripe. All rights reserved.
//

import Static
import StripeTerminal
import UIKit

class StartPrintContentViewController: TableViewController {

    convenience init() {
        self.init(style: .grouped)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        addKeyboardDisplayObservers()
        title = "Print Content"

        updateContent()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        // pop if no reader is connected
        guard Terminal.shared.connectedReader != nil else {
            navigationController?.popViewController(animated: true)
            return
        }
    }

    private func startPrint(image: UIImage) {
        do {
            let content = try PrintContentBuilder(image: image).build()
            let viewController = PrintContentViewController(printContent: content)
            let navigationController = LargeTitleNavigationController(rootViewController: viewController)
            present(navigationController, animated: true)
        } catch {
            presentAlert(error: error)
        }
    }

    private func updateContent() {
        var sections = [Section]()
        let printContentSection = Section(rows: [
            Row(
                text: "Print test image",
                selection: { [unowned self] in
                    startPrint(image: generateTestImage())
                },
                cellClass: ButtonCell.self
            ),
            Row(
                text: "Print image from library",
                selection: { [unowned self] in
                    printImageFromLibrary()
                },
                cellClass: ButtonCell.self
            ),
        ])

        sections.append(printContentSection)
        dataSource.sections = sections
    }

    private func printImageFromLibrary() {
        let imagePicker = UIImagePickerController()
        imagePicker.delegate = self
        imagePicker.sourceType = .photoLibrary
        imagePicker.allowsEditing = false
        present(imagePicker, animated: true)
    }

    private func generateTestImage() -> UIImage {
        let imageWidth = 384
        let imageHeight = 400
        let renderer = UIGraphicsImageRenderer(
            size: CGSize(width: imageWidth, height: imageHeight),
            format: UIGraphicsImageRendererFormat(for: UITraitCollection(displayScale: 1))
        )
        return renderer.image { context in
            let rect = CGRect(x: 0, y: 0, width: imageWidth, height: imageHeight)
            UIColor.white.setFill()
            context.fill(rect)

            let borderWidth = 4
            let borderRect = CGRect(x: 0, y: 0, width: imageWidth, height: imageHeight)
            UIColor.black.setStroke()
            context.cgContext.setLineWidth(CGFloat(borderWidth))
            context.stroke(borderRect)

            let text = "Test Image - 384px wide"
            let attributes: [NSAttributedString.Key: Any] = [
                .font: UIFont.systemFont(ofSize: 28, weight: .bold),
                .foregroundColor: UIColor.black,
            ]
            let textSize = text.size(withAttributes: attributes)
            let textRect = CGRect(
                x: (CGFloat(imageWidth) - textSize.width) / 2,
                y: 50,
                width: textSize.width,
                height: textSize.height
            )
            text.draw(in: textRect, withAttributes: attributes)

            // Add some decorative shapes
            UIColor.black.setFill()
            let circleRect = CGRect(x: 50, y: textRect.maxY + 50, width: 60, height: 60)
            context.cgContext.fillEllipse(in: circleRect)

            let squareRect = CGRect(x: 274, y: textRect.maxY + 90, width: 50, height: 50)
            context.cgContext.fill(squareRect)

            // Draw a cool geometric pattern
            UIColor.black.setFill()
            for i in 0..<8 {
                let angle = Double(i) * .pi / 4
                let radius: CGFloat = 30
                let centerX = rect.midX + cos(angle) * radius
                let centerY = rect.midY + sin(angle) * radius
                context.cgContext.saveGState()
                context.cgContext.translateBy(x: centerX, y: centerY)
                context.cgContext.rotate(by: angle)
                context.cgContext.move(to: CGPoint(x: -10, y: -10))
                context.cgContext.addLine(to: CGPoint(x: 10, y: -10))
                context.cgContext.addLine(to: CGPoint(x: 0, y: 10))
                context.cgContext.closePath()
                context.cgContext.fillPath()
                context.cgContext.restoreGState()
            }
            // Add some connecting lines
            UIColor.black.setStroke()
            context.cgContext.setLineWidth(1)
            for i in 0..<8 {
                let angle1 = Double(i) * .pi / 4
                let angle2 = Double((i + 2) % 8) * .pi / 4
                let radius: CGFloat = 30
                let x1 = rect.midX + cos(angle1) * radius
                let y1 = rect.midY + sin(angle1) * radius
                let x2 = rect.midX + cos(angle2) * radius
                let y2 = rect.midY + sin(angle2) * radius
                context.cgContext.move(to: CGPoint(x: x1, y: y1))
                context.cgContext.addLine(to: CGPoint(x: x2, y: y2))
                context.cgContext.strokePath()
            }

            // Add a second text line
            let subtitle = "Generated with Swift"
            let subtitleAttributes: [NSAttributedString.Key: Any] = [
                .font: UIFont.systemFont(ofSize: 24, weight: .medium),
                .foregroundColor: UIColor.black,
            ]
            let subtitleSize = subtitle.size(withAttributes: subtitleAttributes)
            let subtitleRect = CGRect(
                x: (CGFloat(imageWidth) - subtitleSize.width) / 2,
                y: rect.maxY - 100,
                width: subtitleSize.width,
                height: subtitleSize.height
            )
            subtitle.draw(in: subtitleRect, withAttributes: subtitleAttributes)

            // Add a decorative line
            UIColor.black.withAlphaComponent(0.7).setStroke()
            context.cgContext.setLineWidth(4)
            context.cgContext.move(to: CGPoint(x: 50, y: subtitleRect.maxY + subtitleSize.height + 6))
            context.cgContext.addLine(
                to: CGPoint(x: CGFloat(imageWidth) - 50, y: subtitleRect.maxY + subtitleSize.height + 6)
            )
            context.cgContext.strokePath()
        }
    }
}

// MARK: - UIImagePickerControllerDelegate

extension StartPrintContentViewController: UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    func imagePickerController(
        _ picker: UIImagePickerController,
        didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey: Any]
    ) {
        picker.dismiss(animated: true) { [weak self] in
            if let image = info[.originalImage] as? UIImage {
                self?.startPrint(image: image)
            }
        }
    }

    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        picker.dismiss(animated: true)
    }
}
