//
// SCPAmountDetails.h
// StripeTerminal
//
// Created by Brian Cooke on 11/9/22.
// Copyright (c) 2022 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPTip;

/**
 Contains details about items included in the [PaymentIntent] amount
 */
@interface SCPAmountDetails : NSObject <SCPJSONDecodable, NSCopying>

/// Details about the tip
@property (nonatomic, nullable, readonly) SCPTip *tip;

/**
 You cannot directly instantiate `SCPAmountDetails`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPAmountDetails`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
