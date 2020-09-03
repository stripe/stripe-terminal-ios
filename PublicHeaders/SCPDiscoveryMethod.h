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
     The Bluetooth Scan discovery method searches for Stripe Terminal's
     Bluetooth-capable readers.

     When discovering a reader using this method, the `didUpdateDiscoveredReaders`
     delegate method will be called multiple times as the Bluetooth scan
     proceeds.
     */
    SCPDiscoveryMethodBluetoothScan,
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

     @note The Bluetooth Proximity discovery method can only discovery Chipper
     2X BT readers.
     */
    SCPDiscoveryMethodBluetoothProximity,

    /**
     The Internet discovery method searches for internet-connected readers,
     such as the Verifone P400 or the BBPOS WisePOS E.

     When discovering a reader with this method `didUpdateDiscoveredReaders`
     will only be called once with a list of readers from `/v1/terminal/readers`.
     Note that this will include readers that are both online and offline.

     Because the discovery process continues if connecting to a discovered
     reader fails, the SDK will refresh the list of `SCPReader`s and call
     `didUpdateDiscoveredReaders` with the results. For more details about failed
     connect calls, see `-[SCPTerminal connectReader:connectionConfig:completion:]`

     @see https://stripe.com/docs/api/terminal/readers/list
     */
    SCPDiscoveryMethodInternet,
} NS_SWIFT_NAME(DiscoveryMethod);

NS_ASSUME_NONNULL_END
