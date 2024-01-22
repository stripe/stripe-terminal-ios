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
#import <StripeTerminal/SCPJSONDecodable.h>
#import <StripeTerminal/SCPPaymentIntentParameters.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPCharge, SCPConfirmPaymentIntentError, SCPOfflineDetails, SCPPaymentMethod, SCPAmountDetails, SCPTransferData;

/**
 The possible statuses for a PaymentIntent.

 https://stripe.com/docs/api/payment_intents/object#payment_intent_object-status
 */
typedef NS_ENUM(NSUInteger, SCPPaymentIntentStatus) {
    /**
     Next step: collect a payment method by calling `collectPaymentMethod`.
     */
    SCPPaymentIntentStatusRequiresPaymentMethod,
    /**
     Next step: confirm the payment by calling `confirmPaymentIntent`.
     */
    SCPPaymentIntentStatusRequiresConfirmation,
    /**
     Next step: the payment requires additional actions, such as authenticating with 3D Secure.

     @note PaymentIntents collected with the Terminal SDK should not end in the `requires_action` status.
     You can use the `intent.originalJSON` to review the `next_action`.

     @see https://stripe.com/docs/payments/paymentintents/lifecycle#intent-statuses
     @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-next_action
     */
    SCPPaymentIntentStatusRequiresAction,
    /**
     Next step: capture the PaymentIntent on your backend via the Stripe API.
     */
    SCPPaymentIntentStatusRequiresCapture,
    /**
     The PaymentIntent is in the middle of full EMV processing.
     */
    SCPPaymentIntentStatusProcessing,
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
 A PaymentIntent tracks the process of collecting a payment from your customer.
 We recommend that you create exactly one PaymentIntent for each order or
 customer session in your system. You can reference the PaymentIntent later to
 see the history of payment attempts for a particular session.

 A PaymentIntent transitions through multiple statuses throughout its lifetime
 and ultimately creates at most one successful charge.

 https://stripe.com/docs/api/payment_intents
 */
NS_SWIFT_NAME(PaymentIntent)
@interface SCPPaymentIntent : NSObject <SCPJSONDecodable, NSCopying>

/**
 The unique identifier for the intent.

 When an intent is created offline, the stripeId will be nil. To keep track of
 offline payments, we recommend using the metadata with your own identifiers.

 After the payment has been forwarded the intent's stripeId will
 be filled in.
 */
@property (nonatomic, nullable, readonly, copy) NSString *stripeId;

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
 Controls when the funds will be captured from the customer’s account.
 */
@property (nonatomic, readonly) SCPCaptureMethod captureMethod;

/**
 The currency of the payment.
 */
@property (nonatomic, readonly) NSString *currency;

/**
 Set of key-value pairs attached to the object.

 @see https://stripe.com/docs/api#metadata
 */
@property (nonatomic, nullable, readonly) NSDictionary<NSString *, NSString *> *metadata;

/**
 Charges that were created by this PaymentIntent, if any.
 */
@property (nonatomic, readonly) NSArray<SCPCharge *> *charges;

/**
 The payment method to be used in this PaymentIntent. Only valid in the
 intent returned during `collectPaymentMethod` when using the `updatePaymentIntent`
 option in the `SCPCollectConfiguration`.
 */
@property (nonatomic, nullable, readonly) SCPPaymentMethod *paymentMethod;

/**
 ID of the payment method used in this PaymentIntent.
 */
@property (nonatomic, copy, nullable, readonly) NSString *paymentMethodId;

/**
 Details about items included in the amount after confirmation.
 */
@property (nonatomic, nullable, readonly) SCPAmountDetails *amountDetails;

/**
 Indicates how much the user intends to tip in addition to the amount by at confirmation time.
 This is only non-null in the `PaymentIntent` instance returned during collect when using
 `updatePaymentIntent` set to true in the `CollectConfiguration`.

 After `confirmPaymentIntent` the `amount` will have this tip amount added to it and the
 `amountDetails` will contain the breakdown of how much of the amount was a tip.
 */
@property (nonatomic, nullable, readonly) NSNumber *amountTip;

/**
 Extra information about a PaymentIntent. This will appear on your customer’s statement when
 this PaymentIntent succeeds in creating a charge.
 */
@property (nonatomic, nullable, readonly) NSString *statementDescriptor;

/**
 Extra dynamic information about a PaymentIntent. This will appear concatenated with the statementDescriptor on
 your customer’s statement when this PaymentIntent succeeds in creating a charge.
 */
@property (nonatomic, nullable, readonly) NSString *statementDescriptorSuffix;

/**
 The offline details for this intent, if created or processed while offline.

 When an intent is created offline, the intent.stripeId will be nil. To keep track of
 offline payments, we recommend using the intent.metadata with your own identifiers.

 The `OfflineDetails` `requiresUpload` can be used to
 identify that the intent was processed offline and requires the device to be
 brought back online so the intent can be forwarded.

 @see https://stripe.com/docs/terminal/features/operate-offline/
 */
@property (nonatomic, nullable, readonly) SCPOfflineDetails *offlineDetails;

/**
 The account (if any) for which the funds of the PaymentIntent are intended. See the PaymentIntents [use case
 for connected accounts](https://stripe.com/docs/payments/connected-accounts) for details.
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-on_behalf_of
 */
@property (nonatomic, nullable, readonly) NSString *onBehalfOf;

/**
 The client secret of this PaymentIntent. Used for client-side retrieval using a publishable key.

 The client secret can be used to complete a payment from your frontend. It should not be stored, logged,
 or exposed to anyone other than the customer. Make sure that you have TLS enabled on any page that
 includes the client secret.

 Refer to our docs to [accept a payment](https://stripe.com/docs/payments/accept-a-payment?ui=elements)
 and learn about how `client_secret` should be handled.
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-client_secret
 */
@property (nonatomic, nullable, readonly) NSString *clientSecret;

/**
 Amount that this PaymentIntent collects.
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-amount_received
 */
@property (nonatomic, readonly) NSNumber amountReceived;

/**
 Amount that can be captured from this PaymentIntent.
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-amount_capturable
 */
@property (nonatomic, readonly) NSNumber amountCapturable;

/**
 ID of the Connect application that created the PaymentIntent.
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-application
 */
@property (nonatomic, nullable, readonly) NSString *application;

/**
 The amount of the application fee (if any) that will be requested to be applied to the payment
 and transferred to the application owner’s Stripe account. The amount of the application fee
 collected will be capped at the total payment amount. 
 
 For more information, see the PaymentIntents [use case for connected accounts](https://stripe.com/docs/payments/connected-accounts).
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-application_fee_amount
 */
@property (nonatomic, nullable, readonly) NSNumber *applicationFeeAmount;

/**
 Populated when `status` is `canceled`, this is the time at which the PaymentIntent was canceled.
 Measured in seconds since the Unix epoch.
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-canceled_at
 */
@property (nonatomic, nullable, readonly) NSDate *canceledAt;

/**
 ID of the Customer this PaymentIntent belongs to, if one exists.

 Payment methods attached to other Customers cannot be used with this PaymentIntent.

 If present in combination with [setup_future_usage](https://stripe.com/docs/api/payment_intents/object#payment_intent_object-setup_future_usage),
 this PaymentIntent’s payment method will be attached to the Customer after the PaymentIntent
 has been confirmed and any required actions from the user are complete.
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-customer
 */
@property (nonatomic, nullable, readonly) NSString *customer;

/**
 An arbitrary string attached to the object. Often useful for displaying to users.
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-description
 */
@property (nonatomic, nullable, readonly) NSString *description;

/**
 The latest charge created by this PaymentIntent.
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-latest_charge
 */
@property (nonatomic, nullable, readonly) NSString *latestCharge;

/**
 Email address that the receipt for the resulting payment will be sent to. If `receipt_email`
 is specified for a payment in live mode, a receipt will be sent regardless of your [email settings](https://dashboard.stripe.com/account/emails).
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-receipt_email
 */
@property (nonatomic, nullable, readonly) NSString *receiptEmail;

/**
 String representing the object’s type. Objects of the same type share the same value.
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-object
 */
@property (nonatomic, readonly) NSString object;

/**
 ID of the invoice that created this PaymentIntent, if it exists.
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-invoice
 */
@property (nonatomic, nullable, readonly) NSString *invoice;

/**
 The data that automatically creates a Transfer after the payment finalizes.
 
 Learn more about the [use case for connected accounts](https://stripe.com/docs/payments/connected-accounts).
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-transfer_data
 */
@property (nonatomic, nullable, readonly) SCPTransferData *transferData;

/**
 A string that identifies the resulting payment as part of a group. Learn more about the [use case for 
 connected accounts](https://stripe.com/docs/payments/connected-accounts).
 
 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-transfer_group
 */
@property (nonatomic, nullable, readonly) NSString *transferGroup;

/**
 You cannot directly instantiate `SCPPaymentIntent`. You should only use
 one that has been returned by our SDK.

 @see SCPTerminal.shared.createPaymentIntent()
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPPaymentIntent`. You should only use
 one that has been returned by our SDK.

 @see SCPTerminal.shared.createPaymentIntent()
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
