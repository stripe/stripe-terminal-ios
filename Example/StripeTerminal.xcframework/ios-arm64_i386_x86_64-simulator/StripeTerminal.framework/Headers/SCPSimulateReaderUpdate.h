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
 a simulated bluetooth reader.
 */
typedef NS_ENUM(NSUInteger, SCPSimulateReaderUpdate) {
    /// Default: An update is available that is marked as needing to be installed within 7 days
    SCPSimulateReaderUpdateAvailable = 0,

    /// No updates are available
    SCPSimulateReaderUpdateNone,

    /**
     A required full reader software update exists. Use this to simulate the
     auto-install of a required update that will be applied during connect.
     This simulated update will take 1 minute and progress will be provided
     to the delegate provided to `connectBluetoothReader`.

     @see SCPBluetoothReaderReaderDelegate
     */
    SCPSimulateReaderUpdateRequired,

    /**
     A required update exists. When the SDK connects
     to the reader, the connection will fail because the reader's
     battery is too low for the update to begin.
     */
    SCPSimulateReaderUpdateLowBattery,

    /**
     Randomly picks a type of update for the reader to help exercise the
     various states.
     */
    SCPSimulateReaderUpdateRandom,
} NS_SWIFT_NAME(SimulateReaderUpdate);

NS_ASSUME_NONNULL_END
