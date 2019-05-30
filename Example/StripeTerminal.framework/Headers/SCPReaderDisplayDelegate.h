//
//  SCPReaderDisplayDelegate.h
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
#import "SCPReaderDisplayMessage.h"

NS_ASSUME_NONNULL_BEGIN

@class SCPTerminal;

/**
 You must implement this protocol to handle displaying events when connected
 to a reader without a built-in display (e.g., the BBPOS Chipper 2X BT).
 */
NS_SWIFT_NAME(ReaderDisplayDelegate)
@protocol SCPReaderDisplayDelegate <NSObject>

/**
 This method is called when the reader begins waiting for input. Your app
 should prompt the customer to present a payment method using one of the given input
 options. If the reader emits a prompt, the `didRequestReaderDisplayMessage` method
 will be called.

 Use `stringFromReaderInputOptions` to get a user facing string for the input
 options.

 @param terminal            The originating terminal.
 @param inputOptions        The armed input options on the reader.
 */
- (void)terminal:(SCPTerminal *)terminal
didRequestReaderInput:(SCPReaderInputOptions)inputOptions NS_SWIFT_NAME(terminal(_:didRequestReaderInput:));

/**
 This method is called to request that a prompt be displayed in your app.
 For example, if the prompt is `SwipeCard`, your app should instruct the
 user to present the card again by swiping it.

 Use `stringFromReaderDisplayMessage` to get a user facing string for the prompt.

 @see SCPReaderDisplayMessage

 @param terminal            The originating terminal.
 @param displayMessage      The message to display to the user.
 */
- (void)terminal:(SCPTerminal *)terminal didRequestReaderDisplayMessage:(SCPReaderDisplayMessage)displayMessage NS_SWIFT_NAME(terminal(_:didRequestReaderDisplayMessage:));

@end

NS_ASSUME_NONNULL_END
