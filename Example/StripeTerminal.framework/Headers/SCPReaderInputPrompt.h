//
//  SCPReaderInputPrompt.h
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
 The possible prompts to emitted by the reader as it is accepting input.
 */
typedef NS_ENUM(NSUInteger, SCPReaderInputPrompt) {
    /**
     Retry the presented card.
     */
    SCPReaderInputPromptRetryCard,
    /**
     Insert the presented card.
     */
    SCPReaderInputPromptInsertCard,
    /**
     Insert or swipe the presented card.
     */
    SCPReaderInputPromptInsertOrSwipeCard,
    /**
     Swipe the presented card.
     */
    SCPReaderInputPromptSwipeCard,
    /**
     Remove the presented card.
     */
    SCPReaderInputPromptRemoveCard,
    /**
     The reader detected multiple contactless cards. Make sure only one
     contactless card or NFC device is near the reader.
     */
    SCPReaderInputPromptMultipleContactlessCardsDetected,
    /**
     The card could not be read. Try another read method on the same card, or
     use a different card.
     */
    SCPReaderInputPromptTryAnotherReadMethod,
    /**
     The card is invalid. Try another card.
     */
    SCPReaderInputPromptTryAnotherCard,
} NS_SWIFT_NAME(ReaderInputPrompt);

NS_ASSUME_NONNULL_END
