//
//  SCPTippingConfiguration.h
//  StripeTerminal
//
//  Created by Mindy Lou on 8/15/22.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>

NS_ASSUME_NONNULL_BEGIN

/**
The `TippingConfiguration` contains configuration information relevant to collecting tips.
 */
NS_SWIFT_NAME(TippingConfiguration)
@interface SCPTippingConfiguration : NSObject <NSCopying>

/**
 The amount of the payment total eligible for tips.
 */
@property (nonatomic, assign) NSInteger eligibleAmount;

/**
 Use `SCPTippingConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPTippingConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A builder class for `SCPTippingConfiguration`.
 */
NS_SWIFT_NAME(TippingConfigurationBuilder)
@interface SCPTippingConfigurationBuilder : SCPBuilder <SCPTippingConfiguration *>

/// Set the eligibleAmount property for the `SCPTippingConfiguration` object that will be built.
- (instancetype)setEligibleAmount:(NSInteger)eligibleAmount;

@end

NS_ASSUME_NONNULL_END
