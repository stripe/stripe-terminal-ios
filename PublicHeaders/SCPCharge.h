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
#import <Foundation/Foundation.h>

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
@class SCPGeneratedFrom;

/**
 An object representing a Stripe charge.

 @see https://stripe.com/docs/api#charges
 */
NS_SWIFT_NAME(Charge)
@interface SCPCharge : NSObject

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
 Amount in cents refunded (can be less than the amount attribute on the charge if a partial refund was issued).
 */
@property (nonatomic, readonly) NSUInteger amountRefunded;

/**
 Time at which the object was created. Measured in seconds since the Unix epoch.
 */
@property (nonatomic, nullable, readonly) NSDate *created;

/**
 Whether the charge has been captured.
 */
@property (nonatomic, readonly) BOOL captured;

/**
 Whether the charge succeeded.
 */
@property (nonatomic, readonly) BOOL paid;

/**
 Whether the charge has been fully refunded. If the charge is only partially refunded, this attribute will still be false.
 */
@property (nonatomic, readonly) BOOL refunded;

/**
 ID of the customer this charge is for if one exists.
 */
@property (nonatomic, nullable, readonly) NSString *customer;

/**
 ID of the PaymentIntent associated with this charge, if one exists.
 */
@property (nonatomic, nullable, readonly) NSString *paymentIntentId;

/**
 This is the email address that the receipt for this charge was sent to.
 */
@property (nonatomic, nullable, readonly) NSString *receiptEmail;

/**
 This is the transaction number that appears on email receipts sent for this charge.
 */
@property (nonatomic, nullable, readonly) NSString *receiptNumber;

/**
 This is the URL to view the receipt for this charge.
 */
@property (nonatomic, nullable, readonly) NSString *receiptUrl;

/**
 ID of the balance transaction that describes the impact of this charge on your account balance.
 */
@property (nonatomic, nullable, readonly) NSString *balanceTransaction;

/**
 The application fee (if any) for the charge.
 */
@property (nonatomic, nullable, readonly) NSString *applicationFee;

/**
 The amount of the application fee (if any) requested for the charge.
 */
@property (nonatomic, nullable, readonly) NSNumber *applicationFeeAmount;

/**
 The account (if any) the charge was made on behalf of without triggering an automatic transfer.
 */
@property (nonatomic, nullable, readonly) NSString *onBehalfOf;

/**
 Whether the charge was created in live mode or test mode.
 */
@property (nonatomic, readonly) BOOL livemode;

/**
 Details of the original PaymentMethod that created this object.
 */
@property (nonatomic, nullable, readonly) SCPGeneratedFrom *generatedFrom;

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
