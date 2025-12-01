//
//  SCPTapToPayEasyConnectConfiguration.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2025-10-31.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPEasyConnectConfiguration.h>

@class SCPTapToPayDiscoveryConfiguration;
@class SCPTapToPayConnectionConfiguration;

NS_ASSUME_NONNULL_BEGIN

/**
 Configuration for EasyConnect connections to Tap to Pay readers.
 */
NS_SWIFT_NAME(TapToPayEasyConnectConfiguration)
@interface SCPTapToPayEasyConnectConfiguration : SCPEasyConnectConfiguration

/**
 Initializes a TapToPayEasyConnectConfiguration with the provided discovery and connection configurations.

 @param discoveryConfiguration The Tap to Pay discovery configuration.
 @param connectionConfiguration The Tap to Pay connection configuration.
 @return An initialized TapToPayEasyConnectConfiguration.
 */
- (instancetype)initWithDiscoveryConfiguration:(SCPTapToPayDiscoveryConfiguration *)discoveryConfiguration
                       connectionConfiguration:(SCPTapToPayConnectionConfiguration *)connectionConfiguration NS_DESIGNATED_INITIALIZER;

/**
 Use initWithDiscoveryConfiguration:connectionConfiguration: instead.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use initWithDiscoveryConfiguration:connectionConfiguration: instead.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
