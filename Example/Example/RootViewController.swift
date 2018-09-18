//
//  RootViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/7/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit
import StripeTerminal

class RootViewController: UINavigationController, TerminalDelegate {
    /**
     NOTE: A backend simulator has been included as part of the example app for
     demonstration purposes only.

     Secret API keys should be kept confidential and stored only on your own
     servers. Your account’s secret API key can perform any API request to
     Stripe without restriction.

     You should _never_ hardcode your secret API key into your own app.

     @see https://stripe.com/docs/keys
     */
    static var secretAPIKey: String? = nil

    static var apiClient: APIClient?
    static var terminal: Terminal?
    let backend: BackendSimulator

    init() {
        guard let apiKey = RootViewController.secretAPIKey,
            apiKey.hasPrefix("sk_test") else {
                fatalError("You must provide a secret testmode API key to run this app.")
        }
        backend = BackendSimulator(secretAPIKey: apiKey)
        let apiClient = APIClient(backend: backend)
        RootViewController.apiClient = apiClient
        super.init(nibName: nil, bundle: nil)
        navigationBar.isTranslucent = false
        if #available(iOS 11.0, *) {
            navigationBar.prefersLargeTitles = true
        }
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        guard let apiClient = RootViewController.apiClient else { return }
        let config = TerminalConfiguration()
        // Log events from the SDK to the console
        config.logLevel = .verbose
        let terminal = Terminal(configuration: config,
                                tokenProvider: apiClient,
                                delegate: self)
        RootViewController.terminal = terminal
        let vc = ReaderViewController(terminal: terminal)
        self.pushViewController(vc, animated: false)
    }

}

