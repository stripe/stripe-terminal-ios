//
//  SCPReadCardDelegate.h
//  StripePOS
//
//  Created by Ben Guo on 11/3/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"

NS_ASSUME_NONNULL_BEGIN

@class SCPTerminal;

/**
 The possible card presentation types for a payment.
 */
typedef NS_ENUM(NSUInteger, SCPCardPresentationType) {
    /**
     Swipe a magstripe card.
     */
    SCPCardPresentationTypeSwipe,
    /**
     Insert a chip card.
     */
    SCPCardPresentationTypeInsert,
    /**
     Tap a contactless card.
     */
    SCPCardPresentationTypeTap,
    /**
     Swipe a magstripe card or insert a chip card.
     */
    SCPCardPresentationTypeSwipeOrInsert,
    /**
     Swipe a magstripe card or tap a contactless card.
     */
    SCPCardPresentationTypeSwipeOrTap,
    /**
     Insert a chip card or tap a contactless card.
     */
    SCPCardPresentationTypeInsertOrTap,
    /**
     Swipe, insert, or tap a card.
     */
    SCPCardPresentationTypeSwipeOrInsertOrTap,
};

/**
 The possible prompts to display to the user during attachSource.
 */
typedef NS_ENUM(NSUInteger, SCPReadCardPrompt) {
    /**
     Retry card.
     */
    SCPReadCardPromptRetryCard,
    /**
     Remove card.
     */
    SCPReadCardPromptRemoveCard,
    /**
     The reader detected multiple contactless cards. The cardholder should only
     present one card.
     */
    SCPReadCardPromptMultipleContactlessCardsDetected,
    /**
     Use the magstripe reader.
     */
    SCPReadCardPromptUseMagstripe,
};

/**
 Implement this protocol to handle read card events from calls to attachSource
 and readCard.
 */
@protocol SCPReadCardDelegate <NSObject>

/**
 This method is called when the reader begins waiting for a card. Your app
 should prompt the customer to present a card matching the given presentation
 type. If reading the card fails, the SDK may surface a retry prompt via the
 `terminal:didRequestReadCardPrompt:` method.

 Use `SCPTerminal.stringFromCardPresentationType` to get a user facing string
 for the card presentation type.

 @param terminal            The originating terminal.
 @param presentationType    The type of card presentation required.
 */
- (void)terminal:(SCPTerminal *)terminal
didBeginWaitingForCard:(SCPCardPresentationType)presentationType;

/**
 This method is called to request that a prompt be displayed in your app,
 For example, if the prompt is `UseMagstripe`, your app should instruct the
 user to present the card using the magstripe reader.

 Use `SCPTerminal.stringFromReadCardPrompt` to get a user facing string
 for the action.

 @see SCPReadCardPrompt

 @param terminal       The originating terminal.
 @param prompt         The prompt to request from the cardholder.
 */
- (void)terminal:(SCPTerminal *)terminal didRequestReadCardPrompt:(SCPReadCardPrompt)prompt
NS_SWIFT_NAME(terminal(terminal:didRequestReadCardPrompt:));

@end

NS_ASSUME_NONNULL_END
