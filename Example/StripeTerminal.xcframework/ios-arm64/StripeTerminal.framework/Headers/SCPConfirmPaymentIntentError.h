//
//  SCPConfirmPaymentIntentError.h
//  StripeTerminal
//
//  Created by Ben Guo on 5/11/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPErrors.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPPaymentIntent;

/**
 An error from `-[SCPTerminal confirmPaymentIntent:completion:]`.

 @see https://stripe.com/docs/terminal/payments#process
 */
NS_SWIFT_NAME(ConfirmPaymentIntentError)
@interface SCPConfirmPaymentIntentError : NSError

/**
 The updated PaymentIntent after `confirmPaymentIntent` failed.

 1. If the status of the updated PaymentIntent is still `.requiresConfirmation`
 (e.g the request failed because your app is not connected to the internet),
 you may call `confirmPaymentIntent` again with the updated PaymentIntent to
 retry the request.

 2. If the status of the updated PaymentIntent is `.requiresPaymentMethod` (e.g. the
 request failed because the card was declined), you should call
 `collectPaymentMethod` with the updated PaymentIntent to try charging another
 card.

 3. If this value is `nil`, the request timed out, and the status of the
 PaymentIntent is unknown. We recommend that you retry `confirmPaymentIntent` using
 the original PaymentIntent. If you instead choose to abandon the original
 PaymentIntent and create a new one, you should be sure **not** to capture the
 original PaymentIntent.
 */
@property (nonatomic, nullable, readonly) SCPPaymentIntent *paymentIntent;

/**
 If `confirmPaymentIntent` failed because the underlying network request errored,
 this property contains additional details about the error.
 */
@property (nonatomic, nullable, readonly) NSError *requestError;

/**
 If `confirmPaymentIntent` failed because the payment method was declined, this
 property contains the decline code.
 */
@property (nonatomic, nullable, readonly) NSString *declineCode;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
