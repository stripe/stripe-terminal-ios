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
#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPTippingConfiguration;

/**
 * The `CollectConfiguration` contains configuration information relevant to collecting a payment
 * method.
 */
NS_SWIFT_NAME(CollectConfiguration)
@interface SCPCollectConfiguration : NSObject

/**
 Bypass tipping selection if it would have otherwise been shown.

 Defaults to NO.

 @see https://stripe.com/docs/terminal/features/collecting-tips/on-reader
*/
@property (nonatomic, assign) BOOL skipTipping;

/**
 The tipping configuration for this payment collection.

 @see https://stripe.com/docs/terminal/features/collecting-tips/on-reader#tip-eligible
 */
@property (nonatomic, strong, nullable) SCPTippingConfiguration *tippingConfiguration;

/**
 Whether or not to update the PaymentIntent server side during `collectPaymentMethod`.

 Defaults to NO.
 */
@property (nonatomic, assign) BOOL updatePaymentIntent;

/**
 Initialize a CollectConfiguration

 @param skipTipping Bypass tipping selection if it would have otherwise been shown.
 */
- (instancetype)initWithSkipTipping:(BOOL)skipTipping;

/**
 Initialize a CollectConfiguration

 @param updatePaymentIntent Whether or not to update the PaymentIntent server side during `collectPaymentMethod`.
 */
- (instancetype)initWithUpdatePaymentIntent:(BOOL)updatePaymentIntent;

/**
 Initialize a CollectConfiguration.

 @param tippingConfiguration Tipping configuration for the payment method collection.
 */
- (instancetype)initWithTippingConfiguration:(SCPTippingConfiguration *)tippingConfiguration;

/**
 Initialize a CollectConfiguration

 @param skipTipping Bypass tipping selection if it would have otherwise been shown.
 @param updatePaymentIntent Whether or not to update the PaymentIntent server side during `collectPaymentMethod`.
 */
- (instancetype)initWithSkipTipping:(BOOL)skipTipping
                updatePaymentIntent:(BOOL)updatePaymentIntent;

/**
 Initialize a CollectConfiguration.

 @param skipTipping Bypass tipping selection if it would have otherwise been shown.
 @param tippingConfiguration Tipping configuration for the payment method collection.
 */
- (instancetype)initWithSkipTipping:(BOOL)skipTipping
               tippingConfiguration:(nullable SCPTippingConfiguration *)tippingConfiguration;

/**
 Initialize a CollectConfiguration.

 @param updatePaymentIntent Whether or not to update the PaymentIntent server side during `collectPaymentMethod`.
 @param tippingConfiguration Tipping configuration for the payment method collection.
 */
- (instancetype)initWithUpdatePaymentIntent:(BOOL)updatePaymentIntent
                       tippingConfiguration:(nullable SCPTippingConfiguration *)tippingConfiguration;

/**
 Initialize a CollectConfiguration.

 @param skipTipping Bypass tipping selection if it would have otherwise been shown.
 @param updatePaymentIntent Whether or not to update the PaymentIntent server side during `collectPaymentMethod`.
 @param tippingConfiguration Tipping configuration for the payment method collection.
 */
- (instancetype)initWithSkipTipping:(BOOL)skipTipping
                updatePaymentIntent:(BOOL)updatePaymentIntent
               tippingConfiguration:(nullable SCPTippingConfiguration *)tippingConfiguration NS_DESIGNATED_INITIALIZER;

/**
 Use `initWithSkipTipping:updatePaymentIntent:tippingConfiguration:` or helper initializers.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithSkipTipping:updatePaymentIntent:tippingConfiguration:` or helper initializers.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
