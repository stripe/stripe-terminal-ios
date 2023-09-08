//
//  StartSetReaderDisplayViewController.swift
//  Example
//
//  Created by Matthew Krager on 6/12/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class StartSetReaderDisplayViewController: TableViewController {

    private let totalView = AmountInputView()
    private let taxView = AmountInputView()
    private let currencyView = CurrencyInputView()
    private var setReaderDisplaySection: Section?

    private var lineItems = [CartLineItem]()

    lazy var taxSection = Section(header: Section.Extremity.title("Tax: \(self.taxView.amountString)"), rows: [],
                             footer: Section.Extremity.autoLayoutView(taxView))
    lazy var totalSection = Section(header: Section.Extremity.title("Total: \(self.totalView.amountString)"), rows: [],
                               footer: Section.Extremity.autoLayoutView(totalView))

    convenience init() {
        self.init(style: .grouped)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()
        title = "Set Reader Display"

        totalView.onAmountUpdated = { [unowned self] amountString in
            self.totalSection.header = Section.Extremity.title("Total: \(amountString)")
            self.updateContent()
        }

        taxView.onAmountUpdated = { [unowned self] amountString in
            self.taxSection.header = Section.Extremity.title("Tax: \(amountString)")
            self.updateContent()
        }

        currencyView.onCurrencyUpdated = { [unowned self] currencyString in
            self.totalView.numberFormatter.currencyCode = currencyString
            self.taxView.numberFormatter.currencyCode = currencyString
            self.updateContent()
        }

        let footerString: String
        footerString = "Send the cart to be displayed on the reader. This is not indicitive of what the user will be charged, only what will be displayed."

        self.setReaderDisplaySection = Section(header: nil, rows: [
            Row(text: "Set Reader Display", selection: { [unowned self] in
                self.startSetReaderDisplay()
            }, cellClass: ButtonCell.self),
        ], footer: Section.Extremity.title(footerString))

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

    internal func startSetReaderDisplay() {
        do {
            let cart = try CartBuilder(currency: currencyView.currency)
                .setTax(Int(taxView.amount))
                .setTotal(Int(totalView.amount))
                .setLineItems(lineItems)
                .build()

            Terminal.shared.setReaderDisplay(cart) { [weak self] error in
                guard let self = self else {
                    return
                }

                if let error = error {
                    self.presentAlert(error: error)
                } else {
                    self.presentAlert(title: "Set Reader Display", message: "Successfully updated the display with the specified cart")
                }
            }
        } catch {
            self.presentAlert(error: error)
        }
    }

    internal func clearReaderDisplay() {
        Terminal.shared.clearReaderDisplay { [weak self] error in
            guard let self = self else { return }

            if let error = error {
                self.presentAlert(error: error)
            } else {
                self.presentAlert(title: "Clear Reader Display", message: "Successfully cleared the display back to the splash screen")
            }
        }
    }

    internal func addLineItem() {
        let alertController = UIAlertController(title: "Add New Line Item", message: "", preferredStyle: UIAlertController.Style.alert)
        alertController.addTextField { (textField: UITextField) -> Void in
            textField.placeholder = "Display Name"
        }
        alertController.addTextField { (textField: UITextField) -> Void in
            textField.placeholder = "Price"
            textField.keyboardType = .numberPad
        }
        alertController.addTextField { (textField: UITextField) -> Void in
            textField.placeholder = "Quantity"
            textField.keyboardType = .numberPad
        }

        let createAction = UIAlertAction(title: "Create", style: UIAlertAction.Style.default, handler: { [unowned self] _ -> Void in
            guard let displayNameTextField = alertController.textFields?[0],
                let priceTextField = alertController.textFields?[1],
                let quantityTextField = alertController.textFields?[2],
                let displayName = displayNameTextField.text,
                let quantity = Int(quantityTextField.text ?? "0"),
                let amount = Int(priceTextField.text ?? "0") else {
                return
            }

            do {
                let lineItem = try CartLineItemBuilder(displayName: displayName)
                    .setAmount(amount)
                    .setQuantity(quantity)
                    .build()
                lineItems.append(lineItem)
            } catch {
                self.presentAlert(error: error)
            }
            self.updateContent()
        })
        let cancelAction = UIAlertAction(title: "Cancel", style: UIAlertAction.Style.default, handler: { (_: UIAlertAction!) -> Void in })

        alertController.addAction(cancelAction)
        alertController.addAction(createAction)

        self.present(alertController, animated: true, completion: nil)
    }

    private func updateContent() {
        let currencySection = Section(header: "Currency", rows: [],
                                      footer: Section.Extremity.autoLayoutView(currencyView))

        var lineItemsRows: [Row] = []
        for lineItem in self.lineItems {
            let row = Row(text: lineItem.displayName, detailText: "\(lineItem.amount) ×\(lineItem.quantity)", selection: .none, image: nil, accessory: .none, cellClass: SubtitleCell.self, context: nil, editActions: [.init(title: "Delete", style: .normal, backgroundColor: .systemRed, backgroundEffect: nil, selection: { [unowned self] (indexPath) in
                self.lineItems.remove(at: indexPath.row)
                self.updateContent()
            })])
            lineItemsRows.append(row)
        }

        lineItemsRows.append(Row(text: "+ Add Line Item", selection: { [unowned self] in
            self.addLineItem()
        }, cellClass: ButtonCell.self))
        let lineItemsSection = Section(header: "Line Items", rows: lineItemsRows)

        let clearReaderDisplaySection = Section(header: nil, rows: [
            Row(text: "Clear Reader Display", selection: { [unowned self] in
                self.clearReaderDisplay()
            }, cellClass: ButtonCell.self),
        ], footer: nil)

        guard let setReaderDisplaySection = self.setReaderDisplaySection else {
            return
        }

        let sections: [Section] = [
            lineItemsSection,
            currencySection,
            taxSection,
            totalSection,
            setReaderDisplaySection,
            clearReaderDisplaySection
        ]

        dataSource.sections = sections
    }
}
