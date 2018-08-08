//
//  UIViewController+UNNotificationCenter.swift
//  Stripe POS
//
//  Created by Ben Guo on 10/5/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit
import UserNotifications

extension UIViewController: UNUserNotificationCenterDelegate {

    /**
     Shows a local notification with the given text
     */
    func showNotification(title: String, message: String? = nil) {
        let trigger = UNTimeIntervalNotificationTrigger(timeInterval: 0.01,
                                                        repeats: false)
        let center = UNUserNotificationCenter.current()
        center.delegate = self
        let identifier = UUID().uuidString
        let content = UNMutableNotificationContent()
        if let m = message {
            content.title = title
            content.body = m
        }
        else {
            content.title = ""
            content.body = title
        }
        let request = UNNotificationRequest(identifier: identifier,
                                            content: content,
                                            trigger: trigger)
        center.add(request) { _ in }
    }

    // UNUserNotificationCenterDelegate
    public func userNotificationCenter(_ center: UNUserNotificationCenter, willPresent notification: UNNotification, withCompletionHandler completionHandler: @escaping (UNNotificationPresentationOptions) -> Void) {
        completionHandler([.alert])
    }
}
