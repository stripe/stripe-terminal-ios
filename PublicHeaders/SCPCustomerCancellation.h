//
//  SCPCustomerCancellation.h
//  StripeTerminal
//
//  Created by Brian Cooke on 09/30/25.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Controls whether customer-initiated cancellation is enabled during payment collection.

 * Android based internet readers support enabling and disabling customer cancellation.
 * WisePad 3 and Tap to Pay will always show customer cancellation and it cannot be disabled.
 * Stripe M2 and Chipper 2X do not support customer cancellation.
 */
typedef NS_ENUM(NSUInteger, SCPCustomerCancellation) {
    /**
     Enable customer cancellation if the reader supports it.
     */
    SCPCustomerCancellationEnableIfAvailable,

    /**
     Disable customer cancellation if the reader supports disabling it.
     */
    SCPCustomerCancellationDisableIfAvailable,
} NS_SWIFT_NAME(CustomerCancellation);

NS_ASSUME_NONNULL_END
