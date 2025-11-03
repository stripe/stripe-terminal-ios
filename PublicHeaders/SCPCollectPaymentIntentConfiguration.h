//
//  SCPCollectPaymentIntentConfiguration.h
//  StripeTerminal
//
//  Created by Matthew Krager on 2/1/22.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPAllowRedisplay.h>
#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPCustomerCancellation.h>
#import <StripeTerminal/SCPMotoConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPTippingConfiguration;

/**
 * The `CollectPaymentIntentConfiguration` contains configuration information relevant to collecting a payment
 * method.
 */
NS_SWIFT_NAME(CollectPaymentIntentConfiguration)
@interface SCPCollectPaymentIntentConfiguration : NSObject <NSCopying>

/**
 Bypass tipping selection if it would have otherwise been shown.

 Defaults to NO.

 @see https://stripe.com/docs/terminal/features/collecting-tips/on-reader
*/
@property (nonatomic, assign, readonly) BOOL skipTipping;

/**
 The tipping configuration for this payment collection.

 @see https://stripe.com/docs/terminal/features/collecting-tips/on-reader#tip-eligible
 */
@property (nonatomic, strong, nullable, readonly) SCPTippingConfiguration *tippingConfiguration;

/**
 Whether or not to update the PaymentIntent server side during `collectPaymentMethod`.

 Attempting to collect with `updatePaymentIntent` enabled and a PaymentIntent created while offline
 will error with `SCPErrorUpdatePaymentIntentUnavailableWhileOffline`.

 Defaults to NO.
 */
@property (nonatomic, assign, readonly) BOOL updatePaymentIntent;

/**
 Controls whether customer-initiated cancellation is enabled during payment collection.

 Defaults to SCPCustomerCancellationEnableIfAvailable.
 */
@property (nonatomic, assign, readonly) SCPCustomerCancellation customerCancellation;

/**
 Request Dynamic Currency Conversion for the presented payment method if available.

 `updatePaymentIntent` must be set to true for dynamic currency conversion to be enabled.

 Defaults to NO.
 */
@property (nonatomic, assign, readonly) BOOL requestDynamicCurrencyConversion;

/**
 Display a notice on the reader collection screen to inform cardholders about surcharging on a transaction

 `updatePaymentIntent` must be set to true for to display a surcharge notice

 Defaults to nil.
 */
@property (nonatomic, strong, nullable, readonly) NSString *surchargeNotice;

/**
 Obtain customer consent to save payment method details and set this field to reflect accordingly whether this payment method can be shown again to its customer in a checkout flow.

 `allowRedisplay` must be set to `always` or `limited` if `setup_future_usage` is used

 Defaults to `SCPAllowRedisplayUnspecified`
 */
@property (nonatomic, assign, readonly) SCPAllowRedisplay allowRedisplay;

/**
 Collect and process the payment as a Mail Order/Telephone Order payment on Stripe smart readers. Contact Stripe support to enable this feature on your account.

 @see https://docs.stripe.com/terminal/features/mail-telephone-orders/overview
 */
@property (nonatomic, strong, nullable, readonly) SCPMotoConfiguration *motoConfiguration;

/**
 Use `SCPCollectPaymentIntentConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPCollectPaymentIntentConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The `CollectPaymentIntentConfigurationBuilder` is used to create a `CollectPaymentIntentConfiguration` object.
 */
NS_SWIFT_NAME(CollectPaymentIntentConfigurationBuilder)
@interface SCPCollectPaymentIntentConfigurationBuilder : SCPBuilder <SCPCollectPaymentIntentConfiguration *>

/// Set the skipTipping property for the `CollectPaymentIntentConfiguration` object that will be built.
- (SCPCollectPaymentIntentConfigurationBuilder *)setSkipTipping:(BOOL)skipTipping;

/// Set the tippingConfiguration property for the `CollectPaymentIntentConfiguration` object that will be built.
- (SCPCollectPaymentIntentConfigurationBuilder *)setTippingConfiguration:(nullable SCPTippingConfiguration *)tippingConfiguration;

/// Set the updatePaymentIntent property for the `CollectPaymentIntentConfiguration` object that will be built.
- (SCPCollectPaymentIntentConfigurationBuilder *)setUpdatePaymentIntent:(BOOL)updatePaymentIntent;

/// Set the customerCancellation property for the `CollectPaymentIntentConfiguration` object that will be built.
- (SCPCollectPaymentIntentConfigurationBuilder *)setCustomerCancellation:(SCPCustomerCancellation)customerCancellation;

/// Set the enableCustomerCancellation property for the `CollectPaymentIntentConfiguration` object that will be built.
- (SCPCollectPaymentIntentConfigurationBuilder *)setRequestDynamicCurrencyConversion:(BOOL)requestDynamicCurrencyConversion;

/// Set the surchargeNotice property for the `CollectPaymentIntentConfiguration` object that will be built.
- (SCPCollectPaymentIntentConfigurationBuilder *)setSurchargeNotice:(nullable NSString *)surchargeNotice;

/// Set the allowRedisplay property for the `CollectPaymentIntentConfiguration` object that will be built.
- (SCPCollectPaymentIntentConfigurationBuilder *)setAllowRedisplay:(SCPAllowRedisplay)allowRedisplay;

/// Set the motoConfiguration property for the `CollectPaymentIntentConfiguration` object that will be built.
- (SCPCollectPaymentIntentConfigurationBuilder *)setMotoConfiguration:(nullable SCPMotoConfiguration *)motoConfiguration;

@end

NS_ASSUME_NONNULL_END
