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
#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains configuration information relevant to collecting non-payment data.
*/
NS_SWIFT_NAME(CollectDataConfiguration)
@interface SCPCollectDataConfiguration : NSObject <NSCopying>

/// The non-payment data type to read (eg. magstripe).
@property (nonatomic, readonly, assign) SCPCollectDataType collectDataType;

@end

/**
 The `CollectDataConfigurationBuilder` is used to create a `CollectDataConfiguration` object.
 */
NS_SWIFT_NAME(CollectDataConfigurationBuilder)
@interface SCPCollectDataConfigurationBuilder : SCPBuilder <SCPCollectDataConfiguration *>

/// Set the collectDataType property for the `CollectDataConfiguration` object that will be built.
- (SCPCollectDataConfigurationBuilder *)setCollectDataType:(SCPCollectDataType)collectDataType;

@end

NS_ASSUME_NONNULL_END
