//
//  PaymentViewController.swift
//  Example
//
//  Created by Ben Guo on 9/6/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import Static
import StripeTerminal
import UIKit

enum CardBrandDeclineError: Error {
    case shouldRetry(originalIntent: PaymentIntent)
    case userCancelled(originalIntent: PaymentIntent)

    var shouldRetry: Bool {
        switch self {
        case .shouldRetry: return true
        case .userCancelled: return false
        }
    }

    var originalIntent: PaymentIntent {
        switch self {
        case .shouldRetry(let intent), .userCancelled(let intent):
            return intent
        }
    }
}

class PaymentViewController: EventDisplayingViewController {

    private let paymentParams: PaymentIntentParameters
    private let collectConfig: CollectPaymentIntentConfiguration
    private let confirmConfig: ConfirmPaymentIntentConfiguration
    private let declineCardBrand: CardBrand?
    private let recollectAfterCardBrandDecline: Bool
    private var offlineCreateConfig: CreateConfiguration?
    private let isSposReader: Bool
    private let skipCapture: Bool
    private let onReceiptTip: UInt
    private let useProcessPaymentIntent: Bool
    private var qrModalNavigationController: UINavigationController?

    init(
        paymentParams: PaymentIntentParameters,
        collectConfig: CollectPaymentIntentConfiguration,
        confirmConfig: ConfirmPaymentIntentConfiguration,
        declineCardBrand: CardBrand?,
        recollectAfterCardBrandDecline: Bool,
        isSposReader: Bool,
        offlineTransactionLimit: Int,
        offlineTotalTransactionLimit: Int,
        offlineBehavior: OfflineBehavior,
        skipCapture: Bool,
        onReceiptTip: UInt,
        useProcessPaymentIntent: Bool
    ) {
        self.paymentParams = paymentParams
        self.collectConfig = collectConfig
        self.confirmConfig = confirmConfig
        self.declineCardBrand = declineCardBrand
        self.recollectAfterCardBrandDecline = recollectAfterCardBrandDecline
        self.isSposReader = isSposReader
        self.skipCapture = skipCapture
        self.onReceiptTip = onReceiptTip
        self.useProcessPaymentIntent = useProcessPaymentIntent

        var isOverOfflineTransactionLimit = paymentParams.amount >= offlineTransactionLimit
        if let offlinePaymentTotalByCurrency = Terminal.shared.offlineStatus.sdk.paymentAmountsByCurrency[
            paymentParams.currency
        ]?.intValue {
            isOverOfflineTransactionLimit =
                isOverOfflineTransactionLimit || (offlinePaymentTotalByCurrency >= offlineTotalTransactionLimit)
        }
        let offlineBehaviorFromTransactionLimit: OfflineBehavior = {
            if isOverOfflineTransactionLimit {
                return .requireOnline
            } else {
                return offlineBehavior
            }
        }()
        do {
            self.offlineCreateConfig = try CreateConfigurationBuilder().setOfflineBehavior(
                offlineBehaviorFromTransactionLimit
            ).build()
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

        Task {
            // No need to catch, as the createPI function will log the error if it fails. It only rethrows
            // to allow us to bail out if needed.
            do {
                let intent = try await createPaymentIntent(self.paymentParams)
                startPaymentFlow(intent)
            } catch {
                // create failed, nothing else to do. we're complete.
                self.complete()
            }
        }
    }

    private func startPaymentFlow(_ intent: PaymentIntent) {
        task = Task {
            do {
                defer {
                    self.task = nil
                }

                let finalIntent: PaymentIntent
                if useProcessPaymentIntent {
                    // Use processPaymentIntent (combined collect + confirm)
                    finalIntent = try await processPaymentIntent(intent: intent)
                } else {
                    // Use traditional separate flow
                    let collectedIntent = try await collectPaymentMethod(intent: intent)
                    finalIntent = try await confirmPaymentIntent(intent: collectedIntent)
                }

                // Handle capture if needed
                if finalIntent.status == .requiresCapture && !self.skipCapture {
                    try await self.capturePaymentIntent(intent: finalIntent)
                }

                // success path
                self.complete()
            } catch let error as CardBrandDeclineError {
                // Handle card brand decline with task restart
                if error.shouldRetry && recollectAfterCardBrandDecline {
                    // Cancel current task and restart entire flow
                    self.task?.cancel()
                    self.task = nil
                    self.startPaymentFlow(intent)  // Restart with fresh task
                    // Intentionally not calling complete as we aren't done yet.
                    return
                } else {
                    // Cancel the PaymentIntent and unconditionally call complete
                    do {
                        defer {
                            self.complete()
                        }
                        try await self.cancelPaymentIntent(intent: error.originalIntent)
                    } catch {
                        // no action needed, cancel will report the error
                    }
                }
            } catch {
                // All other error logging handled in individual methods
                // Complete in this error path.
                self.complete()
            }
        }
    }

    private func createPaymentIntent(_ parameters: PaymentIntentParameters) async throws -> PaymentIntent {
        var createEvent = LogEvent(method: .createPaymentIntent)
        self.events.append(createEvent)

        do {
            let intent = try await Terminal.shared.createPaymentIntent(
                parameters,
                createConfig: offlineCreateConfig
            )
            createEvent.result = .succeeded
            createEvent.object = .paymentIntent(intent)
            self.events.append(createEvent)
            return intent
        } catch {
            createEvent.result = .errored
            createEvent.object = .error(error as NSError)
            self.events.append(createEvent)
            throw error
        }
    }

    private func collectPaymentMethod(intent: PaymentIntent) async throws -> PaymentIntent {
        var collectEvent = LogEvent(method: .collectPaymentMethod)
        self.events.append(collectEvent)
        let collectedIntent: PaymentIntent

        do {
            collectedIntent = try await Terminal.shared.collectPaymentMethod(
                intent,
                collectConfig: self.collectConfig
            )
        } catch {
            await self.handlePaymentError(error, event: &collectEvent, originalIntent: intent)
            throw error
        }

        // Before proceeding check if the card brand provided matches the brand chosen to reject
        // We do this outside of the above do/catch so we don't double log the exception
        if let declineCardBrand = self.declineCardBrand,
            let paymentMethod = collectedIntent.paymentMethod,
            let details = paymentMethod.cardPresent ?? paymentMethod.interacPresent,
            details.brand == declineCardBrand
        {
            collectEvent.result = .errored
            let error = NSError(
                domain: "com.stripe-terminal-ios.example",
                code: 1000,
                userInfo: [NSLocalizedDescriptionKey: "Integration rejected card due to card brand"]
            )
            collectEvent.object = .error(error)
            self.events.append(collectEvent)

            if self.recollectAfterCardBrandDecline {
                throw CardBrandDeclineError.shouldRetry(originalIntent: collectedIntent)
            } else {
                throw CardBrandDeclineError.userCancelled(originalIntent: collectedIntent)
            }
        }

        collectEvent.result = .succeeded
        collectEvent.object = .paymentIntent(collectedIntent)
        self.events.append(collectEvent)
        return collectedIntent
    }

    private func cancelPaymentIntent(intent: PaymentIntent) async throws {
        var cancelEvent = LogEvent(method: .cancelPaymentIntent)
        self.events.append(cancelEvent)

        do {
            let canceledIntent = try await Terminal.shared.cancelPaymentIntent(intent)
            cancelEvent.result = .succeeded
            cancelEvent.object = .paymentIntent(canceledIntent)
            self.events.append(cancelEvent)
        } catch {
            cancelEvent.result = .errored
            cancelEvent.object = .error(error as NSError)
            self.events.append(cancelEvent)
            throw error
        }
    }

    private func confirmPaymentIntent(intent: PaymentIntent) async throws -> PaymentIntent {
        // Update the cancel log method for the confirm phase
        self.currentCancelLogMethod = .cancelConfirmPaymentIntent

        var confirmEvent = LogEvent(method: .confirmPaymentIntent)
        self.events.append(confirmEvent)

        do {
            let confirmedIntent = try await Terminal.shared.confirmPaymentIntent(
                intent,
                confirmConfig: self.confirmConfig
            )
            self.handlePaymentSuccess(confirmedIntent, event: &confirmEvent)
            self.dismissQrModalIfPresented()
            return confirmedIntent
        } catch {
            await self.handlePaymentError(error, event: &confirmEvent, originalIntent: intent)
            self.dismissQrModalIfPresented()
            throw error
        }
    }

    private func processPaymentIntent(intent: PaymentIntent) async throws -> PaymentIntent {
        // Note: Card brand decline feature is not supported with processPaymentIntent
        // as it combines collect and confirm into a single operation
        var processEvent = LogEvent(method: .processPaymentIntent)
        self.events.append(processEvent)

        do {
            let processedIntent = try await Terminal.shared.processPaymentIntent(
                intent,
                collectConfig: self.collectConfig,
                confirmConfig: self.confirmConfig
            )
            self.handlePaymentSuccess(processedIntent, event: &processEvent)
            return processedIntent
        } catch {
            await self.handlePaymentError(error, event: &processEvent, originalIntent: intent)
            throw error
        }
    }

    private var intentToRefund: PaymentIntent?

    // Helper to report the event as failed and cancel the intent if needed.
    private func handlePaymentError(_ error: Error, event: inout LogEvent, originalIntent: PaymentIntent) async {
        event.result = .errored
        event.object = .error(error as NSError)
        self.events.append(event)
        #if SCP_SHOWS_RECEIPTS
        if let error = error as? ConfirmPaymentIntentError,
            let paymentIntent = error.paymentIntent
        {
            self.events.append(ReceiptEvent(paymentIntent: paymentIntent))
        }
        #endif

        if (error as NSError).code == ErrorCode.canceled.rawValue {
            do {
                try await self.cancelPaymentIntent(intent: originalIntent)
            } catch {
                // cancel will handle its error and rethrow
            }
        }
    }

    private func handlePaymentSuccess(_ intent: PaymentIntent, event: inout LogEvent) {
        if intent.status == .succeeded || intent.status == .requiresCapture {
            event.result = .succeeded
            event.object = .paymentIntent(intent)
            self.events.append(event)
            #if SCP_SHOWS_RECEIPTS
            self.events.append(ReceiptEvent(paymentIntent: intent))
            #endif

            // Show a refund button if this was an Interac charge to make it easy to refund.
            if let charge = intent.charges.first,
                charge.paymentMethodDetails?.interacPresent != nil
            {
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
            event.result = .errored
            event.object = .paymentIntent(intent)
            self.events.append(event)
        }
    }

    @objc
    private func refundButtonTapped() {
        guard let intent = intentToRefund,
            let intentId = intent.stripeId,
            let charge = intent.charges.first,
            let clientSecret = intent.clientSecret
        else {
            fatalError("Intent or charge to refund was nil: \(intentToRefund?.description ?? "nil intent")")
        }

        self.navigationController?.pushViewController(
            StartRefundViewController(
                isSposReader: self.isSposReader,
                chargeId: charge.stripeId,
                paymentIntentId: intentId,
                clientSecret: clientSecret,
                amount: intent.amount
            ),
            animated: true
        )
    }

    private func writeOfflineIntentLogToDisk(_ intent: PaymentIntent) {
        let logString = "\(NSDate()) Offline payment intent \(intent.offlineId ?? intent.description) saved to disk"
        OfflinePaymentsLogViewController.writeLogToDisk(logString, details: intent)
    }

    private func capturePaymentIntent(intent: PaymentIntent) async throws {
        if let offlineDetails = intent.offlineDetails, offlineDetails.requiresUpload {
            // Offline intent, not capturing.
            self.writeOfflineIntentLogToDisk(intent)
        } else if let piID = intent.stripeId {
            // Online, capture intent.
            var captureEvent = LogEvent(method: .capturePaymentIntent)
            self.events.append(captureEvent)
            let additionalParams = ["amount_to_capture": self.onReceiptTip + intent.amount]

            return try await withCheckedThrowingContinuation { continuation in
                AppDelegate.apiClient?.capturePaymentIntent(piID, additionalParams: additionalParams) { captureError in
                    if let error = captureError {
                        captureEvent.result = .errored
                        captureEvent.object = .error(error as NSError)
                        self.events.append(captureEvent)
                        continuation.resume(throwing: error)
                    } else {
                        captureEvent.result = .succeeded
                        self.events.append(captureEvent)
                        continuation.resume()
                    }
                }
            }
        } else {
            fatalError("Bad payment intent state identified, this should not happen")
        }
    }
}

// MARK: - MobileReaderDelegate (MPOS QR Payments)

extension PaymentViewController {

    // MARK: Payment Method Selection

    func reader(
        _ reader: Reader,
        didRequestPaymentMethodSelection paymentIntent: PaymentIntent,
        availablePaymentOptions: [PaymentOption],
        completion: @escaping PaymentMethodSelectionCompletionBlock
    ) {
        DispatchQueue.main.async {
            let alert = UIAlertController(
                title: "Select Payment Method",
                message: "Choose how the customer wants to pay:",
                preferredStyle: .actionSheet
            )

            for option in availablePaymentOptions {
                let title: String
                switch option.type {
                case .card:
                    title = "Card (Insert/Tap)"
                case .nonCard:
                    title = "\(option.paymentMethodType.displayName) (QR Code)"
                @unknown default:
                    title = "Unknown Payment Type"
                }

                alert.addAction(
                    UIAlertAction(title: title, style: .default) { _ in
                        // Log the selection
                        var event = LogEvent(method: .didRequestPaymentMethodSelection)
                        event.result = .succeeded
                        event.object = .object("Selected: \(title)" as NSString)
                        self.events.append(event)

                        // Complete with selected option
                        completion(option, nil)
                    }
                )
            }

            alert.addAction(
                UIAlertAction(title: "Cancel", style: .cancel) { _ in
                    let error = NSError(
                        domain: "com.stripe.example",
                        code: -1,
                        userInfo: [NSLocalizedDescriptionKey: "User cancelled payment method selection"]
                    )
                    completion(nil, error)
                }
            )

            self.present(alert, animated: true)
        }
    }

    // MARK: QR Code Display

    func reader(
        _ reader: Reader,
        didRequestQrCodeDisplay paymentIntent: PaymentIntent,
        qrData: QrCodeDisplayData,
        completion: @escaping QrCodeDisplayCompletionBlock
    ) {
        DispatchQueue.main.async {
            // Log the QR display request
            var event = LogEvent(method: .didRequestQrCodeDisplay)
            event.object = .object(
                "Payment Method: \(qrData.paymentMethodType.rawValue), PNG URL: \(qrData.qrCodeImageUrlPng ?? "nil")"
                    as NSString
            )
            self.events.append(event)

            // Present dedicated controller to show the QR code
            let qrVC = QrCodeViewController(qrData: qrData)

            // Present in navigation controller
            let navController = UINavigationController(rootViewController: qrVC)

            // Store reference so we can dismiss it when payment completes
            self.qrModalNavigationController = navController

            self.present(navController, animated: true) {
                // Automatically call completion with success once QR is displayed
                var successEvent = LogEvent(method: .didRequestQrCodeDisplay)
                successEvent.result = .succeeded
                self.events.append(successEvent)

                // Call completion immediately to signal QR was displayed successfully
                completion(nil)
            }
        }
    }

    // Helper to dismiss QR modal when payment completes
    private func dismissQrModalIfPresented() {
        DispatchQueue.main.async {
            if let qrModal = self.qrModalNavigationController {
                qrModal.dismiss(animated: true) {
                    self.qrModalNavigationController = nil
                }
            }
        }
    }
}

// MARK: - PaymentMethodType Display Name Helper
extension PaymentMethodType {
    var displayName: String {
        // Get the enum name string (e.g., "wechat_pay", "affirm")
        let enumString = Terminal.stringFromPaymentMethodType(self)

        // Convert snake_case to Title Case (e.g., "wechat_pay" -> "Wechat Pay")
        return
            enumString
            .split(separator: "_")
            .map { $0.capitalized }
            .joined(separator: " ")
    }
}
