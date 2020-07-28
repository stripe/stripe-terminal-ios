//
//  PaymentViewController.swift
//  Example
//
//  Created by Ben Guo on 9/6/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class PaymentViewController: EventDisplayingViewController {

    private let paymentParams: PaymentIntentParameters

    init(paymentParams: PaymentIntentParameters) {
        self.paymentParams = paymentParams
        super.init(style: .grouped)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.addKeyboardDisplayObservers()


        // 1. create PaymentIntent
        createPaymentIntent(self.paymentParams) { intent, createError in
            if createError != nil {
                self.complete()
            } else if let intent = intent {
                // 2. collectPaymentMethod
                var collectEvent = LogEvent(method: .collectPaymentMethod)
                self.events.append(collectEvent)
                self.cancelable = Terminal.shared.collectPaymentMethod(intent, delegate: self) { intentWithPaymentMethod, attachError in
                    self.cancelable = nil
                    if let error = attachError {
                        collectEvent.result = .errored
                        collectEvent.object = .error(error as NSError)
                        self.events.append(collectEvent)
                        self.complete()
                    } else if let intent = intentWithPaymentMethod {
                        collectEvent.result = .succeeded
                        collectEvent.object = .paymentIntent(intent)
                        self.events.append(collectEvent)

                        // 3. confirm PaymentIntent
                        var processEvent = LogEvent(method: .processPayment)
                        self.events.append(processEvent)
                        Terminal.shared.processPayment(intent) { processedIntent, processError in
                            if let error = processError {
                                processEvent.result = .errored
                                processEvent.object = .error(error as NSError)
                                self.events.append(processEvent)
                                self.complete()
                            } else if let intent = processedIntent, intent.status == .succeeded {
                                // If the paymentIntent returns from Stripe with a status of succeeded,
                                // our integration doesn't need to capture the payment intent on the backend.
                                // PaymentIntents will succeed directly after process if they were created with
                                // a single-message payment method, like Interac in Canada.
                                processEvent.result = .succeeded
                                processEvent.object = .paymentIntent(intent)
                                self.events.append(processEvent)
                                self.complete()
                            } else if let intent = processedIntent {
                                processEvent.result = .succeeded
                                processEvent.object = .paymentIntent(intent)
                                self.events.append(processEvent)

                                // 4. send to backend for capture
                                var captureEvent = LogEvent(method: .capturePaymentIntent)
                                self.events.append(captureEvent)
                                AppDelegate.apiClient?.capturePaymentIntent(intent.stripeId) { captureError in
                                    if let error = captureError {
                                        captureEvent.result = .errored
                                        captureEvent.object = .error(error as NSError)
                                    } else {
                                        captureEvent.result = .succeeded
                                    }
                                    self.events.append(captureEvent)
                                    self.complete()
                                }
                            }

                        }
                    }
                }
            }
        }
    }

    private func createPaymentIntent(_ parameters: PaymentIntentParameters, completion: @escaping PaymentIntentCompletionBlock) {
        if Terminal.shared.connectedReader?.deviceType == .verifoneP400 {
            // For p400 readers, PaymentIntents must be created via your backend
            var createEvent = LogEvent(method: .backendCreatePaymentIntent)
            self.events.append(createEvent)

            AppDelegate.apiClient?.createPaymentIntent(parameters) { (result) in
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
                    var retrieveEvent = LogEvent(method: .retrievePaymentIntent)
                    self.events.append(retrieveEvent)
                    Terminal.shared.retrievePaymentIntent(clientSecret: clientSecret) { (intent, error) in
                        if let error = error {
                            retrieveEvent.result = .errored
                            retrieveEvent.object = .error(error as NSError)
                            self.events.append(retrieveEvent)
                        } else if let intent = intent {
                            retrieveEvent.result = .succeeded
                            retrieveEvent.object = .paymentIntent(intent)
                            self.events.append(retrieveEvent)
                        }
                        completion(intent, error)
                    }
                }
            }
        } else {
            var createEvent = LogEvent(method: .createPaymentIntent)
            self.events.append(createEvent)
            Terminal.shared.createPaymentIntent(parameters) { (intent, error) in
                if let error = error {
                    createEvent.result = .errored
                    createEvent.object = .error(error as NSError)
                    self.events.append(createEvent)
                } else if let intent = intent {
                    createEvent.result = .succeeded
                    createEvent.object = .paymentIntent(intent)
                    self.events.append(createEvent)

                }
                completion(intent, error)
            }
        }
    }
}
