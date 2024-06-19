//
//  SCPCollectedData.h
//  StripeTerminal
//
//  Created by Mindy Lou on 3/29/24.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The type of data to collect.
 */
typedef NS_ENUM(NSUInteger, SCPCollectDataType) {
    /// Unknown collect data type.
    SCPCollectDataTypeUnknown,
    /// Collect data using the magstripe interface.
    SCPCollectDataTypeMagstripe,
} NS_SWIFT_NAME(CollectDataType);

/**
 Represents non-payment data collected using `collectData`.
 */
NS_SWIFT_NAME(CollectedData)
@interface SCPCollectedData : NSObject

/**
 Unique identifier for the object.
 */
@property (nonatomic, nullable, readonly, copy) NSString *stripeId;

/**
 Time at which the object was created.
 */
@property (nonatomic, readonly) NSDate *created;

/**
 Whether or not the object exists in livemode.
 */
@property (nonatomic, assign, readonly) BOOL livemode;

/**
 You cannot directly instantiate `SCPCollectedData`. You should only use
 one that has been returned by our SDK.

 @see SCPTerminal.shared.collectData()
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPCollectedData`. You should only use
 one that has been returned by our SDK.

 @see SCPTerminal.shared.collectData()
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
