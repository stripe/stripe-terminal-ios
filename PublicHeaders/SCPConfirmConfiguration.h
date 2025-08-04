//
//  SCPConfirmConfiguration.h
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
#import <StripeTerminal/SCPJSONDecodable.h>
#import <StripeTerminal/SCPSurchargeConfiguration.h>
NS_ASSUME_NONNULL_BEGIN

/**
 * The `ConfirmConfiguration` contains configuration information relevant to confirming a payment
 * intent.
 */
NS_SWIFT_NAME(ConfirmConfiguration)
@interface SCPConfirmConfiguration : NSObject <NSCopying>

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
 Use `SCPConfirmConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPConfirmConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The `ConfirmConfigurationBuilder` is used to create a `ConfirmConfiguration` object.
 */
NS_SWIFT_NAME(ConfirmConfigurationBuilder)
@interface SCPConfirmConfigurationBuilder : SCPBuilder <SCPConfirmConfiguration *>

/// Set the returnUrl property for the `ConfirmConfiguration` object that will be built.
- (SCPConfirmConfigurationBuilder *)setReturnUrl:(NSString *)returnUrl;

/// Set the surchargeConfiguration property for the `ConfirmConfiguration` object that will be built.
- (SCPConfirmConfigurationBuilder *)setSurchargeConfiguration:(SCPSurchargeConfiguration *)surchargeConfiguration;

@end

NS_ASSUME_NONNULL_END
