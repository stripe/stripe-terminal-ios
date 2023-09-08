//
//  ReaderRegistrationViewController.swift
//  Example
//
//  Created by James Little on 6/9/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class ReaderRegistrationViewController: TableViewController, DiscoveryDelegate, CancelableViewController, CancelingViewController {

    internal var cancelable: Cancelable?
    internal weak var cancelButton: UIBarButtonItem?

    /// Prevents double-calls of `formSubmit`, and also controls the isEnabled properties
    /// of the form's text fields
    internal var registrationInProgress = false {
        didSet {
            let fieldsEnabled = !registrationInProgress
            registrationCodeTextField.textField.isEnabled = fieldsEnabled
            readerLabelTextField.textField.isEnabled = fieldsEnabled
            updateContent()
        }
    }

    let registrationCodeTextField = TextFieldView(text: "", footer: "")
    let readerLabelTextField = TextFieldView(text: "", footer: "")
    private var selectedLocationStub: LocationStub?

    var message: String? {
        didSet {
            updateContent()
        }
    }

    var onConnectedToReader: (Reader) -> Void = { _ in }
    var readerId: String?
    private var readers: [Reader] = []

    // MARK: - Initializers

    init() {
        super.init(style: .grouped)
        registrationCodeTextField.textField.autocorrectionType = .no
        registrationCodeTextField.textField.autocapitalizationType = .none
        registrationCodeTextField.textField.placeholder = "banana-apple-pear"

        readerLabelTextField.textField.autocorrectionType = .no
        readerLabelTextField.textField.autocapitalizationType = .none
        readerLabelTextField.textField.placeholder = "Front Desk"
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    // MARK: - ViewController Lifecycle

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "Register Reader"
        self.addKeyboardDisplayObservers()

        let cancelButton = UIBarButtonItem(title: "Back", style: .plain, target: self, action: #selector(dismissAction))
        self.cancelButton = cancelButton
        navigationItem.leftBarButtonItem = cancelButton
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(true)
        updateContent()
    }

    // MARK: - TableView & Form Helpers

    func formSubmit() {
        if registrationInProgress {
            return
        }

        guard let registrationCode = registrationCodeTextField.textField.text,
            var label = readerLabelTextField.textField.text,
            !registrationCode.isEmpty else {
                message = "Please fill out the registration code."
                return
        }

        guard let selectedLocationId = selectedLocationStub?.stripeId else {
            message = "Please select a location."
            return
        }

        if label.isEmpty {
            label = registrationCode
        }

        registrationInProgress = true
        setAllowedCancelMethods([])
        self.message = "Registering..."
        AppDelegate.apiClient?.registerReader(withCode: registrationCode, label: label, locationId: selectedLocationId) { [unowned self] response, error in
            if let error = error {
                self.registrationInProgress = false
                self.setAllowedCancelMethods(.all)
                self.message = "Could not register reader."
                print(error)
            } else if let response = response {
                self.readerId = response["id"] as? String
                self.setAllowedCancelMethods(.all)
                self.message = "Rediscovering..."

                do {
                    let config = try InternetDiscoveryConfigurationBuilder().setLocationId(selectedLocationId).build()
                    self.cancelable = Terminal.shared.discoverReaders(config, delegate: self) { error in
                        self.cancelable = nil
                        if let error = error {
                            self.registrationInProgress = false
                            self.setAllowedCancelMethods(.all)
                            self.message = "Could not discover readers."
                            print(error)
                        }
                    }
                } catch {
                    self.registrationInProgress = false
                    self.setAllowedCancelMethods(.all)
                    self.message = "Could not discover readers. \(error.localizedDescription)"
                    print(error)
                }
            }
        }
    }

    internal func presentModalInNavigationController(_ vc: UIViewController) {
        let navController = LargeTitleNavigationController(rootViewController: vc)
        navController.presentationController?.delegate = self
        self.present(navController, animated: true, completion: nil)
    }

    internal func onLocationSelect(viewController: SelectLocationViewController, locationStub: LocationStub) {
        self.selectedLocationStub = locationStub
        viewController.dismiss(animated: true) {
            self.updateContent()
        }
    }

    internal func showLocationSelector() {
        let selectLocationVC = SelectLocationViewController()
        selectLocationVC.onSelectLocation = { [unowned selectLocationVC] locationStub in
            self.onLocationSelect(viewController: selectLocationVC, locationStub: locationStub)
        }
        self.presentModalInNavigationController(selectLocationVC)
    }

    private func updateContent() {
        let messageSection: Section? = (message != nil)
            ? Section(rows: [Row(text: message ?? "")])
            : nil

        let sections = [
            Section(header: "Registration Code",
                    footer: Section.Extremity.autoLayoutView(registrationCodeTextField)),
            Section(header: "Label (optional)",
                    footer: Section.Extremity.autoLayoutView(readerLabelTextField)),
            Section(
                header: Section.Extremity.title("Location"),
                rows: [
                    Row(
                        text: selectedLocationStub != nil ? selectedLocationStub?.displayName : "No location selected",
                        selection: { [unowned self] in self.showLocationSelector() },
                        accessory: .disclosureIndicator
                    )
                ]
            ),
            messageSection,
            Section(rows: [
                Row(text: "Register Reader",
                    selection: { [unowned self] in
                        self.formSubmit()
                    },
                    cellClass: ButtonCell.self
                )
            ], footer: "Internet-connected readers like the Verifone P400 must be registered to your account and associated to a location before they can be discovered.\n\nPress 0-7-1-3-9 on your reader to display a registration code.")
            ].compactMap { return $0 }

        dataSource.sections = sections
    }

    // MARK: - SCPTerminal Delegate Methods

    func terminal(_ terminal: Terminal, didUpdateDiscoveredReaders readers: [Reader]) {
        self.readers = readers

        guard let readerId = readerId,
            let reader = self.readers.filter({ (reader) -> Bool in
                reader.stripeId == readerId
            }).first else {
                registrationInProgress = false
                message = "Couldn't find newly registered reader."
                print("Couldn't find newly registered reader (looking for \(self.readerId ?? "<unknown>")), but found: \(readers.map {$0.serialNumber})")
                return
        }

        self.setAllowedCancelMethods([])
        self.message = "Connecting..."
        Terminal.shared.connectInternetReader(reader, connectionConfig: nil) { [unowned self] connectedReader, error in
            self.setAllowedCancelMethods(.all)
            if let error = error {
                self.message = "Could not connect to reader."
                print(readers, error)
            } else if let connectedReader = connectedReader {
                self.onConnectedToReader(connectedReader)
            }

            self.registrationInProgress = false
        }
    }

    // MARK: - UIControl Actions

    @objc
    func dismissAction() {
        if let cancelable = cancelable {
            cancelable.cancel { error in
                if let error = error {
                    print("cancel discoverReaders failed: \(error)")
                } else {
                    self.presentingViewController?.dismiss(animated: true, completion: nil)
                }
                self.cancelable = nil
            }
        } else {
            presentingViewController?.dismiss(animated: true, completion: nil)
        }
    }
}
