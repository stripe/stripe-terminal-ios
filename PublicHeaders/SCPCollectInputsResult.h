//
//  SCPCollectInputsResult.h
//  StripeTerminal
//
//  Created by Stephen Lee on 2023-10-20.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains information about the data collected from a given form
 */
NS_SWIFT_NAME(CollectInputsResult)
@interface SCPCollectInputsResult : NSObject

/**
 If true, the skip button was used to skip the form
 */
@property (nonatomic, readonly) BOOL skipped;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
