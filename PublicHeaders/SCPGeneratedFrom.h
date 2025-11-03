//
//  SCPGeneratedFrom.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2025-08-29.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPPaymentMethodDetails;

/**
 Contains details of the original PaymentMethod that created this CardDetails object.

 @see https://stripe.com/docs/api/payment_methods/object#payment_method_object-card-generated_from
 */
NS_SWIFT_NAME(GeneratedFrom)
@interface SCPGeneratedFrom : NSObject <NSCopying>

/**
 The charge that created this object.
 */
@property (nonatomic, nullable, readonly) NSString *charge;

/**
 Transaction-specific details of the payment method used in the payment.
 */
@property (nonatomic, nullable, readonly) SCPPaymentMethodDetails *paymentMethodDetails;

/**
 The ID of the SetupAttempt that generated this PaymentMethod, if any.
 */
@property (nonatomic, nullable, readonly) NSString *setupAttempt;

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
