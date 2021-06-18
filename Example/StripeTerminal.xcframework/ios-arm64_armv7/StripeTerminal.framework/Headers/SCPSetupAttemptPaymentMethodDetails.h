//
//  SCPSetupAttemptPaymentMethodDetails.h
//  StripeTerminal
//
//  Created by James Little on 1/18/21.
//  Copyright © 2021 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPJSONDecodable.h>
#import <StripeTerminal/SCPPaymentMethodType.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPSetupAttemptCardPresentDetails;

/**
 Details about a PaymentMethod at a specific time. ex: at time of transaction
 for a SetupAttempt.

 @see https://stripe.com/docs/api/setup_attempts/object#setup_attempt_object-payment_method_details

 Unlike an SCPPaymentMethod, the details object does not have a `stripeId`,
 and only exists as a sub-object of another Stripe object.
 */
NS_SWIFT_NAME(SetupAttemptPaymentMethodDetails)
@interface SCPSetupAttemptPaymentMethodDetails : NSObject <SCPJSONDecodable>

/**
 The type of the PaymentMethod. The corresponding, similarly named property
 contains additional information specific to the PaymentMethod type.
 e.g. if the type is `SCPPaymentMethodTypeCardPresent`, the `cardPresent`
 property is also populated.
 */
@property (nonatomic, readonly) SCPPaymentMethodType type;

/**
 If this is a card present payment method (ie `self.type == SCPPaymentMethodTypeCardPresent`),
 this contains additional information.
 */
@property (nonatomic, nullable, readonly) SCPSetupAttemptCardPresentDetails *cardPresent;

/**
 If this is a card present payment method (ie `self.type == SCPPaymentMethodTypeInteracPresent`),
 this contains additional information.
 */
@property (nonatomic, nullable, readonly) SCPSetupAttemptCardPresentDetails *interacPresent;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
