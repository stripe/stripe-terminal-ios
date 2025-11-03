//
//  SCPUseStripeSdk.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2025-08-29.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains information for Stripe SDK authentication flows.
 */
NS_SWIFT_NAME(UseStripeSdk)
@interface SCPUseStripeSdk : NSObject <NSCopying>

/**
 The type of authentication flow that should be performed by the Stripe SDK.
 */
@property (nonatomic, nullable, readonly) NSString *type;

/**
 You cannot directly instantiate `SCPUseStripeSdk`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPUseStripeSdk`. You should only use
 one that has been returned by our SDK.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
