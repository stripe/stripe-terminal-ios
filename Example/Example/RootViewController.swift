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
     To get started with this demo, you'll need to first deploy an instance of
     our provided example backend:

     https://github.com/stripe/example-terminal-backend

     After deploying your backend, replace nil on the line below with the URL
     of your Heroku app.

     static var backendUrl: String? = "https://your-app.herokuapp.com"
     */
    static var backendUrl: String? = nil

    static var apiClient: APIClient?

    init() {
        guard let backendUrl = RootViewController.backendUrl else {
            fatalError("You must provide a backend URL to run this app.")
        }
        let apiClient = APIClient()
        apiClient.baseURLString = backendUrl
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
        Terminal.setTokenProvider(apiClient)
        // To log events from the SDK to the console:
//        Terminal.shared.logLevel = .verbose
        let vc = ReaderViewController()
        self.pushViewController(vc, animated: false)
    }

}

