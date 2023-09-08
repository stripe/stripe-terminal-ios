//
//  SCPBluetoothProximityDiscoveryConfiguration.h
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
 The Bluetooth Proximity discovery method searches for a subset of
 Stripe Terminal's Bluetooth-capable readers.

 If your app will be used in a busy environment with multiple iOS
 devices pairing to multiple available readers at the same time, we
 recommend using this discovery method.

 After a reader has been discovered using this method, the LEDs located
 above the reader's power button will start flashing multiple colors.
 After discovering the reader, your app should prompt the user to confirm
 that the reader is flashing, and require a user action (e.g. tapping a
 button) to connect to the reader.

 When discovering a reader using this method, the `didUpdateDiscoveredReaders`
 delegate method will be called twice. It will be called for the first time
 when the reader is initially discovered. The reader's LEDs will begin
 flashing. After a short delay, `didUpdateDiscoveredReaders` will be called
 a second time with an updated reader object, populated with additional
 info about the device, like its battery level.

 Create instances of this class using a `SCPBluetoothProximityDiscoveryConfigurationBuilder`.

 @note The Bluetooth Proximity discovery method can only discover
 Stripe Reader M2 and BBPOS Chipper 2X BT readers.

 @note The simulated Bluetooth Proximity discovery method will always return
 a Stripe Reader M2 simulated device.
 */
NS_SWIFT_NAME(BluetoothProximityDiscoveryConfiguration)
@interface SCPBluetoothProximityDiscoveryConfiguration : NSObject <SCPDiscoveryConfiguration>

@end

/**
 Builder for the Bluetooth Proximity discovery class.

 Example usage:

 `[[[SCPBluetoothProximityDiscoveryConfigurationBuilder new] setSimulated:YES] build]`

 `BluetoothProximityDiscoveryConfigurationBuilder().setSimulated(true).build()`
 */
NS_SWIFT_NAME(BluetoothProximityDiscoveryConfigurationBuilder)
@interface SCPBluetoothProximityDiscoveryConfigurationBuilder : SCPBuilder <SCPBluetoothProximityDiscoveryConfiguration *>

/// Set the simulated property for the discovery configuration that will be built
- (SCPBluetoothProximityDiscoveryConfigurationBuilder *)setSimulated:(BOOL)simulated;

@end

NS_ASSUME_NONNULL_END
