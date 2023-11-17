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

@class SCPCharge, SCPConfirmPaymentIntentError, SCPOfflineDetails, SCPPaymentMethod, SCPAmountDetails;

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
