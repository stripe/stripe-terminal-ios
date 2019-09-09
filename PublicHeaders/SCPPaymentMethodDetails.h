//
//  SCPPaymentMethodDetails.h
//  StripeTerminal
//
//  Created by Daniel Jackson on 4/15/19.
//  Copyright © 2019 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPJSONDecodable.h"
#import "SCPPaymentMethodType.h"

NS_ASSUME_NONNULL_BEGIN

@class SCPCardPresentDetails;

/**
 Details about a PaymentMethod at a specific time. ex: at time of transaction
 for a Charge.

 @see https://stripe.com/docs/api/charges/object#charge_object-payment_method_details

 Unlike an SCPPaymentMethod, the details object does not have a `stripeId`,
 and only exists as a sub-object of another Stripe object.
 */
@interface SCPPaymentMethodDetails : NSObject <SCPJSONDecodable>

/**
 The type of the PaymentMethod.  The corresponding, similarly named property
 contains additional information specific to the PaymentMethod type.
 e.g. if the type is `SCPPaymentMethodTypeCardPresent`, the `cardPresent`
 property is also populated.
 */
@property (nonatomic, readonly) SCPPaymentMethodType type;

/**
 If this is a card present payment method (ie `self.type == SCPPaymentMethodTypeCardPresent`),
 this contains additional information.
 */
@property (nonatomic, nullable, readonly) SCPCardPresentDetails *cardPresent;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
