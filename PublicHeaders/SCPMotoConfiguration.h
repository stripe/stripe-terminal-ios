//
//  SCPMotoConfiguration.h
//  StripeTerminal
//
//  Created by Matthew Mattei on 8/22/25.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The `MotoConfiguration` allows configuring Mail Order/Telephone Order transactions.

 Pass a non-nil value for this configuration to enable MO/TO.
 */
NS_SWIFT_NAME(MotoConfiguration)
@interface SCPMotoConfiguration : NSObject <NSCopying>

/**
 Skip collecting CVC on this MO/TO transaction. This feature is in private preview. Contact Stripe support to enable this feature on your account.
 */
@property (nonatomic, assign, readonly) BOOL skipCvc;

/**
 Use `SCPMotoConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPMotoConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A builder class for `SCPMotoConfiguration`.
 */
NS_SWIFT_NAME(MotoConfigurationBuilder)
@interface SCPMotoConfigurationBuilder : SCPBuilder <SCPMotoConfiguration *>

/// Set the skipCvc property for the `SCPMotoConfiguration` object that will be built.
- (instancetype)setSkipCvc:(BOOL)skipCvc;

@end

NS_ASSUME_NONNULL_END
