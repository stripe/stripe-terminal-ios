//
//  SCPLocalMobileDiscoveryConfiguration.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2023-08-09.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPDiscoveryConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The Local Mobile discovery method searches for any readers built into the
 merchant device that are supported by Stripe Terminal.
 When discovering a reader with this method `didUpdateDiscoveredReaders`
 will only be called once with a list of discovered readers, if any.
 An error may be provided if a discovery attempt is made in an
 on a device without hardware support for the Apple Built-In reader or
 one running an unsupported version of iOS.

 Create instances of this class using a `SCPLocalMobileDiscoveryConfigurationBuilder`.

 @see https://stripe.com/docs/terminal/payments/setup-reader/tap-on-mobile-ios
 */
NS_SWIFT_NAME(LocalMobileDiscoveryConfiguration)
@interface SCPLocalMobileDiscoveryConfiguration : NSObject <SCPDiscoveryConfiguration>

@end

/**
 Builder class for SCPLocalMobileDiscoveryConfiguration

 Example usage:

 `[[[SCPLocalMobileDiscoveryConfigurationBuilder new] setSimulated:YES] build]`

 `try LocalMobileDiscoveryConfigurationBuilder().setSimulated(true).build()`
 */
NS_SWIFT_NAME(LocalMobileDiscoveryConfigurationBuilder)
@interface SCPLocalMobileDiscoveryConfigurationBuilder : SCPBuilder <SCPLocalMobileDiscoveryConfiguration *>

/// Set the simulated property for the discovery configuration that will be built
- (SCPLocalMobileDiscoveryConfigurationBuilder *)setSimulated:(BOOL)simulated;

@end

NS_ASSUME_NONNULL_END
