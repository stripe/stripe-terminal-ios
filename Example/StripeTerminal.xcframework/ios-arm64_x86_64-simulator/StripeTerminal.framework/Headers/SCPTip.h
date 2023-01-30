//
// SCPTip.h
// StripeTerminal
//
// Created by Brian Cooke on 11/9/22.
// Copyright (c) 2022 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains details about tips

 For more information, see the official Stripe docs: [Collect on-reader tips](https://stripe.com/docs/terminal/features/collecting-tips/on-reader)
 */
@interface SCPTip : NSObject <SCPJSONDecodable, NSCopying>

/**
 Portion of the amount that corresponds to a tip

 The value will be `null` in the following scenarios:
 - tipping is skipped by using the CollectConfiguration.skipTipping flag or by setting
   TippingConfiguration.eligibleAmount to `0`
 - current reader location does not have a tipping config set

 If "No tip" is selected on the reader, the value will be `0`
 */
@property (nonatomic, nullable, readonly) NSNumber *amount;

/**
 You cannot directly instantiate `SCPTip`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPTip`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
