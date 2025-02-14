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
    private let refundConfig: RefundConfiguration

    init(refundParams: RefundParameters, refundConfig: RefundConfiguration) {
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

        // 1. collectRefundMethod
        var collectEvent = LogEvent(method: .collectRefundPaymentMethod)
        self.events.append(collectEvent)
        self.currentCancelLogMethod = .cancelCollectRefundPaymentMethod
        self.cancelable = Terminal.shared.collectRefundPaymentMethod(
            self.refundParameters,
            refundConfig: self.refundConfig
        ) { [weak self] collectError in
            guard let self = self else { return }

            if let error = collectError {
                collectEvent.result = .errored
                collectEvent.object = .error(error as NSError)
                self.events.append(collectEvent)
                self.complete()
            } else {
                collectEvent.result = .succeeded
                self.events.append(collectEvent)

                // 2. process refund
                var confirmEvent = LogEvent(method: .confirmRefund)
                self.events.append(confirmEvent)
                self.currentCancelLogMethod = .cancelConfirmRefund
                self.cancelable = Terminal.shared.confirmRefund { [weak self] confirmedRefund, confirmError in
                    guard let self = self else { return }

                    if let error = confirmError {
                        confirmEvent.result = .errored
                        confirmEvent.object = .error(error as NSError)
                        self.events.append(confirmEvent)
                        #if SCP_SHOWS_RECEIPTS
                        self.events.append(ReceiptEvent(refund: error.refund, paymentIntent: nil))
                        #endif
                        self.complete()
                    } else if let refund = confirmedRefund, refund.status == .succeeded {
                        confirmEvent.result = .succeeded
                        confirmEvent.object = .refund(refund)
                        self.events.append(confirmEvent)
                        #if SCP_SHOWS_RECEIPTS
                        self.events.append(ReceiptEvent(refund: refund, paymentIntent: nil))
                        #endif
                        self.complete()
                    } else if confirmedRefund != nil {
                        self.events.append(confirmEvent)
                        self.complete()
                    }
                }
            }
        }
    }
}
