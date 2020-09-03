//
//  RefundViewController.swift
//  Example
//
//  Created by James Little on 3/16/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

class RefundViewController: EventDisplayingViewController {

    private let refundParameters: RefundParameters

    init(refundParams: RefundParameters) {
        self.refundParameters = refundParams
        super.init(style: .grouped)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        // 1. collectRefundMethod
        var collectEvent = LogEvent(method: .collectRefundPaymentMethod)
        self.events.append(.log(collectEvent))
        self.cancelable = Terminal.shared.collectRefundPaymentMethod(self.refundParameters) { collectError in
            if let error = collectError {
                collectEvent.result = .errored
                collectEvent.object = .error(error as NSError)
                self.events.append(.log(collectEvent))
                self.complete()
            } else {
                collectEvent.result = .succeeded
                self.events.append(.log(collectEvent))

                // 2. process refund
                var processEvent = LogEvent(method: .processRefund)
                self.events.append(.log(processEvent))
                Terminal.shared.processRefund { processedRefund, processError in
                    if let error = processError {
                        processEvent.result = .errored
                        processEvent.object = .error(error as NSError)
                        self.events.append(.log(processEvent))
                        self.complete()
                    } else if let refund = processedRefund, refund.status == .succeeded {
                        processEvent.result = .succeeded
                        processEvent.object = .refund(refund)
                        self.events.append(.log(processEvent))
                        self.complete()
                    } else if processedRefund != nil {
                        self.events.append(.log(processEvent))
                        self.complete()
                    }
                }
            }
        }
    }
}
