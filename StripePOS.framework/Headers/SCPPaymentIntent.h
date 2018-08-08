//
//  SCPPaymentIntent.h
//  StripePOS
//
//  Created by Ben Guo on 5/2/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SCPJSONDecodable.h"

NS_ASSUME_NONNULL_BEGIN

@class SCPCharge, SCPConfirmError, SCPCardPresentSource;

/**
 The possible statuses for a payment intent.
 */
typedef NS_ENUM(NSUInteger, SCPPaymentIntentStatus) {
    /**
     A source must be attached to the intent by calling attachSource.
     */
    SCPPaymentIntentStatusRequiresSource,
    /**
     The intent must be confirmed by calling confirmPaymentIntent.
     */
    SCPPaymentIntentStatusRequiresConfirmation,
    /**
     confirmPaymentIntent succeeded. You must send the `stripeId` of the
     payment intent your backend, where you can capture it and perform
     additional processing.
     */
    SCPPaymentIntentStatusRequiresCapture,
    /**
     The payment intent was canceled.
     */
    SCPPaymentIntentStatusCanceled,
    /**
     The payment intent succeeded.
     */
    SCPPaymentIntentStatusSucceeded,
};

/**
 A payment intent.
 */
@interface SCPPaymentIntent : NSObject <SCPJSONDecodable>

/**
 The unique identifier for the intent.
 */
@property (nonatomic, readonly) NSString *stripeId;

/**
 When the intent was created.
 */
@property (nonatomic, readonly) NSDate *created;

/**
 The status of the payment intent.
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
 until the payment intent has been successfully confirmed.
 */
@property (nonatomic, nullable, readonly) SCPCardPresentSource *cardPresentSource;

/**
 Set of key-value pairs attached to the object.
 */
@property (nonatomic, nullable, readonly) NSDictionary *metadata;

/**
 Extra information about a payment intent. This will appear on your customer’s
 statement when this intent succeeds in creating a charge.
 */
@property (nonatomic, nullable, readonly) NSString *statementDescriptor;

/**
 An arbitrary string attached to the object. If you send a receipt email for
 this payment, the email will include the description.
 */
@property (nonatomic, nullable, readonly) NSString *stripeDescription;

/**
 Email address that the receipt for the resulting payment will be sent to.
 */
@property (nonatomic, nullable, readonly) NSString *receiptEmail;

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
