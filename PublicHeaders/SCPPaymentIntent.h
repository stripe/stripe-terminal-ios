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
#import <StripeTerminal/SCPPaymentIntentParameters.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPCharge, SCPConfirmPaymentIntentError, SCPOfflineDetails, SCPPaymentMethod, SCPAmountDetails, SCPNextAction, SCPApiError;

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
@interface SCPPaymentIntent : NSObject <NSCopying>

/**
 The amount to be collected by this PaymentIntent, provided in the currency's
 smallest unit.

 @see https://stripe.com/docs/currencies#zero-decimal
 */
@property (nonatomic, readonly) NSUInteger amount;

/**
 Amount that can be captured for this PaymentIntent.
 */
@property (nonatomic, nullable, readonly) NSNumber *amountCapturable;

/**
 Details about items included in the amount after confirmation.
 */
@property (nonatomic, nullable, readonly) SCPAmountDetails *amountDetails;

/**
 Amount that was received for this PaymentIntent.
 */
@property (nonatomic, nullable, readonly) NSNumber *amountReceived;

/**
 The originally specified request amount if the transaction was partially authorized
*/
@property (nonatomic, nullable, readonly) NSNumber *amountRequested;

/**
 Surcharge amount to apply on top of the purchase amount.
 */
@property (nonatomic, nullable, readonly) NSNumber *amountSurcharge;

/**
 Indicates how much the user intends to tip in addition to the amount by at confirmation time.
 This is only non-null in the `PaymentIntent` instance returned during collect when using
 `updatePaymentIntent` set to true in the `CollectConfiguration`.

 After `confirmPaymentIntent` the `amount` will have this tip amount added to it and the
 `amountDetails` will contain the breakdown of how much of the amount was a tip.
 */
@property (nonatomic, nullable, readonly) NSNumber *amountTip;

/**
 The amount of the application fee (if any) for the resulting payment.
 */
@property (nonatomic, nullable, readonly) NSNumber *applicationFeeAmount;

/**
 Time at which the PaymentIntent was canceled, if it was canceled.
 */
@property (nonatomic, nullable, readonly) NSDate *canceledAt;

/**
 Reason for cancellation of this PaymentIntent.
 */
@property (nonatomic, nullable, readonly) NSString *cancellationReason;

/**
 Controls when the funds will be captured from the customer's account.
 */
@property (nonatomic, readonly) SCPCaptureMethod captureMethod;

/**
 Charges that were created by this PaymentIntent, if any.
 */
@property (nonatomic, readonly) NSArray<SCPCharge *> *charges;

/**
 The client secret for this intent.
 */
@property (nonatomic, nullable, readonly) NSString *clientSecret;

/**
 The confirmation method for this PaymentIntent ("automatic" or "manual").
 */
@property (nonatomic, nullable, readonly) NSString *confirmationMethod;

/**
 When the intent was created.
 */
@property (nonatomic, readonly) NSDate *created;

/**
 The currency of the payment.
 */
@property (nonatomic, readonly) NSString *currency;

/**
 ID of the Customer this PaymentIntent belongs to, if one exists.
 */
@property (nonatomic, nullable, readonly) NSString *customer;

/**
 Last payment error on a charge, if any.
 */
@property (nonatomic, nullable, readonly) SCPApiError *lastPaymentError;

/**
 Whether this PaymentIntent was created in live mode or test mode.
 */
@property (nonatomic, readonly) BOOL livemode;

/**
 Set of key-value pairs attached to the object.

 @see https://stripe.com/docs/api#metadata
 */
@property (nonatomic, nullable, readonly) NSDictionary<NSString *, NSString *> *metadata;

/**
 If present, this property tells you what actions you need to take for your customer to continue payment.
 */
@property (nonatomic, nullable, readonly) SCPNextAction *nextAction;

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
 The account (if any) for which the payment is intended.
 */
@property (nonatomic, nullable, readonly) NSString *onBehalfOf;

/**
 The payment method to be used in this PaymentIntent. Only valid in the
 intent returned during `collectPaymentMethod` when using the `updatePaymentIntent`
 option in the `SCPCollectPaymentIntentConfiguration`.
 */
@property (nonatomic, nullable, readonly) SCPPaymentMethod *paymentMethod;

/**
 ID of the payment method used in this PaymentIntent.
 */
@property (nonatomic, copy, nullable, readonly) NSString *paymentMethodId;

/**
 Payment-method-specific configuration for this PaymentIntent.
 */
@property (nonatomic, nullable, readonly) SCPPaymentMethodOptionsParameters *paymentMethodOptions;

/**
 The list of payment method types that this PaymentIntent can use.
 These are NSNumber's where the value is in `SCPPaymentMethodType`.
 */
@property (nonatomic, nullable, readonly) NSArray<NSNumber *> *paymentMethodTypes;

/**
 Email address that the receipt for the resulting payment will be sent to.
 */
@property (nonatomic, nullable, readonly) NSString *receiptEmail;

/**
 Indicates that you intend to make future payments with this PaymentIntent's payment method.

 Providing this parameter will attach the payment method to the PaymentIntent's Customer, if present, after the PaymentIntent is confirmed and any required actions from the user are complete. If no Customer was provided, the payment method can still be attached to a Customer after the transaction completes.

 When processing card payments, Stripe also uses setup_future_usage to dynamically optimize your payment flow and comply with regional legislation and network rules, such as SCA.
 */
@property (nonatomic, nullable, readonly) NSString *setupFutureUsage;

/**
 Extra information about a PaymentIntent. This will appear on your customer's statement when
 this PaymentIntent succeeds in creating a charge.
 */
@property (nonatomic, nullable, readonly) NSString *statementDescriptor;

/**
 Extra dynamic information about a PaymentIntent. This will appear concatenated with the statementDescriptor on
 your customer's statement when this PaymentIntent succeeds in creating a charge.
 */
@property (nonatomic, nullable, readonly) NSString *statementDescriptorSuffix;

/**
 The status of the PaymentIntent.
 */
@property (nonatomic, readonly) SCPPaymentIntentStatus status;

/**
 An arbitrary string attached to the object. Often useful for displaying to users.
 */
@property (nonatomic, nullable, readonly) NSString *stripeDescription;

/**
 The unique identifier for the intent.

 When an intent is created offline, the stripeId will be nil. To keep track of
 offline payments, we recommend using the metadata with your own identifiers.

 After the payment has been forwarded the intent's stripeId will
 be filled in.
 */
@property (nonatomic, nullable, readonly, copy) NSString *stripeId;

/**
 A string that identifies this PaymentIntent as part of a group.
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
