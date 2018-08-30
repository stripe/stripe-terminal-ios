//
//  RootViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/7/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit
import StripePOS

class RootViewController: UITabBarController {
    /**
     NOTE: The example app uses a secret API key, but you should NEVER hardcode
     your secret API key in your own app. A fake backend has been included as
     part of the example app for demonstration purposes only.

     Secret API keys should be kept confidential and only stored on your own
     servers. Your account’s secret API key can perform any API request to
     Stripe without restriction.

     @see https://stripe.com/docs/keys
     */
    static var secretAPIKey: String? = "sk_test_fkGHWvi9zNJo81LT5CeCjUr0"

    let terminalVC = ReaderViewController()
    let paymentVC = PaymentViewController()
    let settingsVC = SettingsViewController()
    let apiClient: APIClient
    var terminal: SCPTerminal

    init() {
        guard let apiKey = RootViewController.secretAPIKey,
            apiKey.hasPrefix("sk_test") else {
                fatalError("You must provide a secret testmode API key to run this app.")
        }

        let config = SCPTerminalConfiguration()
        // To log events from the SDK to console:
         config.logLevel = .verbose
        let backend = FakeBackend(secretAPIKey: apiKey)
        self.apiClient = APIClient(backend: backend)
        self.terminal = SCPTerminal(configuration: config,
                                    tokenProvider: self.apiClient,
                                    delegate: self.terminalVC)
        self.terminalVC.terminal = self.terminal
        self.paymentVC.terminal = self.terminal
        self.settingsVC.terminal = self.terminal
        super.init(nibName: nil, bundle: nil)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        tabBar.isTranslucent = false
        terminalVC.tabBarItem = UITabBarItem.buildItem(title: "Terminal")
        paymentVC.tabBarItem = UITabBarItem.buildItem(title: "Payment")
        settingsVC.tabBarItem = UITabBarItem.buildItem(title: "Settings")
        self.viewControllers = [
            terminalVC,
            paymentVC,
            settingsVC,
        ]
    }

}

