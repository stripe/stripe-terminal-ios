//
//  SCPInternetEasyConnectConfiguration.h
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

@class SCPInternetDiscoveryConfiguration;
@class SCPInternetConnectionConfiguration;

NS_ASSUME_NONNULL_BEGIN

/**
 EasyConnectConfiguration for internet readers, which simplifies discovery and connecting to internet readers.

 Note: The discoveryConfiguration must include a DiscoveryFilter that will filter the discovery
 results to a single reader. Otherwise the easy connect process will fail if multiple readers are found.
 */
NS_SWIFT_NAME(InternetEasyConnectConfiguration)
@interface SCPInternetEasyConnectConfiguration : SCPEasyConnectConfiguration

/**
 Initializes an InternetEasyConnectConfiguration with the provided discovery and connection configurations.

 @param discoveryConfiguration The internet discovery configuration. Must include a DiscoveryFilter.
 @param connectionConfiguration The internet connection configuration.
 @return An initialized InternetEasyConnectConfiguration.
 */
- (instancetype)initWithDiscoveryConfiguration:(SCPInternetDiscoveryConfiguration *)discoveryConfiguration
                       connectionConfiguration:(SCPInternetConnectionConfiguration *)connectionConfiguration NS_DESIGNATED_INITIALIZER;

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
