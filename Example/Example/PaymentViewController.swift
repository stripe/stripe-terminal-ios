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
    private let confirmConfig: ConfirmConfiguration
    private let declineCardBrand: CardBrand?
    private let recollectAfterCardBrandDecline: Bool
    private var offlineCreateConfig: CreateConfiguration?
    private let isSposReader: Bool
    private let skipCapture: Bool

    init(paymentParams: PaymentIntentParameters,
         collectConfig: CollectConfiguration,
         confirmConfig: ConfirmConfiguration,
         declineCardBrand: CardBrand?,
         recollectAfterCardBrandDecline: Bool,
         isSposReader: Bool,
         offlineTransactionLimit: Int,
         offlineTotalTransactionLimit: Int,
         offlineBehavior: OfflineBehavior,
         skipCapture: Bool) {
        self.paymentParams = paymentParams
        self.collectConfig = collectConfig
        self.confirmConfig = confirmConfig
        self.declineCardBrand = declineCardBrand
        self.recollectAfterCardBrandDecline = recollectAfterCardBrandDecline
        self.isSposReader = isSposReader
        self.skipCapture = skipCapture

        var isOverOfflineTransactionLimit = paymentParams.amount >= offlineTransactionLimit
        if let offlinePaymentTotalByCurrency = Terminal.shared.offlineStatus.sdk.paymentAmountsByCurrency[paymentParams.currency]?.intValue {
            isOverOfflineTransactionLimit = isOverOfflineTransactionLimit || (offlinePaymentTotalByCurrency >= offlineTotalTransactionLimit)
        }
        let offlineBehaviorFromTransactionLimit: OfflineBehavior = {
            if isOverOfflineTransactionLimit {
                return .requireOnline
            } else {
                return offlineBehavior
            }
        }()
        do {
            self.offlineCreateConfig = try CreateConfigurationBuilder().setOfflineBehavior(offlineBehaviorFromTransactionLimit).build()
        } catch {
            fatalError("Invalid create configuration: \(error.localizedDescription)")
        }
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
        if Terminal.shared.connectedReader?.deviceType == .verifoneP400 {
            // When using a Verifone P400, PaymentIntents must be created via your backend
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
            Terminal.shared.createPaymentIntent(parameters, createConfig: offlineCreateConfig) { intent, error in
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
                if (error as NSError).code == ErrorCode.canceled.rawValue {
                    self.cancelPaymentIntent(intent: intent)
                } else {
                    self.complete()
                }
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
                            self.cancelPaymentIntent(intent: intent)
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

    private func cancelPaymentIntent(intent: PaymentIntent) {
        var cancelEvent = LogEvent(method: .cancelPaymentIntent)
        self.events.append(cancelEvent)
        Terminal.shared.cancelPaymentIntent(intent) { canceledPaymentIntent, cancelError in
            if let error = cancelError {
                cancelEvent.result = .errored
                cancelEvent.object = .error(error as NSError)
                self.events.append(cancelEvent)
            } else if let intent = canceledPaymentIntent {
                cancelEvent.result = .succeeded
                cancelEvent.object = .paymentIntent(intent)
                self.events.append(cancelEvent)
            }
            self.complete()
        }
    }

    private func confirmPaymentIntent(intent: PaymentIntent) {
        var processEvent = LogEvent(method: .confirmPaymentIntent)
        self.events.append(processEvent)
        Terminal.shared.confirmPaymentIntent(intent, confirmConfig: self.confirmConfig) { processedIntent, processError in
            if let error = processError {
                processEvent.result = .errored
                processEvent.object = .error(error as NSError)
                self.events.append(processEvent)
                #if SCP_SHOWS_RECEIPTS
                self.events.append(ReceiptEvent(refund: nil, paymentIntent: error.paymentIntent))
                #endif
                self.complete()
            } else if let intent = processedIntent {
                if intent.status == .succeeded || intent.status == .requiresCapture {
                    processEvent.result = .succeeded
                    processEvent.object = .paymentIntent(intent)
                    self.events.append(processEvent)
                    #if SCP_SHOWS_RECEIPTS
                    self.events.append(ReceiptEvent(refund: nil, paymentIntent: intent))
                    #endif

                    if intent.status == .requiresCapture && !self.skipCapture {
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
                    if let charge = intent.charges.first,
                       charge.paymentMethodDetails?.interacPresent != nil {
                        self.intentToRefund = intent
                        let refundButton: UIBarButtonItem
                        if #available(iOS 16.0, *) {
                            refundButton = UIBarButtonItem(
                                title: nil,
                                image: UIImage(systemName: "dollarsign.arrow.circlepath"),
                                target: self,
                                action: #selector(self.refundButtonTapped)
                            )
                        } else {
                            refundButton = UIBarButtonItem(
                                title: "Refund",
                                style: .plain,
                                target: self,
                                action: #selector(self.refundButtonTapped)
                            )
                        }

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

    private var intentToRefund: PaymentIntent?

    @objc
    private func refundButtonTapped() {
        guard let intent = intentToRefund,
        let intentId = intentToRefund?.stripeId,
        let charge = intent.charges.first else {
            fatalError("Intent or charge to refund was nil: \(intentToRefund?.description ?? "nil intent")")
        }

        self.navigationController?.pushViewController(
            StartRefundViewController(isSposReader: self.isSposReader, chargeId: charge.stripeId, paymentIntentId: intentId, amount: intent.amount),
            animated: true
        )
    }

    private func writeOfflineIntentLogToDisk(_ intent: PaymentIntent) {
        let logString = "\(NSDate()) Offline payment intent \(intent.offlineId ?? intent.description) saved to disk"
        OfflinePaymentsLogViewController.writeLogToDisk(logString, details: intent)
    }

    private func capturePaymentIntent(intent: PaymentIntent) {
        if let offlineDetails = intent.offlineDetails, offlineDetails.requiresUpload {
            // Offline intent, not capturing.
            self.writeOfflineIntentLogToDisk(intent)
            self.complete()
        } else if let piID = intent.stripeId {
            // Online, capture intent.
            var captureEvent = LogEvent(method: .capturePaymentIntent)
            self.events.append(captureEvent)
            AppDelegate.apiClient?.capturePaymentIntent(piID) { captureError in
                if let error = captureError {
                    captureEvent.result = .errored
                    captureEvent.object = .error(error as NSError)
                } else {
                    captureEvent.result = .succeeded
                }
                self.events.append(captureEvent)
                self.complete()
            }
        } else {
            fatalError("Bad payment intent state identified, this should not happen")
        }
    }
}
