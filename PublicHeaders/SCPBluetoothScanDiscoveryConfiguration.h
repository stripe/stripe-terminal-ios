//
//  SCPBluetoothScanDiscoveryConfiguration.h
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
 The Bluetooth Scan discovery method searches for Stripe Terminal's
 Bluetooth-capable readers.

 When discovering a reader using this method, the `didUpdateDiscoveredReaders`
 delegate method will be called multiple times as the Bluetooth scan
 proceeds.

 Create instances of this class using a `SCPBluetoothScanDiscoveryConfigurationBuilder`.
 */
NS_SWIFT_NAME(BluetoothScanDiscoveryConfiguration)
@interface SCPBluetoothScanDiscoveryConfiguration : NSObject <SCPDiscoveryConfiguration>

/**
 The timeout (in seconds) after which `discoverReaders:` should fail. If the
 value is `0` (the default), discoverReaders will never timeout.
 */
@property (nonatomic, assign, readonly) NSUInteger timeout;

@end

/**
 Builder class for SCPBluetoothScanDiscoveryConfiguration
 */
NS_SWIFT_NAME(BluetoothScanDiscoveryConfigurationBuilder)
@interface SCPBluetoothScanDiscoveryConfigurationBuilder : SCPBuilder <SCPBluetoothScanDiscoveryConfiguration *>

/// Set the simulated property for the discovery configuration that will be built
- (SCPBluetoothScanDiscoveryConfigurationBuilder *)setSimulated:(BOOL)simulated;

/// Set the timeout value for the discovery configuration that will be built
- (SCPBluetoothScanDiscoveryConfigurationBuilder *)setTimeout:(NSUInteger)timeout;

@end

NS_ASSUME_NONNULL_END
