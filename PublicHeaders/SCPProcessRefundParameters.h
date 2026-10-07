//
//  SCPProcessRefundParameters.h
//  StripeTerminal
//
//  Created by James Little on 2/10/20.
//  Copyright © 2020 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPPaymentIntent.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Parameters for processing an in-person `SCPRefund`.

 @see https://stripe.com/docs/api/refunds/create
 */
NS_SWIFT_NAME(ProcessRefundParameters)
@interface SCPProcessRefundParameters : NSObject

/**
 The ID of the payment intent to be refunded.
 */
@property (nonatomic, nullable, readonly) NSString *paymentIntentId;

/**
 The client secret for the PaymentIntent.
 */
@property (nonatomic, nullable, readonly) NSString *clientSecret;

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

 @note The metadata property is not set when issuing refunds with the Verifone P400 reader.

 @see https://stripe.com/docs/api#metadata
 */
@property (nonatomic, nullable, readonly) NSDictionary<NSString *, NSString *> *metadata;

/**
 Connect only: Nullable boolean indicating whether the transfer should be
 reversed when refunding this charge. The transfer will be reversed proportionally
 to the amount being refunded (either the entire or partial amount).

 @note This property is a nullable NSNumber being used to represent a nullable
 boolean. A value of 0 represents `false`, while any non-zero value represents
 `true`.

 @see https://stripe.com/docs/api/refunds/create#create_refund-reverse_transfer
 */
@property (nonatomic, nullable, readonly) NSNumber *reverseTransfer;

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
@property (nonatomic, nullable, readonly) NSNumber *refundApplicationFee;

/**
 Use `SCPProcessRefundParametersBuilder`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPProcessRefundParametersBuilder`
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder class for `SCPProcessRefundParameters`.
 */
NS_SWIFT_NAME(ProcessRefundParametersBuilder)
@interface SCPProcessRefundParametersBuilder : SCPBuilder <SCPProcessRefundParameters *>

/**
 Initializes `SCPProcessRefundParametersBuilder` with the given payment intent, client secret, amount, and currency.

 @param paymentIntentId    The ID of the PaymentIntent to be refunded.

 @param clientSecret       The client secret for the PaymentIntent.

 @param amount      The amount to be refunded, provided in the currency's
 smallest unit.

 @param currency    The currency of the original charge. You cannot refund a charge
 with a different currency than the currency that was used to create the charge.
 */
- (instancetype)initWithPaymentIntentId:(NSString *)paymentIntentId
                           clientSecret:(NSString *)clientSecret
                                 amount:(NSUInteger)amount
                               currency:(NSString *)currency;

/**
 Initializes `SCPProcessRefundParametersBuilder` with the given charge, amount, and currency.

 @param chargeId    The ID of the charge to be refunded.

 @param amount      The amount to be refunded, provided in the currency's
 smallest unit.

 @param currency    The currency of the original charge. You cannot refund a charge
 with a different currency than the currency that was used to create the charge.
 */
- (instancetype)initWithChargeId:(NSString *)chargeId
                          amount:(NSUInteger)amount
                        currency:(NSString *)currency;

/// @see SCPProcessRefundParameters.chargeId
- (SCPProcessRefundParametersBuilder *)setChargeId:(NSString *)chargeId;

/// @see SCPProcessRefundParameters.paymentIntentId
- (SCPProcessRefundParametersBuilder *)setPaymentIntentId:(NSString *)paymentIntentId;

/// @see SCPProcessRefundParameters.clientSecret
- (SCPProcessRefundParametersBuilder *)setClientSecret:(NSString *)clientSecret;

/// @see SCPProcessRefundParameters.amount
- (SCPProcessRefundParametersBuilder *)setAmount:(NSUInteger)amount;

/// @see SCPProcessRefundParameters.currency
- (SCPProcessRefundParametersBuilder *)setCurrency:(NSString *)currency;

/// @see SCPProcessRefundParameters.metadata
- (SCPProcessRefundParametersBuilder *)setMetadata:(nullable NSDictionary<NSString *, NSString *> *)metadata;

/// @see SCPProcessRefundParameters.reverseTransfer
- (SCPProcessRefundParametersBuilder *)setReverseTransfer:(BOOL)reverseTransfer;

/// @see SCPProcessRefundParameters.refundApplicationFee
- (SCPProcessRefundParametersBuilder *)setRefundApplicationFee:(BOOL)refundApplicationFee;

/**
 Use `initWithChargeId:amount:currency:` or `initWithPaymentIntentId:clientSecret:amount:currency:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithChargeId:amount:currency:`
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
