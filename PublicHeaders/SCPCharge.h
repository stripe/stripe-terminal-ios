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

#import <StripeTerminal/SCPJSONDecodable.h>

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
NS_SWIFT_NAME(Charge)
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

 @see https://stripe.com/docs/api#metadata
 */
@property (nonatomic, readonly) NSDictionary<NSString *, NSString *> *metadata;

/**
 The unique identifier for the charge.
 */
@property (nonatomic, readonly) NSString *stripeId;

/**
 Extra dynamic information about a Charge. This will appear concatenated with the statementDescriptor on
 your customer's credit card’s statement.
 */
@property (nonatomic, nullable, readonly) NSString *statementDescriptorSuffix;

/**
 The full statement descriptor that is displayed on your customer's credit card's statement, after the
 static statementDescriptor and dynamic statementDescriptorSuffix portions are combined.
 */
@property (nonatomic, nullable, readonly) NSString *calculatedStatementDescriptor;

/**
 6 digit authorization code for this charge.
 */
@property (nonatomic, nullable, readonly) NSString *authorizationCode;

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
