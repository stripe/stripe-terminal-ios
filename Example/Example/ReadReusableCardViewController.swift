//
//  ReadReusableCardViewController.swift
//  AppStore
//
//  Created by Ben Guo on 9/12/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class ReadReusableCardViewController: EventDisplayingViewController {
    override func viewDidLoad() {
        super.viewDidLoad()

        let params = ReadReusableCardParameters()
        params.metadata = [
            // optional: attach metadata (specific to your app/backend) to the PaymentMethod
            "unique_id": "764BA46C-478D-4EC8-9906-0949B49A60B9"
        ]
        var readEvent = LogEvent(method: .readReusableCard)
        self.events.append(readEvent)
        self.cancelable = Terminal.shared.readReusableCard(params) { [weak self] paymentMethod, error in
            guard let self = self else { return }

            self.cancelable = nil
            if let error = error {
                readEvent.result = .errored
                readEvent.object = .error(error as NSError)
                self.events.append(readEvent)
                self.complete()
            } else if let paymentMethod = paymentMethod {
                readEvent.result = .succeeded
                readEvent.object = .paymentMethod(paymentMethod)
                self.events.append(readEvent)

                var attachEvent = LogEvent(method: .attachPaymentMethod)
                self.events.append(attachEvent)

                // At this point, you have a `PaymentMethod` of type `card`.
                // This example app sends it to the example-terminal-backend, which attaches it to a
                // customer and returns the attached PaymentMethod with an expanded Customer.
                AppDelegate.apiClient?.attachPaymentMethod(paymentMethod.stripeId, completion: { [weak self] (json, error) in
                    guard let self = self else { return }

                    if let error = error {
                        attachEvent.result = .errored
                        attachEvent.object = .error(error as NSError)
                    } else if let json = json {
                        attachEvent.result = .succeeded
                        attachEvent.object = .json(json)
                    }
                    self.events.append(attachEvent)
                    self.complete()
                })
            }
        }
    }
}
