//
//  SCPCharge.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/27/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import "SCPJSONDecodable.h"

NS_ASSUME_NONNULL_BEGIN

/**
 The possible statuses for a charge
 */
typedef NS_ENUM(NSUInteger, SCPChargeStatus) {
    /**
     The charge succeeded.
     */
    SCPChargeStatusSucceeded,
    /**
     The charge succeeded.
     */
    SCPChargeStatusPending,
    /**
     The charge failed.
     */
    SCPChargeStatusFailed,
} NS_SWIFT_NAME(ChargeStatus);

@class SCPPaymentMethodDetails;

/**
 An object representing a Stripe charge.

 @see https://stripe.com/docs/api#charges
 */
@interface SCPCharge : NSObject <SCPJSONDecodable>

/**
 The amount of the charge.
 */
@property (nonatomic, readonly) NSUInteger amount;

/**
 The currency of the charge.
 */
@property (nonatomic, readonly) NSString *currency;

/**
 The status of the charge.
 */
@property (nonatomic, readonly) SCPChargeStatus status;

/**
 The payment method details associated with the charge.
 */
@property (nonatomic, nullable, readonly) SCPPaymentMethodDetails *paymentMethodDetails;

/**
 A string describing the charge, displayed in the Stripe dashboard and in
 email receipts.
 */
@property (nonatomic, nullable, readonly) NSString *stripeDescription;

/**
 Metadata associated with the charge.
 */
@property (nonatomic, readonly) NSDictionary *metadata;

/**
 The unique identifier for the charge.
 */
@property (nonatomic, readonly) NSString *stripeId;

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
