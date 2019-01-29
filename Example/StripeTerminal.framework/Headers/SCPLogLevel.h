//
//  SCPLogLevel.h
//  StripeTerminal
//
//  Created by Ben Guo on 1/23/19.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

NS_ASSUME_NONNULL_BEGIN

/**
 The various log levels for the SDK.
 */
typedef NS_ENUM(NSUInteger, SCPLogLevel) {
    /**
     No logs will printed to the console.
     */
    SCPLogLevelNone,
    /**
     Verbose logs will be printed to the console.
     */
    SCPLogLevelVerbose,
} NS_SWIFT_NAME(LogLevel);

NS_ASSUME_NONNULL_END
