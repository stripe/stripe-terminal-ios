//
//  SCPOfflineBehavior.h
//  StripeTerminal
//
//  Created by Henry Xu on 2/7/24.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
  The available operating modes that define how payment intents respond to changes in network connectivity.
 */
typedef NS_ENUM(NSInteger, SCPOfflineBehavior) {
    /**
      When network connectivity is available, this PaymentIntent will be transacted online. When network connectivity is unavailable, the PaymentIntent will be transacted offline.
     */
    SCPOfflineBehaviorPreferOnline,
    /**
      The PaymentIntent will only be transacted when network connectivity is available.
     */
    SCPOfflineBehaviorRequireOnline,
    /**
      The PaymentIntent will only be transacted offline, regardless of network connectivity.
     */
    SCPOfflineBehaviorForceOffline
} NS_SWIFT_NAME(OfflineBehavior);

NS_ASSUME_NONNULL_END
