//
//  SCPConfirmRefundParameters.h
//  StripeTerminal
//
//  Created by Stripe on 9/11/26.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPRefundReason.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Parameters for confirming a refund without collecting a payment method.

 @note This feature is in private preview and is subject to change.

 @see https://docs.stripe.com/api/refunds/create
 */
NS_SWIFT_NAME(ConfirmRefundParameters)
@interface SCPConfirmRefundParameters : NSObject

/**
 The ID of the PaymentIntent to refund.
 */
@property (nonatomic, copy, readonly) NSString *paymentIntentId;

/**
 The client secret for the PaymentIntent.
 */
@property (nonatomic, copy, readonly) NSString *clientSecret;

/**
 The amount to refund, in the currency's smallest unit.

 If omitted, the entire remaining refundable amount is refunded.
 */
@property (nonatomic, nullable, readonly) NSNumber *amount;

/**
 The reason for the refund.
 */
@property (nonatomic, nullable, readonly) SCPRefundReason reason;

/**
 Set of key-value pairs to attach to the Refund.

 @see https://docs.stripe.com/api/refunds/create#create_refund-metadata
 */
@property (nonatomic, nullable, copy, readonly) NSDictionary<NSString *, NSString *> *metadata;

/**
 Connect only: Whether to reverse the transfer when refunding this payment.

 This nullable NSNumber represents a nullable Boolean. A value of 0 represents
 `false`, while any non-zero value represents `true`.
 */
@property (nonatomic, nullable, readonly) NSNumber *reverseTransfer;

/**
 Connect only: Whether to refund the application fee when refunding this
 payment.

 This nullable NSNumber represents a nullable Boolean. A value of 0 represents
 `false`, while any non-zero value represents `true`.
 */
@property (nonatomic, nullable, readonly) NSNumber *refundApplicationFee;

/**
 Email address to send refund instructions to.
 */
@property (nonatomic, nullable, copy, readonly) NSString *instructionsEmail;

/**
 Use `SCPConfirmRefundParametersBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPConfirmRefundParametersBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder class for `SCPConfirmRefundParameters`.
 */
NS_SWIFT_NAME(ConfirmRefundParametersBuilder)
@interface SCPConfirmRefundParametersBuilder : SCPBuilder <SCPConfirmRefundParameters *>

/**
 Initializes the builder with the PaymentIntent to refund.

 @param paymentIntentId The ID of the PaymentIntent to refund.
 @param clientSecret The client secret for the PaymentIntent.
 */
- (instancetype)initWithPaymentIntentId:(NSString *)paymentIntentId
                           clientSecret:(NSString *)clientSecret;

/// @see `SCPConfirmRefundParameters.amount`
- (SCPConfirmRefundParametersBuilder *)setAmount:(NSUInteger)amount;

/// @see `SCPConfirmRefundParameters.reason`
- (SCPConfirmRefundParametersBuilder *)setReason:(nullable SCPRefundReason)reason;

/// @see `SCPConfirmRefundParameters.metadata`
- (SCPConfirmRefundParametersBuilder *)setMetadata:(nullable NSDictionary<NSString *, NSString *> *)metadata;

/// @see `SCPConfirmRefundParameters.reverseTransfer`
- (SCPConfirmRefundParametersBuilder *)setReverseTransfer:(BOOL)reverseTransfer;

/// @see `SCPConfirmRefundParameters.refundApplicationFee`
- (SCPConfirmRefundParametersBuilder *)setRefundApplicationFee:(BOOL)refundApplicationFee;

/// @see `SCPConfirmRefundParameters.instructionsEmail`
- (SCPConfirmRefundParametersBuilder *)setInstructionsEmail:(nullable NSString *)instructionsEmail;

/**
 Use `initWithPaymentIntentId:clientSecret:`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithPaymentIntentId:clientSecret:`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
