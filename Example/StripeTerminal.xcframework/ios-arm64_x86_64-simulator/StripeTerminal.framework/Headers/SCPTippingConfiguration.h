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

NS_ASSUME_NONNULL_BEGIN

/**
The `TippingConfiguration` contains configuration information relevant to collecting tips.
 */
NS_SWIFT_NAME(TippingConfiguration)
@interface SCPTippingConfiguration : NSObject

/**
 The amount of the payment total eligible for tips.
 */
@property (nonatomic, assign) NSInteger eligibleAmount;

/**
 Initialize a `TippingConfiguration` instance.

 @param eligibleAmount Amount eligible for tips.
 */
- (instancetype)initWithEligibleAmount:(NSInteger)eligibleAmount;

/**
 Use `initWithEligibleAmount:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithEligibleAmount:`
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
