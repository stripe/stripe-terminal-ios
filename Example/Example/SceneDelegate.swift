//
//  SceneDelegate.swift
//  Example
//
//  Copyright © 2026 Stripe. All rights reserved.
//

import UIKit

// This app uses a single scene and single window. UIApplicationSupportsMultipleScenes
// is set to false in Info.plist, which prevents iOS/iPadOS from creating additional
// scenes (no Split View or Slide Over multitasking). The SceneDelegate exists solely
// to satisfy the UIScene lifecycle requirement introduced in iOS 27.
@objc(SceneDelegate)
class SceneDelegate: UIResponder, UIWindowSceneDelegate {

    var window: UIWindow?

    func scene(
        _ scene: UIScene,
        willConnectTo session: UISceneSession,
        options connectionOptions: UIScene.ConnectionOptions
    ) {
        guard let windowScene = scene as? UIWindowScene else {
            assertionFailure("SceneDelegate: expected a UIWindowScene")
            return
        }

        let window = UIWindow(windowScene: windowScene)
        window.rootViewController = RootViewController()
        window.makeKeyAndVisible()
        self.window = window
    }
}

extension UIApplication {
    /// The app's single window (read-only).
    private var currentWindow: UIWindow? {
        (connectedScenes.first as? UIWindowScene)?.keyWindow
    }

    /// The root view controller of the app's single window (read-only).
    var rootViewController: UIViewController? {
        currentWindow?.rootViewController
    }
}
