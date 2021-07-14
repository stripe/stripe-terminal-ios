//
//  SetupIntentViewController.swift
//  AppStore
//
//  Created by James Little on 1/13/21.
//  Copyright © 2021 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class SetupIntentViewController: EventDisplayingViewController {

    override var cancelLogMethod: LogEvent.Method {
        return .cancelCollectSetupIntentPaymentMethod
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        let params = SetupIntentParameters(customer: nil)

        var createEvent = LogEvent(method: .createSetupIntent)
        self.events.append(createEvent)

        // TODO: If connected to a Rabbit reader, create SetupIntent
        Terminal.shared.createSetupIntent(params, completion: { (createdSetupIntent, createError) in
            if let error = createError {
                createEvent.result = .errored
                createEvent.object = .error(error as NSError)
                self.events.append(createEvent)
                self.complete()
            } else if let si = createdSetupIntent {
                var collectEvent = LogEvent(method: .collectSetupIntentPaymentMethod)
                self.events.append(collectEvent)

                self.cancelable = Terminal.shared.collectSetupIntentPaymentMethod(si, customerConsentCollected: true) { (collectedSetupIntent, collectError) in
                    if let error = collectError {
                        collectEvent.result = .errored
                        collectEvent.object = .error(error as NSError)
                        self.events.append(collectEvent)
                        self.complete()
                    } else if let intent = collectedSetupIntent {
                        collectEvent.result = .succeeded
                        collectEvent.object = .setupIntent(intent)
                        self.events.append(collectEvent)
                        self.confirmSetupIntent(intent)
                    }
                }
            }
        })
    }

    private func confirmSetupIntent(_ intent: SetupIntent) {
        var processEvent = LogEvent(method: .confirmSetupIntent)
        self.events.append(processEvent)
        Terminal.shared.confirmSetupIntent(intent) { processedIntent, processError in
            if let error = processError {
                processEvent.result = .errored
                processEvent.object = .error(error as NSError)
                self.events.append(processEvent)
                self.complete()
            } else if let intent = processedIntent {
                if intent.status == .succeeded {
                    processEvent.result = .succeeded
                    processEvent.object = .setupIntent(intent)
                    self.events.append(processEvent)
                    self.complete()
                } else {
                    processEvent.result = .errored
                    processEvent.object = .setupIntent(intent)
                    self.events.append(processEvent)
                    self.complete()
                }
            }
        }
    }
}
