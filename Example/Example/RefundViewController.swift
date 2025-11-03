//
//  RefundViewController.swift
//  Example
//
//  Created by James Little on 3/16/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import Static
import StripeTerminal
import UIKit

class RefundViewController: EventDisplayingViewController {
    private let refundParameters: RefundParameters
    private let refundConfig: CollectRefundConfiguration

    init(refundParams: RefundParameters, refundConfig: CollectRefundConfiguration) {
        self.refundParameters = refundParams
        self.refundConfig = refundConfig
        super.init()
        self.currentCancelLogMethod = .cancelCollectRefundPaymentMethod
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        // This sets the EventDisplayingVC's task which then will cancel the task when requested.
        task = Task {
            do {
                defer {
                    self.task = nil
                    self.complete()
                }

                _ = try await processRefund()
            } catch {
                // All error logging is handled in individual methods
            }
        }
    }

    private func processRefund() async throws -> Refund {
        var processEvent = LogEvent(method: .processRefund)
        self.events.append(processEvent)

        do {
            let confirmedRefund = try await Terminal.shared.processRefund(
                self.refundParameters,
                collectConfig: self.refundConfig
            )

            self.handleRefundResult(confirmedRefund, event: &processEvent)
            return confirmedRefund
        } catch {
            self.handleRefundError(error, event: &processEvent)
            throw error
        }
    }

    private func handleRefundError(_ error: Error, event: inout LogEvent) {
        event.result = .errored
        event.object = .error(error as NSError)
        self.events.append(event)
        #if SCP_SHOWS_RECEIPTS
        if let error = error as? ConfirmRefundError,
            let refund = error.refund
        {
            self.events.append(ReceiptEvent(refund: refund))
        }
        #endif
    }

    private func handleRefundResult(_ refund: Refund, event: inout LogEvent) {
        if refund.status == .succeeded {
            event.result = .succeeded
            event.object = .refund(refund)
            self.events.append(event)
            #if SCP_SHOWS_RECEIPTS
            self.events.append(ReceiptEvent(refund: refund))
            #endif
        } else {
            event.result = .errored
            event.object = .refund(refund)
            self.events.append(event)
        }
    }
}
