//
//  SCPPaymentMethod.h
//  StripeTerminal
//
//  Created by Daniel Jackson on 3/12/19.
//  Copyright © 2019 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPJSONDecodable.h>
#import <StripeTerminal/SCPPaymentMethodType.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPCardDetails, SCPCardPresentDetails, SCPWechatPayDetails, SCPAffirmDetails;

/**
 PaymentMethod objects represent your customer's payment instruments.
 They can be used with PaymentIntents to collect payments, or saved
 to Customer objects to store instrument details for future payments.

 @see https://stripe.com/docs/api/payment_methods
 @see https://stripe.com/docs/payments/payment-methods/saving#attach-method
 */
NS_SWIFT_NAME(PaymentMethod)
@interface SCPPaymentMethod : NSObject <SCPJSONDecodable>

/**
 The unique identifier for the PaymentMethod
 */
@property (nonatomic, readonly) NSString *stripeId;

/**
 Time at which the object was created. Measured in seconds since the Unix epoch.
 */
@property (nonatomic, nullable, readonly) NSDate *created;

/**
 The type of the PaymentMethod.  The corresponding, similarly named property contains additional information specific to the PaymentMethod type.
 e.g. if the type is `SCPPaymentMethodTypeCard`, the `card` property is also populated.
 */
@property (nonatomic, readonly) SCPPaymentMethodType type;

/**
 If this is a card PaymentMethod (ie `self.type == SCPPaymentMethodTypeCard`), this contains additional details.
 */
@property (nonatomic, nullable, readonly) SCPCardDetails *card;

/**
 If this is a card_present PaymentMethod (ie `self.type == SCPPaymentMethodTypeCardPresent`), this contains additional details.
 */
@property (nonatomic, nullable, readonly) SCPCardPresentDetails *cardPresent;

/**
 If this is an Interac_present PaymentMethod (ie `self.type == SCPPaymentMethodTypeInteracPresent`), this contains additional details.
 */
@property (nonatomic, nullable, readonly) SCPCardPresentDetails *interacPresent;

/**
 If this is a wechat_pay PaymentMethod (ie `self.type == SCPPaymentMethodTypeWechatPay`), this contains additional details.
 */
@property (nonatomic, nullable, readonly) SCPWechatPayDetails *wechatPay;

/**
 If this is a affirm PaymentMethod (ie `self.type == SCPPaymentMethodTypeAffirm`), this contains additional details.
 */
@property (nonatomic, nullable, readonly) SCPAffirmDetails *affirm;

/**
 The Customer that this PaymentMethod is attached to, or nil.
 */
@property (nonatomic, nullable, readonly) NSString *customer;

/**
 Set of key-value pairs that you can attach to an object. This can be useful for storing additional information about the object in a structured format.

 @see https://stripe.com/docs/api#metadata
 */
@property (nonatomic, readonly) NSDictionary<NSString *, NSString *> *metadata;

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
