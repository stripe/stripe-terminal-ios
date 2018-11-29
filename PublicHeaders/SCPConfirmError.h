//
//  SCPConfirmError.h
//  StripeTerminal
//
//  Created by Ben Guo on 5/11/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPErrors.h"

NS_ASSUME_NONNULL_BEGIN

@class SCPPaymentIntent;

/**
 An error confirming a PaymentIntent.
 */
NS_SWIFT_NAME(ConfirmError)
@interface SCPConfirmError : NSError

/**
 The updated PaymentIntent after a confirm request errors.

 If the status of the updated PaymentIntent is still `RequiresConfirmation`
 (e.g the request failed because your app is not connected to the internet),
 you may call `confirmPaymentIntent` again with the updated PaymentIntent to
 retry the request.

 If the status of the updated PaymentIntent is `RequiresSource` (e.g. the
 request failed because the card was declined), you should call `collectPaymentMethod`
 with the updated PaymentIntent to try charging another card.

 If this value is nil, the request timed out, and the status of the
 PaymentIntent is unknown. We recommend that you retry confirming the original
 PaymentIntent. If you instead choose to abandon the original PaymentIntent
 and create a new one, you should be sure not to capture the original
 PaymentIntent. On your backend, consider reconciling PaymentIntents with your
 internal orders system to clean up any dangling authorizations.
 */
@property (nonatomic, nullable, readonly) SCPPaymentIntent *paymentIntent;

/**
 If the confirm failed because the underlying network request errored,
 this property contains additional details about the error.
 */
@property (nonatomic, nullable, readonly) NSError *requestError;

/**
 If the confirm failed because the payment method was declined, this property
 contains the decline code.
 */
@property (nonatomic, nullable, readonly) NSString *declineCode;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
