//
//  SCPTerminalConfiguration.h
//  StripePOS
//
//  Created by Ben Guo on 8/3/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPAddress;

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
};

/**
 SCPTerminalConfiguration represents all the options you can set when
 creating an SCPTerminal instance.
 */
@interface SCPTerminalConfiguration : NSObject

/**
 The log level for the SDK. The default value is None.
 */
@property (nonatomic, assign, readwrite) SCPLogLevel logLevel;

@end

NS_ASSUME_NONNULL_END
