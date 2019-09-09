//
//  SCPPaymentIntentParameters.h
//  StripeTerminal
//
//  Created by Ben Guo on 8/2/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Parameters for creating an `SCPPaymentIntent`.

 @see https://stripe.com/docs/api/payment_intents/create
 */
NS_SWIFT_NAME(PaymentIntentParameters)
@interface SCPPaymentIntentParameters : NSObject

/**
 The amount of the payment, provided in the currency's smallest unit.
 */
@property (nonatomic, readonly) NSUInteger amount;

/**
 Three-letter ISO currency code, in lowercase. Must be a supported currency.
 */
@property (nonatomic, readonly) NSString *currency;

/**
 Set of key-value pairs that you can attach to an object. This can be useful for
 storing additional information about the object in a structured format.
 */
@property (nonatomic, copy, nullable, readwrite) NSDictionary *metadata;

/**
 An arbitrary string attached to the object. If you send a receipt email for
 this payment, the email will include the description.
 */
@property (nonatomic, copy, nullable, readwrite) NSString *stripeDescription;

/**
 A string to be displayed on your customer's credit card statement. This may be
 up to 22 characters. The statement descriptor must contain at least one letter,
 may not include `<>"'` characters, and will appear on your customer's statement
 in capital letters. Non-ASCII characters are automatically stripped. While
 most banks and card issuers display this information consistently, some may
 display it incorrectly or not at all.
 */
@property (nonatomic, copy, nullable, readwrite) NSString *statementDescriptor;

/**
 Email address that the receipt for the resulting payment will be sent to.

 @see https://stripe.com/docs/terminal/checkout/receipts
 */
@property (nonatomic, copy, nullable, readwrite) NSString *receiptEmail;

/**
 The ID of the Customer this PaymentIntent is for, if one exists.

 @see https://stripe.com/docs/api/customers
 */
@property (nonatomic, copy, nullable, readwrite) NSString *customer;

/**
 The amount of the application fee (if any) that will be applied to the
 payment and transferred to the application owner’s Stripe account. To use an
 application fee, the request must be made on behalf of another account,
 using the stripeAccount property or an OAuth key.

 The amount must be provided as a boxed UInt in the currency's smallest unit.

 @see https://stripe.com/docs/connect/direct-charges#collecting-fees
 */
@property (nonatomic, copy, nullable, readwrite) NSNumber *applicationFeeAmount;

/**
 A string that identifies the resulting payment as part of a group.

 @see https://stripe.com/docs/connect/charges-transfers#grouping-transactions
 */
@property (nonatomic, copy, nullable, readwrite) NSString *transferGroup;

/**
 The account (if any) the payment will be attributed to for tax reporting, and
 where funds from the payment will be transferred to upon payment success.

 At capture time, use `transfer_data[amount]` to specify the amount that will be
 transferred automatically when a charge succeeds.

 When `transferDataDestination` is specified, `onBehalfOf` must also be
 specified and must match the destination of the transfer.
 */
@property (nonatomic, copy, nullable, readwrite) NSString *transferDataDestination;

/**
 The Stripe account ID for which these funds are intended.

 When `transferDataDestination` is specified, `onBehalfOf` must also be
 specified and must match the destination of the transfer.

 @see https://stripe.com/docs/connect/charges-transfers#on-behalf-of
 */
@property (nonatomic, copy, nullable, readwrite) NSString *onBehalfOf;

/**
 Initializes SCPPaymentIntentParameters with the given parameters.

 @param amount      The amount of the payment, provided in the currency's
 smallest unit.

 Note: in testmode, only amounts ending in "00" will be approved. All other
 amounts will be declined by the Stripe API. For more information about this
 feature, see https://stripe.com/docs/terminal/testing#test-card

 @param currency    The currency of the payment.
 */
- (instancetype)initWithAmount:(NSUInteger)amount
                      currency:(NSString *)currency;

/**
 Use `initWithAmount:currency:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithAmount:currency:`
 */
- (instancetype)new NS_UNAVAILABLE;

/**
 Use stripeDescription for the string attached to the object.
 */
@property (nonatomic, copy, readonly) NSString *description DEPRECATED_MSG_ATTRIBUTE("Did you mean to use stripeDescription?");

@end

NS_ASSUME_NONNULL_END
