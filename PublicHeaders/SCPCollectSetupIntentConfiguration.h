//
//  SCPCollectSetupIntentConfiguration.h
//  StripeTerminal
//
//  Created by Michael Shafrir on 8/28/23.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPAllowRedisplay.h>
#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPCustomerCancellation.h>
#import <StripeTerminal/SCPMotoConfiguration.h>
#import <StripeTerminal/SCPSetupIntentCollectionReason.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The `CollectSetupIntentConfiguration` contains configuration information relevant to collecting a payment
 * method for an SCPSetupIntent.
 */
NS_SWIFT_NAME(CollectSetupIntentConfiguration)
@interface SCPCollectSetupIntentConfiguration : NSObject <NSCopying>

/**
 Controls whether the payment method may be shown again to its customer in a checkout flow.

 Collecting cardholder consent
 -----------------------------

 Card networks require that you collect consent from the customer before saving
 and reusing their card information. The SetupIntent confirmation API method
 normally takes a `mandate_data` hash that lets you specify details about the
 customer's consent. The Stripe Terminal SDK will fill in the `mandate_data`
 hash with relevant information, but in order for it to do so, you must specify
 whether you have gathered consent from the cardholder using this property.

 The payment method will not be collected without the cardholder's consent.

 `allowRedisplay` must be set to `always` or `limited`.

 */
@property (nonatomic, assign, readonly) SCPAllowRedisplay allowRedisplay;

/**
 Controls whether customer-initiated cancellation is enabled during setup intent collection.

 Defaults to SCPCustomerCancellationEnableIfAvailable.
 */
@property (nonatomic, assign, readonly) SCPCustomerCancellation customerCancellation;

/**
 Collect and process the SetupIntent as a Mail Order/Telephone Order payment on Stripe smart readers. Contact Stripe support to enable this feature on your account.
 @see https://docs.stripe.com/terminal/features/mail-telephone-orders/overview
 */
@property (nonatomic, strong, nullable, readonly) SCPMotoConfiguration *motoConfiguration;

/**
 The collection reason, applicable only for Tap to Pay devices.

 Defaults to SCPSetupIntentCollectionReasonSaveCard
 */
@property (nonatomic, assign, readonly) SCPSetupIntentCollectionReason collectionReason;

/**
 Use `SCPCollectSetupIntentConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPCollectSetupIntentConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The `CollectSetupIntentConfigurationBuilder` is used to create a `CollectSetupIntentConfiguration` object.
 */
NS_SWIFT_NAME(CollectSetupIntentConfigurationBuilder)
@interface SCPCollectSetupIntentConfigurationBuilder : SCPBuilder <SCPCollectSetupIntentConfiguration *>

/**
 Initializes `SCPCollectSetupIntentConfigurationBuilder` with the given `allowRedisplay` value.

 @param allowRedisplay Indicates whether the customer consented to redisplaying the saved payment method.
 */
- (instancetype)initWithAllowRedisplay:(SCPAllowRedisplay)allowRedisplay NS_DESIGNATED_INITIALIZER;

/// Set the allowRedisplay property for the `CollectSetupIntentConfiguration` object that will be built.
- (SCPCollectSetupIntentConfigurationBuilder *)setAllowRedisplay:(SCPAllowRedisplay)allowRedisplay;

/// Set the customerCancellation property for the `CollectSetupIntentConfiguration` object that will be built.
- (SCPCollectSetupIntentConfigurationBuilder *)setCustomerCancellation:(SCPCustomerCancellation)customerCancellation;

/// Set the motoConfiguration property for the `CollectSetupIntentConfiguration` object that will be built.
- (SCPCollectSetupIntentConfigurationBuilder *)setMotoConfiguration:(nullable SCPMotoConfiguration *)motoConfiguration;

/// Set the collection reason for the `CollectSetupIntentConfiguration` object that will be built.
/// Applicable only for Tap to Pay devices. The default value is `SCPSetupIntentCollectionReasonSaveCard`.
- (SCPCollectSetupIntentConfigurationBuilder *)setCollectionReason:(SCPSetupIntentCollectionReason)collectionReason;

/**
 Use `initWithAllowRedisplay:`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithAllowRedisplay:`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
