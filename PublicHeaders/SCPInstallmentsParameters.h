//
//  SCPInstallmentsParameters.h
//  StripeTerminal
//
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The type of an installment plan.
 */
typedef NS_ENUM(NSUInteger, SCPInstallmentPlanType) {
    /**
    An installment plan with a fixed number of payments.
    */
    SCPInstallmentPlanTypeFixedCount,
    /**
     An installment plan with a bonus payment structure.
     */
    SCPInstallmentPlanTypeBonus,
    /**
     An installment plan with a revolving payment structure.
     */
    SCPInstallmentPlanTypeRevolving,
} NS_SWIFT_NAME(InstallmentPlanType);

/**
 The interval between payments in an installment plan.
 */
typedef NS_ENUM(NSUInteger, SCPInstallmentPlanInterval) {
    /**
     Payments are made monthly.
     */
    SCPInstallmentPlanIntervalMonth,
} NS_SWIFT_NAME(InstallmentPlanInterval);

/**
 Details about an installment plan available for or selected on a PaymentIntent.
 */
NS_SWIFT_NAME(InstallmentPlanDetails)
@interface SCPInstallmentPlanDetails : NSObject <NSCopying>

/**
 The installment plan type. `SCPInstallmentPlanType` as a nullable NSNumber.
 */
@property (nonatomic, copy, nullable, readonly) NSNumber *type;

/**
 The number of payments in a fixed-count installment plan.
 */
@property (nonatomic, copy, nullable, readonly) NSNumber *count;

/**
 The interval between payments. `SCPInstallmentPlanInterval` as a nullable NSNumber.
 */
@property (nonatomic, copy, nullable, readonly) NSNumber *interval;

/**
 You cannot directly instantiate `SCPInstallmentPlanDetails`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPInstallmentPlanDetails`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Parameters for card-present installments on a PaymentIntent.
 */
NS_SWIFT_NAME(InstallmentsParameters)
@interface SCPInstallmentsParameters : NSObject <NSCopying>

/**
 Whether card-present installments are enabled for the PaymentIntent.
 */
@property (nonatomic, copy, nullable, readonly) NSNumber *enabled;

/**
 Installment plans returned after payment method collection. This property is readonly.
 */
@property (nonatomic, copy, nullable, readonly) NSArray<SCPInstallmentPlanDetails *> *availablePlans;

/**
 The installment plan selected by the cardholder, returned after confirmation. This property is readonly.
 */
@property (nonatomic, copy, nullable, readonly) SCPInstallmentPlanDetails *plan;

/**
 Use `SCPInstallmentsParametersBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPInstallmentsParametersBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder for `SCPInstallmentsParameters`.
 */
NS_SWIFT_NAME(InstallmentsParametersBuilder)
@interface SCPInstallmentsParametersBuilder : SCPBuilder <SCPInstallmentsParameters *>

/// @see `SCPInstallmentsParameters.enabled`
- (SCPInstallmentsParametersBuilder *)setEnabled:(BOOL)enabled;

/// Build the `SCPInstallmentsParameters` instance.
- (SCPInstallmentsParameters *)build:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
