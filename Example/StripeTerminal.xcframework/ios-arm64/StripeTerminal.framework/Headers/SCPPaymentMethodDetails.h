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

#import <StripeTerminal/SCPJSONDecodable.h>
#import <StripeTerminal/SCPPaymentMethodType.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPCardPresentDetails;
@class SCPWechatPayDetails;
@class SCPAffirmDetails;

/**
 Details about a PaymentMethod at a specific time. ex: at time of transaction
 for a Charge.

 @see https://stripe.com/docs/api/charges/object#charge_object-payment_method_details

 Unlike an SCPPaymentMethod, the details object does not have a `stripeId`,
 and only exists as a sub-object of another Stripe object.
 */
NS_SWIFT_NAME(PaymentMethodDetails)
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
 If this is an Interac present payment method (ie `self.type == SCPPaymentMethodTypeInteracPresent`),
 this contains additional information.
 */
@property (nonatomic, nullable, readonly) SCPCardPresentDetails *interacPresent;

/**
 If this is a Wechat pay payment method (ie `self.type == SCPPaymentMethodTypeWechatPay`),
 this contains additional information.
 */
@property (nonatomic, nullable, readonly) SCPWechatPayDetails *wechatPay;

/**
 If this is an Affirm payment method (ie `self.type == SCPPaymentMethodTypeAffirm`),
 this contains additional information.
 */
@property (nonatomic, nullable, readonly) SCPAffirmDetails *affirm;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
