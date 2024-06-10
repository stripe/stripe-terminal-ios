//
//  SCPSurcharge.h
//  StripeTerminal
//
//  Created by Stanley Lin on 6/6/24.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains details about the availability and maximum amount for surcharging on this PaymentIntent.
 */
NS_SWIFT_NAME(Surcharge)
@interface SCPSurcharge : NSObject <SCPJSONDecodable, NSCopying>

/// Surcharge availability
@property (nonatomic, readonly) NSString *status;

/// The maximum surcharge amount allowed for this PaymentIntent.
@property (nonatomic, readonly, assign) NSUInteger maximumAmount;

/**
 You cannot directly instantiate `SCPSurcharge`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPSurcharge`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
