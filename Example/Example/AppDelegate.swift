//
//  AppDelegate.swift
//  Stripe POS
//
//  Created by Ben Guo on 7/26/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit
import UserNotifications
import StripeTerminal

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
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

    var window: UIWindow?

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        guard let backendUrl = AppDelegate.backendUrl else {
            fatalError("You must provide a backend URL to run this app.")
        }
        
        let apiClient = APIClient()
        apiClient.baseURLString = backendUrl
        Terminal.setTokenProvider(apiClient)
        AppDelegate.apiClient = apiClient
        
        // To log events from the SDK to the console:
//        Terminal.shared.logLevel = .verbose

        let window = UIWindow(frame: UIScreen.main.bounds)
        window.rootViewController = RootViewController()
        window.makeKeyAndVisible()
        self.window = window

        return true
    }

}

