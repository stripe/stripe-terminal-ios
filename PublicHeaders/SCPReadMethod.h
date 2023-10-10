//
//  SCPReadMethod.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/27/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 How card details were read in this transaction.
 */
typedef NS_ENUM(NSUInteger, SCPReadMethod) {
    /**
     An unknown card read method
     */
    SCPReadMethodUnknown = 0,
    /**
     Inserting a chip card into the card reader.
     */
    SCPReadMethodContactEMV = 5,
    /**
     Tapping a contactless-enabled chip card or mobile wallet.
     */
    SCPReadMethodContactlessEMV = 7,
    /**
     When inserting a chip card fails three times in a row, fallback to a magnetic stripe read.
     */
    SCPReadMethodMagneticStripeFallback = 80,
    /**
     Swiping a card using the magnetic stripe reader.
     */
    SCPReadMethodMagneticStripeTrack2 = 90,
    /**
     Older standard for contactless payments that emulated a magnetic stripe read.
     */
    SCPReadMethodContactlessMagstripeMode = 91,
};

NS_ASSUME_NONNULL_END
