//
//  SCPConfirmPaymentIntentConfiguration.h
//  StripeTerminal
//
//  Created by Stanley Lin on 5/28/24.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPSurchargeConfiguration.h>
NS_ASSUME_NONNULL_BEGIN

/**
 * The `ConfirmPaymentIntentConfiguration` contains configuration information relevant to confirming a payment
 * intent.
 */
NS_SWIFT_NAME(ConfirmPaymentIntentConfiguration)
@interface SCPConfirmPaymentIntentConfiguration : NSObject <NSCopying>

/**
 The URL to redirect your customer back to after they authenticate or cancel their payment on the payment method's app or site.
 If you'd prefer to redirect to a mobile application, you can alternatively supply an application URI scheme.

 This parameter is only used for redirect-based payment methods.

 Defaults to nil.
 */
@property (nonatomic, strong, nullable, readonly) NSString *returnUrl;

/**
 Configuration for surcharge collection during payment confirmation.

 Defaults to nil.
 */
@property (nonatomic, strong, nullable, readonly) SCPSurchargeConfiguration *surcharge;

/**
 Use `SCPConfirmPaymentIntentConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPConfirmPaymentIntentConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The `ConfirmPaymentIntentConfigurationBuilder` is used to create a `ConfirmPaymentIntentConfiguration` object.
 */
NS_SWIFT_NAME(ConfirmPaymentIntentConfigurationBuilder)
@interface SCPConfirmPaymentIntentConfigurationBuilder : SCPBuilder <SCPConfirmPaymentIntentConfiguration *>

/// Set the returnUrl property for the `ConfirmPaymentIntentConfiguration` object that will be built.
- (SCPConfirmPaymentIntentConfigurationBuilder *)setReturnUrl:(NSString *)returnUrl;

/// Set the surchargeConfiguration property for the `ConfirmPaymentIntentConfiguration` object that will be built.
- (SCPConfirmPaymentIntentConfigurationBuilder *)setSurchargeConfiguration:(SCPSurchargeConfiguration *)surchargeConfiguration;

@end

NS_ASSUME_NONNULL_END
