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

        createSetupIntent(params) { intent, createError in
            if createError != nil {
                self.complete()
            } else if let intent = intent {
                // 2. collectSetupIntent
                self.collectSetupIntent(intent: intent)
            }
        }
    }

    private func createSetupIntent(_ params: SetupIntentParameters, completion: @escaping SetupIntentCompletionBlock) {
        if Terminal.shared.connectedReader?.deviceType == .wisePosE {
            // For internet-connected readers, SetupIntents must be created via your backend
            var createEvent = LogEvent(method: .backendCreateSetupIntent)
            self.events.append(createEvent)

            AppDelegate.apiClient?.createSetupIntent(params) { (result) in
                switch result {
                case .failure(let error):
                    createEvent.result = .errored
                    createEvent.object = .error(error as NSError)
                    self.events.append(createEvent)
                    completion(nil, error)

                case .success(let clientSecret):
                    createEvent.result = .succeeded
                    createEvent.object = .object(clientSecret)
                    self.events.append(createEvent)

                    // and then retrieved w/Terminal SDK
                    var retrieveEvent = LogEvent(method: .retrieveSetupIntent)
                    self.events.append(retrieveEvent)
                    Terminal.shared.retrieveSetupIntent(clientSecret: clientSecret) { (intent, error) in
                        if let error = error {
                            retrieveEvent.result = .errored
                            retrieveEvent.object = .error(error as NSError)
                            self.events.append(retrieveEvent)
                        } else if let intent = intent {
                            retrieveEvent.result = .succeeded
                            retrieveEvent.object = .setupIntent(intent)
                            self.events.append(retrieveEvent)
                        }
                        completion(intent, error)
                    }
                }
            }
        } else {
            var createEvent = LogEvent(method: .createSetupIntent)
            self.events.append(createEvent)
            Terminal.shared.createSetupIntent(params, completion: { (createdSetupIntent, createError) in
                if let error = createError {
                    createEvent.result = .errored
                    createEvent.object = .error(error as NSError)
                    self.events.append(createEvent)
                } else if let si = createdSetupIntent {
                    createEvent.result = .succeeded
                    createEvent.object = .setupIntent(si)
                    self.events.append(createEvent)
                }
                completion(createdSetupIntent, createError)
            })
        }
    }

    private func collectSetupIntent(intent: SetupIntent) {
        var collectEvent = LogEvent(method: .collectSetupIntentPaymentMethod)
        self.events.append(collectEvent)
        self.cancelable = Terminal.shared.collectSetupIntentPaymentMethod(intent, customerConsentCollected: true) { (collectedSetupIntent, collectError) in
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
