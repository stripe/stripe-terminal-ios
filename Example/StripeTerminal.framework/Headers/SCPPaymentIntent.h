//
//  SCPPaymentIntent.h
//  StripeTerminal
//
//  Created by Ben Guo on 5/2/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import "SCPJSONDecodable.h"

NS_ASSUME_NONNULL_BEGIN

@class SCPCharge, SCPConfirmError, SCPCardPresentSource;

/**
 The possible statuses for a PaymentIntent.
 */
typedef NS_ENUM(NSUInteger, SCPPaymentIntentStatus) {
    /**
     Next step: collect a payment method for the PaymentMethod by calling
     collectPaymentMethod.
     */
    SCPPaymentIntentStatusRequiresSource,
    /**
     Next step: confirm the PaymentIntent by calling confirmPaymentIntent.
     */
    SCPPaymentIntentStatusRequiresConfirmation,
    /**
     Next step: capture the PaymentIntent on your backend.
     */
    SCPPaymentIntentStatusRequiresCapture,
    /**
     The PaymentIntent was canceled.
     */
    SCPPaymentIntentStatusCanceled,
    /**
     The PaymentIntent succeeded.
     */
    SCPPaymentIntentStatusSucceeded,
} NS_SWIFT_NAME(PaymentIntentStatus);

/**
 A PaymentIntent is an object that represents your intent to collect payment
 from a customer, tracking the lifecycle of the payment process through each
 step. Each PaymentIntent typically correlates with a single “cart” or customer
 session in your application.
 */
NS_SWIFT_NAME(PaymentIntent)
@interface SCPPaymentIntent : NSObject <SCPJSONDecodable, NSCopying>

/**
 The unique identifier for the intent.
 */
@property (nonatomic, readonly) NSString *stripeId;

/**
 When the intent was created.
 */
@property (nonatomic, readonly) NSDate *created;

/**
 The status of the PaymentIntent.
 */
@property (nonatomic, readonly) SCPPaymentIntentStatus status;

/**
 The amount to be collected by this PaymentIntent, provided in the currency's
 smallest unit.
 @see https://stripe.com/docs/currencies#zero-decimal
 */
@property (nonatomic, readonly) NSUInteger amount;

/**
 The currency of the payment.
 */
@property (nonatomic, readonly) NSString *currency;

/**
 The card present source associated with the charge. This value will be nil
 until the PaymentIntent has been successfully confirmed.
 */
@property (nonatomic, nullable, readonly) SCPCardPresentSource *cardPresentSource;

/**
 Set of key-value pairs attached to the object.
 */
@property (nonatomic, nullable, readonly) NSDictionary *metadata;

/**
 Charges that were created by this PaymentIntent, if any.
 */
@property (nonatomic, readonly) NSArray<SCPCharge *> *charges;

/**
 You cannot directly instantiate `SCPPaymentIntent`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPPaymentIntent`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
