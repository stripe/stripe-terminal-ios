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
 */
typedef NS_ENUM(NSUInteger, SCPDeviceType) {
    /**
     Chipper 2X
     */
    SCPDeviceTypeChipper2X,
    /**
     A reader simulator.
     */
    SCPDeviceTypeReaderSimulator,
} NS_SWIFT_NAME(DeviceType);

NS_ASSUME_NONNULL_END
