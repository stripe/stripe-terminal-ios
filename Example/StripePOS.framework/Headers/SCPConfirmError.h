//
//  SCPConfirmError.h
//  StripePOS
//
//  Created by Ben Guo on 5/11/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPErrors.h"

NS_ASSUME_NONNULL_BEGIN

@class SCPPaymentIntent;

/**
 An error confirming a payment intent.
 */
@interface SCPConfirmError : NSError

/**
 The updated payment intent after a confirm request errors.

 If this value is nil, the request timed out, and the status of the payment
 intent is unknown. We recommend that you retry confirming the original
 payment intent. If you instead choose to abandon the original payment intent
 and instead create a new one, you should be sure not to capture the original
 payment intent. You may also want to reconcile payment intents with your
 internal orders system to clean up any dangling authorizations.

 If the status of the updated payment intent is still `RequiresConfirmation`
 (e.g the request failed because your app is not connected to the internet),
 you may call `confirmPaymentIntent` again with the updated payment intent to
 retry the request.

 If the status of the updated payment intent is now `RequiresSource` (e.g. the
 request failed because the card was declined), you should call `attachSource`
 with the updated payment intent to try charging another card.
 */
@property (nonatomic, nullable, readonly) SCPPaymentIntent *paymentIntent;

/**
 If the confirm failed and the code is DeclinedByStripeAPI, this property
 contains the decline code.
 */
@property (nonatomic, nullable, readonly) NSString *declineCode;

/**
 If the confirm failed because the underlying charge request errored,
 this property contains additional details about the error.
 */
@property (nonatomic, nullable, readonly) NSError *requestError;

/**
 An unlocalized string describing the error.
 */
@property (nonatomic, readonly) NSString *reason;

/**
 You cannot directly instantiate `SCPConfirmError`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPConfirmError`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
