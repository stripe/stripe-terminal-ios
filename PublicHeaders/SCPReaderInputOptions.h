//
//  SCPReaderInputOptions.h
//  StripeTerminal
//
//  Created by Ben Guo on 9/11/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This represents all of the input methods available to your user when the
 reader begins waiting for input.
 */
typedef NS_OPTIONS(NSUInteger, SCPReaderInputOptions) {
    /**
     No input options are available on the reader.
     */
    SCPReaderInputOptionNone = 0,

    /**
     Swipe a magstripe card.
     */
    SCPReaderInputOptionSwipeCard = 1 << 0,

    /**
     Insert a chip card.
     */
    SCPReaderInputOptionInsertCard = 1 << 1,

    /**
     Tap a contactless card.
     */
    SCPReaderInputOptionTapCard = 1 << 2,
} NS_SWIFT_NAME(ReaderInputOptions);

NS_ASSUME_NONNULL_END
