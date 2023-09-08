//
//  SCPDiscoveryConfiguration.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/17/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPDiscoveryMethod.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Protocol for classes to conform to that apply configuration options for discovering readers.

 You should not implement this protocol yourself; instead, use one of the following:

 - `SCPBluetoothScanDiscoveryConfiguration`
 - `SCPBluetoothProximityDiscoveryConfiguration`
 - `SCPInternetDiscoveryConfiguration`
 - `SCPLocalMobileDiscoveryConfiguration`

 Objects of those types get passed into the `Terminal.shared.discoverReaders()`
 method to control which devices get discovered, and how.

 @see https://stripe.com/docs/terminal/readers/connecting
 */
NS_SWIFT_NAME(DiscoveryConfiguration)
@protocol SCPDiscoveryConfiguration <NSObject>

/**
 The method by which to discover readers.
 */
@property (nonatomic, readonly) SCPDiscoveryMethod discoveryMethod;

/**
 Whether to use simulated discovery to discover a device simulator.

 The Terminal SDK comes with the ability to simulate behavior without using
 physical hardware. This makes it easy to quickly test your integration
 end-to-end, from pairing with a reader to taking payments.
 */
@property (nonatomic, readonly) BOOL simulated;

@end

NS_ASSUME_NONNULL_END
