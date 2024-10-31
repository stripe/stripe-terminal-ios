//
//  SCPAllowRedisplay.h
//  StripeTerminal
//
//  Created by Henry Xu on 8/20/24.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A field used to indicate whether a payment method can be shown again to its customer in a checkout flow. Consent must be obtained to set this field.
 */
typedef NS_ENUM(NSUInteger, SCPAllowRedisplay) {
    /**
     This is the default value for payment methods where allow_redisplay wasn’t set.
     */
    SCPAllowRedisplayUnspecified,
    /**
     Use always to indicate that this payment method can always be shown to a customer in a checkout flow.
     */
    SCPAllowRedisplayAlways,
    /**
     Use limited to indicate that this payment method can’t always be shown to a customer in a checkout flow. For example, it can only be shown in the context of a specific subscription.
     */
    SCPAllowRedisplayLimited,
} NS_SWIFT_NAME(AllowRedisplay);

NS_ASSUME_NONNULL_END
