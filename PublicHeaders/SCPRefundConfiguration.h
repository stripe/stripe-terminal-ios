//
//  SCPRefundConfiguration.h
//  StripeTerminal
//
//  Created by Michael Shafrir on 8/28/23.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The `RefundConfiguration` contains configuration information relevant to refunding a payment.
 */
NS_SWIFT_NAME(RefundConfiguration)
@interface SCPRefundConfiguration : NSObject <NSCopying>

/**
 Whether to show a cancel button in transaction UI on Stripe smart readers.

 Defaults to NO.
 */
@property (nonatomic, assign, readonly) BOOL enableCustomerCancellation;

/**
 Use `SCPRefundConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPRefundConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The `RefundConfigurationBuilder` is used to create a `RefundConfiguration` object.
 */
NS_SWIFT_NAME(RefundConfigurationBuilder)
@interface SCPRefundConfigurationBuilder : SCPBuilder <SCPRefundConfiguration *>

/// Set the enableCustomerCancellation property for the `RefundConfiguration` object that will be built.
- (SCPRefundConfigurationBuilder *)setEnableCustomerCancellation:(BOOL)enableCustomerCancellation;

@end

NS_ASSUME_NONNULL_END
