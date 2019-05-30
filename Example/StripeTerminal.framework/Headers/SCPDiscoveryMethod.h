//
//  SCPDiscoveryMethod.h
//  StripeTerminal
//
//  Created by Evan Sandler on 10/17/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

NS_ASSUME_NONNULL_BEGIN

/**
 The possible methods for discovering a reader.

 @see https://stripe.com/docs/terminal/readers/connecting
 */
typedef NS_ENUM(NSUInteger, SCPDiscoveryMethod) {
    /**
     Bluetooth Scan

     When discovering a reader using this method, the `didUpdateDiscoveredReaders`
     delegate method will be called multiple times as the Bluetooth scan
     proceeds.
     */
    SCPDiscoveryMethodBluetoothScan,
    /**
     Bluetooth Proximity

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
     */
    SCPDiscoveryMethodBluetoothProximity,
} NS_SWIFT_NAME(DiscoveryMethod);

NS_ASSUME_NONNULL_END
