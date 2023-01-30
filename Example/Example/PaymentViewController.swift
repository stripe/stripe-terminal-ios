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
    private let collectConfig: CollectConfiguration
    private let declineCardBrand: CardBrand?
    private let recollectAfterCardBrandDecline: Bool

    init(paymentParams: PaymentIntentParameters,
         collectConfig: CollectConfiguration,
         declineCardBrand: CardBrand?,
         recollectAfterCardBrandDecline: Bool) {
        self.paymentParams = paymentParams
        self.collectConfig = collectConfig
        self.declineCardBrand = declineCardBrand
        self.recollectAfterCardBrandDecline = recollectAfterCardBrandDecline
        super.init()
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
                self.collectPaymentMethod(intent: intent)
            }
        }
    }

    private func createPaymentIntent(_ parameters: PaymentIntentParameters, completion: @escaping PaymentIntentCompletionBlock) {
        if Terminal.shared.connectedReader?.deviceType == .verifoneP400
            || Terminal.shared.connectedReader?.deviceType == .wisePosE
            || Terminal.shared.connectedReader?.deviceType == .wisePosEDevKit
            || Terminal.shared.connectedReader?.deviceType == .etna
            || Terminal.shared.connectedReader?.deviceType == .stripeS700
            || Terminal.shared.connectedReader?.deviceType == .stripeS700DevKit {
            // For internet-connected readers, PaymentIntents must be created via your backend
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
            Terminal.shared.createPaymentIntent(parameters
            ) { intent, error in
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

    private func collectPaymentMethod(intent: PaymentIntent) {
        var collectEvent = LogEvent(method: .collectPaymentMethod)
        self.events.append(collectEvent)
        self.cancelable = Terminal.shared.collectPaymentMethod(intent, collectConfig: self.collectConfig) { intentWithPaymentMethod, attachError in
            let collectCancelable = self.cancelable
            self.cancelable = nil
            if let error = attachError {
                collectEvent.result = .errored
                collectEvent.object = .error(error as NSError)
                self.events.append(collectEvent)
                self.complete()
            } else if let intent = intentWithPaymentMethod {
                // Before proceeding check if the card brand provided matches the brand chosen to reject
                if let declineCardBrand = self.declineCardBrand,
                   let paymentMethod = intent.paymentMethod,
                   let details = paymentMethod.cardPresent ?? paymentMethod.interacPresent,
                   details.brand == declineCardBrand {
                    collectEvent.result = .errored
                    let error = NSError(domain: "com.stripe-terminal-ios.example",
                                        code: 1000,
                                        userInfo: [NSLocalizedDescriptionKey: "Integration rejected card due to card brand"])
                    collectEvent.object = .error(error)
                    self.events.append(collectEvent)
                    if self.recollectAfterCardBrandDecline {
                        // Start collect all over
                        self.collectPaymentMethod(intent: intent)
                    } else {
                        // Cancel to ensure the reader resets back to its idle state
                        collectCancelable?.cancel { cancelError in
                            var cancelEvent = LogEvent(method: .cancelCollectPaymentMethod)
                            if let error = cancelError {
                                cancelEvent.result = .errored
                                cancelEvent.object = .error(error as NSError)
                            } else {
                                cancelEvent.result = .succeeded
                                cancelEvent.object = .paymentIntent(intent)
                            }
                            self.events.append(cancelEvent)
                            self.complete()
                        }
                    }
                    return
                }

                collectEvent.result = .succeeded
                collectEvent.object = .paymentIntent(intent)
                self.events.append(collectEvent)

                // 3. confirm PaymentIntent
                self.confirmPaymentIntent(intent: intent)
            }
        }
    }

    private func confirmPaymentIntent(intent: PaymentIntent) {
        var processEvent = LogEvent(method: .processPayment)
        self.events.append(processEvent)
        Terminal.shared.processPayment(intent) { processedIntent, processError in
            if let error = processError {
                processEvent.result = .errored
                processEvent.object = .error(error as NSError)
                self.events.append(processEvent)
                self.complete()
            } else if let intent = processedIntent {
                if intent.status == .succeeded || intent.status == .requiresCapture {
                    processEvent.result = .succeeded
                    processEvent.object = .paymentIntent(intent)
                    self.events.append(processEvent)
                    #if SCP_SHOWS_RECEIPTS
                    self.events.append(ReceiptEvent(refund: nil, paymentIntent: intent))
                    #endif

                    if intent.status == .requiresCapture {
                        // 4. send to backend for capture
                        self.capturePaymentIntent(intent: intent)
                    } else {
                        // If the paymentIntent returns from Stripe with a status of succeeded,
                        // our integration doesn't need to capture the payment intent on the backend.
                        // PaymentIntents will succeed directly after process if they were created with
                        // a single-message payment method, like Interac in Canada.
                        self.complete()
                    }

                    // Show a refund button if this was an Interac charge to make it easy to refund.
                    // Require iOS 16 since we're using a 16+ SF Symbol
                    if #available(iOS 16.0, *),
                       let charge = intent.charges.first,
                       charge.paymentMethodDetails?.interacPresent != nil {
                        let refundButton = UIBarButtonItem(
                            image: UIImage(systemName: "dollarsign.arrow.circlepath"),
                            primaryAction: UIAction(handler: { [weak self] _ in
                                self?.refund(chargeId: charge.stripeId, amount: intent.amount)
                            }))
                        self.navigationItem.rightBarButtonItems = [self.doneButton, refundButton].compactMap({ $0 })
                    }
                } else {
                    // The intent should be succeeded or requiresCapture.
                    // This is unexpected, report it as an error
                    processEvent.result = .errored
                    processEvent.object = .paymentIntent(intent)
                    self.events.append(processEvent)
                    self.complete()
                }
            }
        }
    }


    private func capturePaymentIntent(intent: PaymentIntent) {
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

    public func refund(chargeId: String, amount: UInt) {
        self.navigationController?.pushViewController(
            StartRefundViewController(chargeId: chargeId, amount: amount),
            animated: true
        )
    }
}
