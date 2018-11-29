//
//  SCPReaderInputDelegate.h
//  StripeTerminal
//
//  Created by Ben Guo on 11/3/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"
#import "SCPReaderInputOptions.h"
#import "SCPReaderInputPrompt.h"

NS_ASSUME_NONNULL_BEGIN

@class SCPTerminal;

/**
 Implement this protocol to handle events from the reader while accepting input.
 */
NS_SWIFT_NAME(ReaderInputDelegate)
@protocol SCPReaderInputDelegate <NSObject>

/**
 This method is called when the reader begins waiting for input. Your app
 should prompt the customer to present a source using one of the given input
 options. If the reader emits a prompt, the `didRequestReaderInputPrompt` method
 will be called.

 Use `stringFromReaderInputOptions` to get a user facing string for the input
 options.

 @param terminal            The originating terminal.
 @param inputOptions        The armed input options on the reader.
 */
- (void)terminal:(SCPTerminal *)terminal
didBeginWaitingForReaderInput:(SCPReaderInputOptions)inputOptions NS_SWIFT_NAME(terminal(_:didBeginWaitingForReaderInput:));

/**
 This method is called to request that a prompt be displayed in your app.
 For example, if the prompt is `SwipeCard`, your app should instruct the
 user to present the card again by swiping it.

 Use `stringFromReaderInputPrompt` to get a user facing string for the prompt.

 @see SCPReaderInputPrompt

 @param terminal            The originating terminal.
 @param inputPrompt         The input prompt to display to the user.
 */
- (void)terminal:(SCPTerminal *)terminal didRequestReaderInputPrompt:(SCPReaderInputPrompt)inputPrompt
NS_SWIFT_NAME(terminal(_:didRequestReaderInputPrompt:));

@end

NS_ASSUME_NONNULL_END
