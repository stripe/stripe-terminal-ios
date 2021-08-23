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
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The possible device types for a reader.

 @see https://stripe.com/docs/terminal/readers
 */
typedef NS_ENUM(NSUInteger, SCPDeviceType) {
    /**
     The BBPOS Chipper 2X BT mobile reader.

     @see https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt
     */
    SCPDeviceTypeChipper2X,

    /**
     The Verifone P400 countertop reader.

     @see https://stripe.com/docs/terminal/readers/verifone-p400
     */
    SCPDeviceTypeVerifoneP400,

    /**
     The BBPOS WisePad 3 mobile reader.

     Support for this reader is currently in beta.
     
     @see https://stripe.com/docs/terminal/readers/bbpos-wisepad3
     */
    SCPDeviceTypeWisePad3,

    /**
     The Stripe Reader M2 mobile reader.

     Support for this reader is currently in beta.
     */
    SCPDeviceTypeStripeM2,

    /**
     The BBPOS WisePOS E countertop reader.

     Support for this reader is currently in beta.

     @see https://stripe.com/docs/terminal/readers/bbpos-wisepos-e
     */
    SCPDeviceTypeWisePosE,

    /**
     The BBPOS Chipper mobile reader.

     :nodoc: Support for this reader is not generally available.
     */
    SCPDeviceTypeChipper1X,

    /**
     The BBPOS WiseCube reader.

     :nodoc: Support for this reader is not generally available.
     */
    SCPDeviceTypeWiseCube,
} NS_SWIFT_NAME(DeviceType);

NS_ASSUME_NONNULL_END
