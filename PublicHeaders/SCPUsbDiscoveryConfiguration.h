//
//  SCPUsbDiscoveryConfiguration.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2024-02-16.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#ifdef SCP_USB_ENABLED

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPDiscoveryConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The USB discovery method searches for Stripe Terminal's
 USB-capable readers.

 When discovering a reader using this method, the `didUpdateDiscoveredReaders`
 delegate method will be called once when a reader is discovered.

 Create instances of this class using a `SCPUsbDiscoveryConfigurationBuilder`.
 */
NS_SWIFT_NAME(UsbDiscoveryConfiguration)
@interface SCPUsbDiscoveryConfiguration : NSObject <SCPDiscoveryConfiguration>

/**
 The timeout (in seconds) after which `discoverReaders:` should fail. If the
 value is `0` (the default), discoverReaders will never timeout.
 */
@property (nonatomic, assign, readonly) NSUInteger timeout;

@end

/**
 Builder class for SCPUsbDiscoveryConfiguration
 */
NS_SWIFT_NAME(UsbDiscoveryConfigurationBuilder)
@interface SCPUsbDiscoveryConfigurationBuilder : SCPBuilder <SCPUsbDiscoveryConfiguration *>

/// Set the simulated property for the discovery configuration that will be built
- (SCPUsbDiscoveryConfigurationBuilder *)setSimulated:(BOOL)simulated;

/// Set the timeout value for the discovery configuration that will be built
- (SCPUsbDiscoveryConfigurationBuilder *)setTimeout:(NSUInteger)timeout;

@end

NS_ASSUME_NONNULL_END

#endif // SCP_USB_ENABLED
