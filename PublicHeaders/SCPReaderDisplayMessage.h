//
//  SCPReaderDisplayMessage.h
//  StripeTerminal
//
//  Created by Ben Guo on 9/17/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The display messages that a reader may request be displayed by your app.
 */
typedef NS_ENUM(NSUInteger, SCPReaderDisplayMessage) {
    /**
     Retry the presented card.
     */
    SCPReaderDisplayMessageRetryCard,
    /**
     Insert the presented card.
     */
    SCPReaderDisplayMessageInsertCard,
    /**
     Insert or swipe the presented card.
     */
    SCPReaderDisplayMessageInsertOrSwipeCard,
    /**
     Swipe the presented card.
     */
    SCPReaderDisplayMessageSwipeCard,
    /**
     Remove the presented card.
     */
    SCPReaderDisplayMessageRemoveCard,
    /**
     The reader detected multiple contactless cards. Make sure only one
     contactless card or NFC device is near the reader.
     */
    SCPReaderDisplayMessageMultipleContactlessCardsDetected,
    /**
     The card could not be read. Try another read method on the same card, or
     use a different card.
     */
    SCPReaderDisplayMessageTryAnotherReadMethod,
    /**
     The card is invalid. Try another card.
     */
    SCPReaderDisplayMessageTryAnotherCard,
} NS_SWIFT_NAME(ReaderDisplayMessage);

NS_ASSUME_NONNULL_END
