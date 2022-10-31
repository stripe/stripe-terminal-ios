//
//  SCPLocationStatus.h
//  StripeTerminal
//
//  Created by Brian Cooke on 6/26/20.
//  Copyright © 2020 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Represents the possible states of the `location` object for a
 discovered reader.

 @see `SCPReader`
 */
typedef NS_ENUM(NSUInteger, SCPLocationStatus) {
    /**
     The location is not known. `location` will be nil.

     A reader will only have a location status of `unknown` when a Bluetooth
     reader's full location information failed to fetch properly during discovery.
     */
    SCPLocationStatusUnknown,

    /**
     The location was successfully set to a known location.
     `location` is a valid `SCPLocation`.
     */
    SCPLocationStatusSet,

    /**
     This location is known to be not set. `location` will be nil.
     */
    SCPLocationStatusNotSet,

} NS_SWIFT_NAME(LocationStatus);

NS_ASSUME_NONNULL_END
