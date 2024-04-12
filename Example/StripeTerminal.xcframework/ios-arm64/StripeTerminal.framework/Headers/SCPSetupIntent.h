//
//  SCPSetupIntent.h
//  StripeTerminal
//
//  Created by James Little on 10/13/20.
//  Copyright © 2020 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPSetupAttempt;

/**
 The possible statuses of the SetupIntent.

 @see https://stripe.com/docs/api/setup_intents/object#setup_intent_object-status
*/
typedef NS_ENUM(NSUInteger, SCPSetupIntentStatus) {
    /**
     Next step: collect a payment method by calling `collectPaymentMethod`.
     */
    SCPSetupIntentStatusRequiresPaymentMethod,

    /**
     Next step: confirm the SetupIntent by calling `confirmSetupIntent`.
     */
    SCPSetupIntentStatusRequiresConfirmation,

    /**
     If the setup requires additional actions, such as authenticating with
     3D Secure, the SetupIntent has a status of requires_action.
     */
    SCPSetupIntentStatusRequiresAction,

    /**
     Once required actions are handled, the SetupIntent moves to processing.
     While for certain payment methods (e.g., cards) processing can be quick,
     other payment methods can take up to a few days to process.
     */
    SCPSetupIntentStatusProcessing,

    /**
     The SetupIntent was canceled.
     */
    SCPSetupIntentStatusCanceled,

    /**
     The SetupIntent succeeded.
     */
    SCPSetupIntentStatusSucceeded
} NS_SWIFT_NAME(SetupIntentStatus);

/**
 The SetupIntent usage options tell Stripe how the payment method is intended to be used in the future.
 Stripe will use the chosen option to pick the most frictionless flow for the customer.

 @see https://stripe.com/docs/payments/setup-intents#increasing-success-rate-by-specifying-usage
 */
typedef NS_ENUM(NSUInteger, SCPSetupIntentUsage) {
    /**
     An off-session usage indicates to Stripe that future payments will take place
     without the direct involvement of the customer. Creating an off-session SetupIntent
     might incur some initial friction from additional authentication steps,
     but can reduce customer intervention in later off-session payments.
     */
    SCPSetupIntentUsageOffSession,

    /**
     An on-session usage indicates to Stripe that future payments will take place
     while the customer is actively in your checkout flow and able to authenticate
     the payment method. With the on-session option, you can postpone authenticating
     the card details until a future checkout to avoid upfront friction.
     */
    SCPSetupIntentUsageOnSession
} NS_SWIFT_NAME(SetupIntentUsage);

/**
 A SetupIntent guides you through the process of setting up and saving a
 customer's payment credentials for future payments. For example, you could use
 a SetupIntent to set up and save your customer's card without immediately
 collecting a payment. Later, you can use PaymentIntents to drive the payment flow.

 @see https://stripe.com/docs/api/setup_intents
 */
NS_SWIFT_NAME(SetupIntent)
@interface SCPSetupIntent : NSObject <SCPJSONDecodable, NSCopying>

/**
 The unique identifier for the intent.
 */
@property (nonatomic, readonly) NSString *stripeId;

/**
 When the intent was created.
 */
@property (nonatomic, readonly) NSDate *created;

/**
 The identifier of a customer object to which the SetupIntent is attached, if applicable.
 */
@property (nonatomic, nullable, readonly) NSString *customer;

/**
 Set of key-value pairs attached to the object.

 @see https://stripe.com/docs/api#metadata
*/
@property (nonatomic, nullable, readonly) NSDictionary<NSString *, NSString *> *metadata;

/**
 An SCPSetupIntentUsage value describing how the SetupIntent will be used.
 Defaults to off-session if not set.
 */
@property (nonatomic, readonly) SCPSetupIntentUsage usage;

/**
 The status of the intent.
 */
@property (nonatomic, readonly) SCPSetupIntentStatus status;

/**
 The most recent SetupAttempt for this SetupIntent
 */
@property (nonatomic, nullable, readonly) SCPSetupAttempt *latestAttempt;

/**
 The list of payment method types that this SetupIntent is allowed to use.
 */
@property (nonatomic, readonly) NSArray<NSString *> *paymentMethodTypes;

/**
 You cannot directly instantiate this class. You should only use SetupIntents
 that have been returned by other methods in our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class. You should only use SetupIntents
 that have been returned by other methods in our SDK.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
