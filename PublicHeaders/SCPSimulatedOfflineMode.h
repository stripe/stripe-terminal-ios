//
//  SCPSimulatedOfflineMode.h
//  StripeTerminal
//
//  Created by Stripe.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Types of network failure that can be simulated.
 */
typedef NS_ENUM(NSUInteger, SCPSimulatedOfflineMode) {
    /**
     Disables simulated offline mode. Network requests proceed normally
     and connectivity status reflects actual network conditions.
     This is the default state.
     */
    SCPSimulatedOfflineModeDisabled = 0,

    /**
     Immediate connection failure. Requests fail instantly with a network error.
     This is the fastest mode for testing but least realistic.
     */
    SCPSimulatedOfflineModeOfflineImmediate,

    /**
     Timeout simulation. Requests hang until timeout (15 seconds), then fail.
     More realistic but slower due to retry logic being exercised.
     */
    SCPSimulatedOfflineModeOfflineTimeout,

    /**
     Intermittent failures. Approximately 50% of requests will fail randomly.
     Useful for testing retry behavior and partial connectivity.
     */
    SCPSimulatedOfflineModeOfflineIntermittent,
} NS_SWIFT_NAME(SimulatedOfflineMode);

NS_ASSUME_NONNULL_END
