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

NS_ASSUME_NONNULL_BEGIN

/**
 * The `ConfirmConfiguration` contains configuration information relevant to confirming a payment
 * intent.
 */
NS_SWIFT_NAME(ConfirmConfiguration)
@interface SCPConfirmConfiguration : NSObject <NSCopying>

/**
 Apply a surcharge to a transaction

 `updatePaymentIntent` must be set to true for to surcharge on a payment method

 Defaults to nil.
 */
@property (nonatomic, strong, nullable, readonly) NSNumber *amountSurcharge;

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

/// Set the amountSurcharge property for the `ConfirmConfiguration` object that will be built.
- (SCPConfirmConfigurationBuilder *)setAmountSurcharge:(NSUInteger)amountSurcharge;

@end

NS_ASSUME_NONNULL_END
