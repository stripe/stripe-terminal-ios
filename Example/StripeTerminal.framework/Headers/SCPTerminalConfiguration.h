//
//  SCPTerminalConfiguration.h
//  StripeTerminal
//
//  Created by Ben Guo on 8/3/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

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

/**
 Configuration for creating a Terminal object.
 */
NS_SWIFT_NAME(TerminalConfiguration)
@interface SCPTerminalConfiguration : NSObject

/**
 The log level for the SDK. The default value is None.
 */
@property (nonatomic, assign, readwrite) SCPLogLevel logLevel;

@end

NS_ASSUME_NONNULL_END
