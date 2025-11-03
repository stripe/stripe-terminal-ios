//
//  SCPCollectRefundConfiguration.h
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
#import <StripeTerminal/SCPCustomerCancellation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The `CollectRefundConfiguration` contains configuration information relevant to refunding a payment.
 */
NS_SWIFT_NAME(CollectRefundConfiguration)
@interface SCPCollectRefundConfiguration : NSObject <NSCopying>

/**
 Controls whether customer-initiated cancellation is enabled during refund collection.

 Defaults to SCPCustomerCancellationEnableIfAvailable.
 */
@property (nonatomic, assign, readonly) SCPCustomerCancellation customerCancellation;

/**
 Use `SCPCollectRefundConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPCollectRefundConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The `CollectRefundConfigurationBuilder` is used to create a `CollectRefundConfiguration` object.
 */
NS_SWIFT_NAME(CollectRefundConfigurationBuilder)
@interface SCPCollectRefundConfigurationBuilder : SCPBuilder <SCPCollectRefundConfiguration *>

/// Set the customerCancellation property for the `CollectRefundConfiguration` object that will be built.
- (SCPCollectRefundConfigurationBuilder *)setCustomerCancellation:(SCPCustomerCancellation)customerCancellation;

@end

NS_ASSUME_NONNULL_END
