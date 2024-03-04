//
//  SCPCollectConfiguration.h
//  StripeTerminal
//
//  Created by Matthew Krager on 2/1/22.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPTippingConfiguration;

/**
 * The `CollectConfiguration` contains configuration information relevant to collecting a payment
 * method.
 */
NS_SWIFT_NAME(CollectConfiguration)
@interface SCPCollectConfiguration : NSObject <NSCopying>

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
 Whether to show a cancel button in transaction UI on Stripe smart readers.

 Defaults to NO.
 */
@property (nonatomic, assign, readonly) BOOL enableCustomerCancellation;

/**
 Request Dynamic Currency Conversion for the presented payment method if available.

 `updatePaymentIntent` must be set to true for dynamic currency conversion to be enabled.

 Defaults to NO.
 */
@property (nonatomic, assign, readonly) BOOL requestDynamicCurrencyConversion;

/**
 Use `SCPCollectConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPCollectConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The `CollectConfigurationBuilder` is used to create a `CollectConfiguration` object.
 */
NS_SWIFT_NAME(CollectConfigurationBuilder)
@interface SCPCollectConfigurationBuilder : SCPBuilder <SCPCollectConfiguration *>

/// Set the skipTipping property for the `CollectConfiguration` object that will be built.
- (SCPCollectConfigurationBuilder *)setSkipTipping:(BOOL)skipTipping;

/// Set the tippingConfiguration property for the `CollectConfiguration` object that will be built.
- (SCPCollectConfigurationBuilder *)setTippingConfiguration:(nullable SCPTippingConfiguration *)tippingConfiguration;

/// Set the updatePaymentIntent property for the `CollectConfiguration` object that will be built.
- (SCPCollectConfigurationBuilder *)setUpdatePaymentIntent:(BOOL)updatePaymentIntent;

/// Set the enableCustomerCancellation property for the `CollectConfiguration` object that will be built.
- (SCPCollectConfigurationBuilder *)setEnableCustomerCancellation:(BOOL)enableCustomerCancellation;

/// Set the enableCustomerCancellation property for the `CollectConfiguration` object that will be built.
- (SCPCollectConfigurationBuilder *)setRequestDynamicCurrencyConversion:(BOOL)requestDynamicCurrencyConversion;

@end

NS_ASSUME_NONNULL_END
