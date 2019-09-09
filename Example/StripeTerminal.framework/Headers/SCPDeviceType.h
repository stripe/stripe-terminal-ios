//
//  SCPDeviceType.h
//  StripeTerminal
//
//  Created by Ben Guo on 9/9/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

NS_ASSUME_NONNULL_BEGIN

/**
 The possible device types for a reader.

 @see https://stripe.com/docs/terminal/readers
 */
typedef NS_ENUM(NSUInteger, SCPDeviceType) {
    /**
     Chipper 2X

     @see https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt
     */
    SCPDeviceTypeChipper2X,
} NS_SWIFT_NAME(DeviceType);

NS_ASSUME_NONNULL_END
