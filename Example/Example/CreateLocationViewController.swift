//
//  CreateLocationViewController.swift
//  Example
//
//  Created by Bibek Ghimire on 3/25/21.
//  Copyright © 2021 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class CreateLocationViewController: TableViewController, CancelableViewController {

    var onCreateLocation: (Location) -> Void = { _ in }
    internal var cancelable: Cancelable?
    internal weak var cancelButton: UIBarButtonItem?

    /// Prevents double-calls of `formSubmit`, and also controls the isEnabled properties
    /// of the form's text fields
    internal var submissionInProgress = false {
        didSet {
            let fieldsEnabled = !submissionInProgress
            displayNameTextField.textField.isEnabled = fieldsEnabled
            addressLine1TextField.textField.isEnabled = fieldsEnabled
            addressLine2TextField.textField.isEnabled = fieldsEnabled
            addressCityTextField.textField.isEnabled = fieldsEnabled
            addressStateTextField.textField.isEnabled = fieldsEnabled
            addressCountryTextField.textField.isEnabled = fieldsEnabled
            addressPostalCodeTextField.textField.isEnabled = fieldsEnabled
            updateContent()
        }
    }

    // MARK: - Form field views
    let displayNameTextField = TextFieldView()
    let addressInputsView = UIStackView()
    let addressLine1TextField = TextFieldView(header: "Line 1")
    let addressLine2TextField = TextFieldView(header: "Line 2")
    let addressCityTextField = TextFieldView(header: "City")
    let addressStateTextField = TextFieldView(header: "State")
    let addressCountryTextField = CountryInputView(header: "Country")
    let addressPostalCodeTextField = TextFieldView(header: "Postal code")

    var message: (text: String, color: UIColor)? {
        didSet {
            updateContent()
        }
    }

    // MARK: - Initializers

    init() {
        super.init(style: .grouped)
        buildAddressInput()
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    // MARK: - ViewController Lifecycle

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "Create Location"
        self.addKeyboardDisplayObservers()

        let cancelButton = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(dismissAction))
        self.cancelButton = cancelButton
        navigationItem.leftBarButtonItem = cancelButton
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(true)
        updateContent()
    }

    // MARK: - TableView & Form Helpers

    private func buildAddressInput() {
        displayNameTextField.textField.autocorrectionType = .no
        displayNameTextField.textField.autocapitalizationType = .words
        displayNameTextField.textField.placeholder = "HQ"

        addressLine1TextField.textField.autocorrectionType = .no
        addressLine1TextField.textField.autocapitalizationType = .words
        addressLine1TextField.textField.placeholder = "510 Townsend St"

        addressLine2TextField.textField.autocorrectionType = .no
        addressLine2TextField.textField.autocapitalizationType = .words

        addressCityTextField.textField.autocorrectionType = .no
        addressCityTextField.textField.autocapitalizationType = .words
        addressCityTextField.textField.placeholder = "San Francisco"

        addressStateTextField.textField.autocorrectionType = .no
        addressStateTextField.textField.autocapitalizationType = .words
        addressStateTextField.textField.placeholder = "CA"

        addressPostalCodeTextField.textField.autocorrectionType = .no
        addressPostalCodeTextField.textField.autocapitalizationType = .none
        addressPostalCodeTextField.textField.placeholder = "94103"

        addressInputsView.addArrangedSubview(addressLine1TextField)
        addressInputsView.addArrangedSubview(addressLine2TextField)
        addressInputsView.addArrangedSubview(addressCityTextField)
        addressInputsView.addArrangedSubview(addressStateTextField)
        addressInputsView.addArrangedSubview(addressCountryTextField)
        addressInputsView.addArrangedSubview(addressPostalCodeTextField)
        addressInputsView.axis = .vertical
    }

    func formSubmit() {
        if submissionInProgress {
            return
        }

        // Validate required parameters have been filled out
        guard let displayName = displayNameTextField.textField.text, !displayName.isEmpty else {
            message = (text: "Please enter a display name", color: UIColor.red)
            return
        }

        guard let line1 = addressLine1TextField.textField.text, !line1.isEmpty else {
            message = (text: "Please enter an address line 1", color: UIColor.red)
            return
        }

        var addressParam: [String: String] = [
            "line1": line1,
            "country": addressCountryTextField.country,
        ]
        if let line2 = addressLine2TextField.textField.text, !line2.isEmpty {
            addressParam["line2"] = line2
        }
        if let city = addressCityTextField.textField.text, !city.isEmpty {
            addressParam["city"] = city
        }
        if let state = addressStateTextField.textField.text, !state.isEmpty {
            addressParam["state"] = state
        }
        if let postal_code = addressPostalCodeTextField.textField.text, !postal_code.isEmpty {
            addressParam["postal_code"] = postal_code
        }

        submissionInProgress = true
        setAllowedCancelMethods([])
        self.message = (text: "Creating location...", color: UIColor.gray)
        AppDelegate.apiClient?.createLocation(displayName: displayName, address: addressParam, completion: {[weak self] response, error in
            // This should be practically impossible since the VC is uncancelable while this request is in-flight but to appease Swift,
            // make sure CreateLocationVC hasn't been dismissed by the time this completion block is called.
            guard let self = self else { return }

            if let error = error {
                self.submissionInProgress = false
                self.message = (text: "Could not create location.", color: UIColor.red)
                self.setAllowedCancelMethods([.button, .swipe])
                print(error)
            } else if let location = response {
                self.message = nil
                self.onCreateLocation(location)
            }
        })
    }

    private func updateContent() {
        let messageView = InsetLabel()
        messageView.inset.left = 16
        messageView.text = message?.text
        messageView.textColor = message?.color
        messageView.sizeToFit()
        let messageSection: Section? = (message != nil)
            ? Section(header: Section.Extremity.view(messageView))
            : nil

        let sections = [
            messageSection,
            Section(header: "Display Name",
                    footer: Section.Extremity.autoLayoutView(displayNameTextField)),
            Section(header: "Address",
                    footer: Section.Extremity.autoLayoutView(addressInputsView)),
            submissionInProgress ? nil : Section(rows: [
                Row(text: "Create Location", selection: { [unowned self] in self.formSubmit() }, cellClass: ButtonCell.self)
            ])
        ].compactMap { return $0 }

        dataSource.sections = sections
    }

    // MARK: - UIControl Actions

    @objc
    func dismissAction() {
        presentingViewController?.dismiss(animated: true, completion: nil)
    }
}
