//
//  SCPBatteryStatus.h
//  StripeTerminal
//
//  Created by Brian Cooke on 4/29/2021.
//  Copyright © 2021 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A categorization of a reader's battery charge level.
 */
typedef NS_ENUM(NSUInteger, SCPBatteryStatus) {
    /// Battery state is not yet known or not available for the connected reader.
    SCPBatteryStatusUnknown,

    /// The device's battery is less than or equal to 5%.
    SCPBatteryStatusCritical,

    /// The device's battery is between 5% and 20%.
    SCPBatteryStatusLow,

    /// The device's battery is greater than 20%.
    SCPBatteryStatusNominal,
} NS_SWIFT_NAME(BatteryStatus);

NS_ASSUME_NONNULL_END
