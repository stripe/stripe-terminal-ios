//
//  SCPOfflineDelegate.h
//  StripeTerminal
//
//  Created by James Little on 11/4/21.
//  Copyright © 2021 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPNetworkStatus.h>
#import <StripeTerminal/SCPOfflineStatus.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPTerminal;
@class SCPPaymentIntent;

/**
 Implement this protocol to handle callbacks when the SDK is performing
 actions related to offline mode.
 */
NS_SWIFT_NAME(OfflineDelegate)
@protocol SCPOfflineDelegate

/**
 This method is called on the offline delegate when any of the underlying
 `offlineStatus` fields have changed.
 */
- (void)terminal:(SCPTerminal *)terminal
    didChangeOfflineStatus:(SCPOfflineStatus *)offlineStatus;

/**
 This method is called on the offline delegate when a locally stored payment
 intent was forwarded to stripe.com.

 @param intent The SCPPaymentIntent that was forwarded. This will always be provided.
               If there was an error, the `intent` contains the local representation
               and the `intent.offlineDetails` can be used to identify the payment.
 @param error  The error, if an error occurred.
 */
- (void)terminal:(SCPTerminal *)terminal
    didForwardPaymentIntent:(SCPPaymentIntent *)intent
                      error:(nullable NSError *)error;

/**
 This method is called on the offline delegate when the Stripe Terminal SDK
 encounters an error that is not specific to any particular Payment Intent. For
 example, if the SDK fails to fetch a connection token as part of the
 forwarding process, this method will be called with an appropriate error.

 Note that if an error is encountered during the course of forwarding a
 specific payment intent, `didForwardPaymentIntent` will be called with a
 non-nil `error` argument.
 */
- (void)terminal:(SCPTerminal *)terminal didReportForwardingError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
