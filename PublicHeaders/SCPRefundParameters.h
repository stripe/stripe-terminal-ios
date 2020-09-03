//
//  SCPRefundParameters.h
//  StripeTerminal
//
//  Created by James Little on 2/10/20.
//  Copyright © 2020 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import "SCPPaymentIntent.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Parameters for creating an `SCPRefund`.

 @see https://stripe.com/docs/api/refunds/create
 */
NS_SWIFT_NAME(RefundParameters)
@interface SCPRefundParameters : NSObject

/**
 The ID of the charge to be refunded.
 */
@property (nonatomic, nullable, readonly) NSString *chargeId;

/**
 The amount of the refund, provided in the currency's smallest unit.
 */
@property (nonatomic, readonly) NSUInteger amount;

/**
 Three-letter ISO currency code. Must be a supported currency.
 */
@property (nonatomic, readonly) NSString *currency;

/**
 Set of key-value pairs that you can attach to an object. This can be useful for
 storing additional information about the object in a structured format.
 */
@property (nonatomic, copy, nullable, readwrite) NSDictionary *metadata;

/**
 Connect only: Nullable boolean indicating whether the transfer should be
 reversed when refunding this charge. The transfer will be reversed proportionally
 to the amount being refunded (either the entire or partial amount).

 @note This property is a nullable NSNumber being used to represent a nullable
 boolean. A value of 0 represents `false`, while any non-zero value represents
 `true`.

 @see https://stripe.com/docs/api/refunds/create#create_refund-reverse_transfer
 */
@property (nonatomic, nullable, readwrite) NSNumber *reverseTransfer;

/**
 Connect only: Nullable boolean indicating whether the application fee should be
 refunded when refunding this charge. If a full charge refund is given, the
 full application fee will be refunded. Otherwise, the application fee will be
 refunded in an amount proportional to the amount of the charge refunded.

 @note This property is a nullable NSNumber being used to represent a nullable
 boolean. A value of 0 represents `false`, while any non-zero value represents
 `true`.

 @see https://stripe.com/docs/api/refunds/create#create_refund-refund_application_fee
 */
@property (nonatomic, nullable, readwrite) NSNumber *refundApplicationFee;

/**
 Initializes `SCPRefundParameters` with the given charge, amount, and currency.

 @param chargeId    The ID of the charge to be refunded.

 @param amount      The amount to be refunded, provided in the currency's
 smallest unit.

 @param currency    The currency of the original charge. You cannot refund a charge
 with a different currency than the currency that was used to create the charge.
 */
- (instancetype)initWithChargeId:(NSString *)chargeId
                          amount:(NSUInteger)amount
                        currency:(NSString *)currency;

/**
 Use `initWithChargeId:amount:currency:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithChargeId:amount:currency:`
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
