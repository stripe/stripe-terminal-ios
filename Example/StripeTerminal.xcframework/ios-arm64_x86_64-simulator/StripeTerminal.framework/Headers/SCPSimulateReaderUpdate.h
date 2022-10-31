//
//  SCPSimulateReaderUpdate.h
//  StripeTerminal
//
//  Created by Brian Cooke on 5/29/20.
//  Copyright © 2020 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Enum used to simulate various types of reader updates being available for
 a simulated bluetooth or local mobile reader.
 */
typedef NS_ENUM(NSUInteger, SCPSimulateReaderUpdate) {
    /**
     Default value.
     - When connecting to a Bluetooth reader, an update is available that is marked
       as needing to be installed within 7 days.
     - When connecting to a Local Mobile reader, a mandatory update will complete
       during the connection flow.
     */
    SCPSimulateReaderUpdateAvailable = 0,

    /// No updates are available
    SCPSimulateReaderUpdateNone,

    /**
     A required full reader software update exists. Use this to simulate the
     auto-install of a required update that will be applied during connect.
     This simulated update will take 1 minute and progress will be provided
     to the delegate provided to `connectBluetoothReader` or
     `connectLocalMobileReader` as appropriate.

     @see SCPBluetoothReaderReaderDelegate
     @see SCPLocalMobileReaderDelegate
     */
    SCPSimulateReaderUpdateRequired,

    /**
     A required update exists.
     - When connecting to a Bluetooth reader, the connection will fail because
       the reader's battery is too low for an update to begin.
     - When connecting to a Local Mobile reader, a mandatory update will
       complete during the connection flow.
     */
    SCPSimulateReaderUpdateLowBattery,

    /**
     Randomly picks a type of update for the reader to help exercise the
     various states.
     */
    SCPSimulateReaderUpdateRandom,
} NS_SWIFT_NAME(SimulateReaderUpdate);

NS_ASSUME_NONNULL_END
