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
 The possible payment statuses for a terminal.
 */
typedef NS_ENUM(NSUInteger, SCPPaymentStatus) {
    /**
     Terminal is not ready to start a payment. It may be busy with another
     command, or a reader may not be connected.
     */
    SCPPaymentStatusNotReady,
    /**
     Terminal is ready to start a payment. Create a PaymentIntent, and then
     call collectPaymentMethod to begin reading a card.
     */
    SCPPaymentStatusReady,
    /**
     Terminal is in the process of collecting a payment method for a PaymentIntent.
     */
    SCPPaymentStatusCollectingPaymentMethod,
    /**
     Terminal is in the process of confirming a PaymentIntent.
     */
    SCPPaymentStatusConfirmingPaymentIntent,
} NS_SWIFT_NAME(PaymentStatus);

NS_ASSUME_NONNULL_END
