//
//  SCPCollectDataConfiguration.h
//  StripeTerminal
//
//  Created by Mindy Lou on 4/25/24.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <StripeTerminal/SCPCollectedData.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPCustomerCancellation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains configuration information relevant to collecting non-payment data.
*/
NS_SWIFT_NAME(CollectDataConfiguration)
@interface SCPCollectDataConfiguration : NSObject <NSCopying>

/// The non-payment data type to read (eg. magstripe).
@property (nonatomic, readonly, assign) SCPCollectDataType collectDataType;

/**
 Controls whether customer-initiated cancellation is enabled during data collection.

 Defaults to SCPCustomerCancellationEnableIfAvailable.
 */
@property (nonatomic, assign, readonly) SCPCustomerCancellation customerCancellation;

/**
 Use `SCPCollectDataConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;
/**
 Use `SCPCollectDataConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The `CollectDataConfigurationBuilder` is used to create a `CollectDataConfiguration` object.
 */
NS_SWIFT_NAME(CollectDataConfigurationBuilder)
@interface SCPCollectDataConfigurationBuilder : SCPBuilder <SCPCollectDataConfiguration *>

/// Set the collectDataType property for the `CollectDataConfiguration` object that will be built.
- (SCPCollectDataConfigurationBuilder *)setCollectDataType:(SCPCollectDataType)collectDataType;

/// Set the customerCancellation property for the `CollectConfiguration` object that will be built.
- (SCPCollectDataConfigurationBuilder *)setCustomerCancellation:(SCPCustomerCancellation)customerCancellation;

@end

NS_ASSUME_NONNULL_END
