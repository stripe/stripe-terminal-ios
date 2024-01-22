//
//  SCPTransferData.h
//  StripeTerminal
//
//  Created by Jermaine Oppong on 19/01/2024.
//  Copyright (c) 2024 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The data that automatically creates a Transfer after the payment finalizes.
 
 Learn more about the [use case for connected accounts](https://stripe.com/docs/payments/connected-accounts).
 */
@interface SCPTransferData : NSObject <SCPJSONDecodable, NSCopying>

/**
 Amount intended to be collected by this PaymentIntent. A positive integer representing
 how much to charge in the [smallest currency unit](https://stripe.com/docs/currencies#zero-decimal)
 (e.g., 100 cents to charge $1.00 or 100 to charge ¥100, a zero-decimal currency). The minimum amount is $0.50 US or [equivalent
 in charge currency](https://stripe.com/docs/currencies#minimum-and-maximum-charge-amounts).
 The amount value supports up to eight digits (e.g., a value of 99999999 for a USD charge of $999,999.99).

 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-transfer_data-amount
 */
@property (nonatomic, nullable, readonly) NSNumber *amount;

/**
 The account (if any) that the payment is attributed to for tax reporting, and where funds from
 the payment are transferred to after payment success.

 https://stripe.com/docs/api/payment_intents/object#payment_intent_object-transfer_destination
 */
@property (nonatomic, readonly) NSString destination;

/**
 You cannot directly instantiate `SCPTransferData`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPTransferData`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
