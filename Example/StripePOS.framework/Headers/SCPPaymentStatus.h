//
//  SCPPaymentStatus.h
//  StripePOS
//
//  Created by Ben Guo on 5/14/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

/**
 The possible payment statuses for an SCPTerminal.
 */
typedef NS_ENUM(NSUInteger, SCPPaymentStatus) {
    /**
     SCPTerminal is not ready to start a payment. It may not be activated, or
     a reader may not be connected.
     */
    SCPPaymentStatusNotReady,
    /**
     SCPTerminal is ready to start a payment. Create a PaymentIntent, and then
     call attachSource to begin reading a card.
     */
    SCPPaymentStatusReady,
    /**
     SCPTerminal is in the process of attaching a source to a PaymentIntent.
     */
    SCPPaymentStatusAttachingSource,
    /**
     SCPTerminal is in the process of confirming a payment intent.
     */
    SCPPaymentStatusConfirmingPaymentIntent,
};

NS_ASSUME_NONNULL_END
