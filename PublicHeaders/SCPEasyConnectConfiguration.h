//
//  SCPEasyConnectConfiguration.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2025-10-31.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

@protocol SCPDiscoveryConfiguration;
@class SCPConnectionConfiguration;

NS_ASSUME_NONNULL_BEGIN

/**
 Base class for all EasyConnectConfiguration subclasses.

 EasyConnectConfiguration simplifies discovering and connecting to a reader for user integrations.

 Your app should use the subclasses depending on the reader type being used:
 - `SCPInternetEasyConnectConfiguration` for internet readers
 - `SCPTapToPayEasyConnectConfiguration` for Tap to Pay readers
 */
NS_SWIFT_NAME(EasyConnectConfiguration)
@interface SCPEasyConnectConfiguration : NSObject

/**
 The discovery configuration used to discover readers.
 */
@property (nonatomic, readonly) id<SCPDiscoveryConfiguration> discoveryConfiguration;

/**
 The connection configuration used to connect to the discovered reader.
 */
@property (nonatomic, readonly) SCPConnectionConfiguration *connectionConfiguration;

/**
 You cannot directly instantiate this class.

 Use InternetEasyConnectConfiguration or TapToPayEasyConnectConfiguration
 depending on the reader you're connecting to.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.

 Use InternetEasyConnectConfiguration or TapToPayEasyConnectConfiguration
 depending on the reader you're connecting to.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
