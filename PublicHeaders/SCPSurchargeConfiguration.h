//
//  SCPSurchargeConfiguration.h
//  StripeTerminal
//
//  Created by Nishant Karajgikar on 06/13/2025.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Enum representing surcharge consent collection states.
 */
typedef NS_ENUM(NSUInteger, SCPSurchargeConsentCollection) {
    /**
     * Surcharge consent collection is disabled.
     */
    SCPSurchargeConsentCollectionDisabled,
    /**
     * Surcharge consent collection is enabled.
     */
    SCPSurchargeConsentCollectionEnabled,
} NS_SWIFT_NAME(SurchargeConsentCollection);

/**
 * The `SurchargeConsent` contains configuration information for surcharge consent collection.
 */
NS_SWIFT_NAME(SurchargeConsent)
@interface SCPSurchargeConsent : NSObject <NSCopying>

/**
 Whether to collect surcharge consent from the customer.

 Defaults to `SCPSurchargeConsentCollectionDisabled`.
 */
@property (nonatomic, assign, readonly) SCPSurchargeConsentCollection collection;

/**
 Display a custom message on the surcharge consent screen to the customer.
 If null, then no additional message will be displayed to the customer.

 Defaults to nil
 */
@property (nonatomic, strong, nullable, readonly) NSString *notice;

/**
 Use `SCPSurchargeConsentBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPSurchargeConsentBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The `SurchargeConsentBuilder` is used to create a `SurchargeConsent` object.
 */
NS_SWIFT_NAME(SurchargeConsentBuilder)
@interface SCPSurchargeConsentBuilder : SCPBuilder <SCPSurchargeConsent *>

/// Set the collection property for the `SurchargeConsent` object that will be built.
- (SCPSurchargeConsentBuilder *)setCollection:(SCPSurchargeConsentCollection)collection;

/// Set the notice property for the `SurchargeConsent` object that will be built.
- (SCPSurchargeConsentBuilder *)setNotice:(NSString *)notice;

@end

/**
 * The `SurchargeConfiguration` contains configuration information relevant to surcharge collection
 * during payment confirmation.
 */
NS_SWIFT_NAME(SurchargeConfiguration)
@interface SCPSurchargeConfiguration : NSObject <NSCopying>

/**
 The surcharge amount to apply to the transaction.

 Defaults to nil.
 */
@property (nonatomic, strong, nullable, readonly) NSNumber *amount;

/**
 Configuration for surcharge consent collection.

 Defaults to nil.
 */
@property (nonatomic, strong, nullable, readonly) SCPSurchargeConsent *surchargeConsent;

/**
 Use `SCPSurchargeConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPSurchargeConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The `SurchargeConfigurationBuilder` is used to create a `SurchargeConfiguration` object.
 */
NS_SWIFT_NAME(SurchargeConfigurationBuilder)
@interface SCPSurchargeConfigurationBuilder : SCPBuilder <SCPSurchargeConfiguration *>

/// Set the amount property for the `SurchargeConfiguration` object that will be built.
- (SCPSurchargeConfigurationBuilder *)setAmount:(NSUInteger)amount;

/// Set the surchargeConsent property for the `SurchargeConfiguration` object that will be built.
- (SCPSurchargeConfigurationBuilder *)setSurchargeConsent:(SCPSurchargeConsent *)surchargeConsent;

@end

NS_ASSUME_NONNULL_END
