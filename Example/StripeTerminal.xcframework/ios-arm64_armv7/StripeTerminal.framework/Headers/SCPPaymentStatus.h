//
//  SCPPaymentStatus.h
//  StripeTerminal
//
//  Created by Ben Guo on 5/14/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

NS_ASSUME_NONNULL_BEGIN

/**
 The possible payment statuses for the SDK.

 @see https://stripe.com/docs/terminal/payments
 */
typedef NS_ENUM(NSUInteger, SCPPaymentStatus) {
    /**
     The SDK is not ready to start a payment. It may be busy with another
     command, or a reader may not be connected.
     */
    SCPPaymentStatusNotReady,
    /**
     The SDK is ready to start a payment.
     */
    SCPPaymentStatusReady,
    /**
     The SDK is waiting for input from the customer (e.g., for a card to
     be presented to the reader)
     */
    SCPPaymentStatusWaitingForInput,
    /**
     The SDK is processing a payment.
     */
    SCPPaymentStatusProcessing,
} NS_SWIFT_NAME(PaymentStatus);

NS_ASSUME_NONNULL_END
