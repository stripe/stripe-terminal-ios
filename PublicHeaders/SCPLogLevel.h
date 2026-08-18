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
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The various log levels for the SDK.

 Setting a given level prints log messages of that severity and all more-severe
 messages (for example, `SCPLogLevelWarning` prints warnings and errors). This
 mirrors the severities available in the Android SDK's `LogLevel`.

 Raw values are assigned explicitly and must remain stable across releases:
 `SCPLogLevelNone` and `SCPLogLevelVerbose` keep their original values for
 backwards compatibility, and newer levels are appended. Severity is defined by
 the SDK, not by the raw value ordering — do not infer one from the other.
 */
typedef NS_ENUM(NSUInteger, SCPLogLevel) {
    /**
     No logs will be printed to the console.
     */
    SCPLogLevelNone = 0,
    /**
     All logs will be printed to the console.
     */
    SCPLogLevelVerbose = 1,
    /**
     Only error logs will be printed to the console.
     */
    SCPLogLevelError = 2,
    /**
     All errors and warnings will be printed to the console.
     */
    SCPLogLevelWarning = 3,
    /**
     All errors, warnings, and info logs will be printed to the console.
     */
    SCPLogLevelInfo = 4,
} NS_SWIFT_NAME(LogLevel);

NS_ASSUME_NONNULL_END
