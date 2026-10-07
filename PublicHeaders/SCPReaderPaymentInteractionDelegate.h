//
//  SCPReaderPaymentInteractionDelegate.h
//  StripeTerminal
//
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

@class SCPPaymentInteraction;
@class SCPReader;

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle payment interactions for mobile and tap to pay readers that require your application to display
 UI and provide a response before the payment can continue.

 The provided delegate must be retained by your application until the reader disconnects.
 */
NS_SWIFT_NAME(ReaderPaymentInteractionDelegate)
@protocol SCPReaderPaymentInteractionDelegate <NSObject>

/**
 This method is called when a payment interaction requires a response from your application.

 Inspect the concrete `SCPPaymentInteraction` subclass to determine which UI to display and use
 its completion method to continue the payment.

 @param reader      The originating reader.
 @param interaction The payment interaction requiring a response.
 */
- (void)reader:(SCPReader *)reader
    didRequestInteraction:(SCPPaymentInteraction *)interaction NS_SWIFT_NAME(reader(_:didRequestInteraction:));

@end

NS_ASSUME_NONNULL_END
