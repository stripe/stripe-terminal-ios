//
//  SCPSurchargeDetails.h
//  StripeTerminal
//
//  Created by Qiang Jiang on 4/7/26.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Represents the surcharge eligibility status for a transaction.
 */
typedef NS_ENUM(NSUInteger, SCPSurchargeStatus) {
    /**
     Surcharging is available for this transaction.
     */
    SCPSurchargeStatusAvailable,
    /**
     Surcharging is not available for this transaction.
     */
    SCPSurchargeStatusUnavailable,
} NS_SWIFT_NAME(SurchargeStatus);

/**
 Contains details about surcharges, including the surcharge amount,
 availability, and maximum allowed amount.
 */
NS_SWIFT_NAME(SurchargeDetails)
@interface SCPSurchargeDetails : NSObject <NSCopying>

/**
 Amount that corresponds to a surcharge, in the smallest currency unit (e.g. cents).
 @see https://stripe.com/docs/currencies#zero-decimal
 */
@property (nonatomic, readonly, nullable) NSNumber *amount;

/**
 The maximum amount allowed for the surcharge, in the smallest currency unit (e.g. cents).
 @see https://stripe.com/docs/currencies#zero-decimal
 */
@property (nonatomic, readonly, nullable) NSNumber *maximumAmount;

/**
 The surcharge eligibility status. `SCPSurchargeStatus` as a nullable NSNumber.
 */
@property (nonatomic, strong, nullable, readonly) NSNumber *status;

/**
 You cannot directly instantiate `SCPSurchargeDetails`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPSurchargeDetails`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
