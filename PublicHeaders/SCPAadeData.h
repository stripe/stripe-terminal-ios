//
//  SCPAadeData.h
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
 The mode of the AADE e-invoicing integration.

 Greek Governor's Decision A.1155/2023 mandates that all Greek POS systems integrate with an
 AADE-certified e-invoicing provider for every in-person transaction.
 */
typedef NS_ENUM(NSUInteger, SCPAadeMode) {
    /**
     Standard mode: the mark was produced by the live e-invoicing provider and will be
     validated against the provider's public signature.
     */
    SCPAadeModeStandard,

    /**
     Autonomous mode: the mark was produced locally by the POS during an e-invoicing system
     outage. No validation of the mark is required.
     */
    SCPAadeModeAutonomous,
} NS_SWIFT_NAME(AadeMode);

/**
 The reason the POS system is operating in autonomous (unbound) mode.
 */
typedef NS_ENUM(NSUInteger, SCPAadeUnboundPosReason) {
    /**
     The POS lost connectivity to the e-invoicing provider.
     */
    SCPAadeUnboundPosReasonInterconnectionLoss,

    /**
     The POS is operating as a replacement cash register system.
     */
    SCPAadeUnboundPosReasonReplacementCashSystem,

    /**
     The POS is locked and operating offline.
     */
    SCPAadeUnboundPosReasonLock,
} NS_SWIFT_NAME(AadeUnboundPosReason);

/**
 AADE (Greek tax authority) e-invoicing data required for card-present transactions in Greece.

 Greek Governor's Decision A.1155/2023 mandates that all Greek POS systems integrate with an
 AADE-certified e-invoicing provider. At the time of payment, the merchant's e-invoicing provider
 generates a cryptographic signature (MARK) over the transaction data which must be attached to
 the PaymentIntent.

 Use `SCPAadeDataBuilder` to create an instance.
 */
NS_SWIFT_NAME(AadeData)
@interface SCPAadeData : NSObject <NSCopying>

/**
 The cryptographic signature (MARK) produced by the merchant's e-invoicing
 provider. Only present in `SCPAadeModeStandard` mode.
 */
@property (nonatomic, nullable, readonly) NSString *mark;

/**
 The data payload that was signed to produce the `mark`. Only present in `SCPAadeModeStandard` mode.
 */
@property (nonatomic, nullable, readonly) NSString *markData;

/**
 The ID of the AADE-certified e-invoicing provider that produced the `mark`.
 Only present in `SCPAadeModeStandard` mode.
 */
@property (nonatomic, nullable, readonly) NSNumber *providerId;

/**
 The mode of the AADE e-invoicing integration.
 */
@property (nonatomic, readonly) SCPAadeMode mode;

/**
 The reason the POS system is operating in autonomous mode as a nullable NSNumber.
 Only present when `mode` is `SCPAadeModeAutonomous`.
 */
@property (nonatomic, nullable, readonly) NSNumber *unboundPos;

/**
 Use `SCPAadeDataBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPAadeDataBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder for `SCPAadeData`.
 */
NS_SWIFT_NAME(AadeDataBuilder)
@interface SCPAadeDataBuilder : SCPBuilder <SCPAadeData *>

/**
 Initialize a builder for `SCPAadeModeStandard` mode.

 @param mark The cryptographic signature produced by the e-invoicing provider.
 @param markData The data payload that was signed to produce the mark.
 @param providerId The ID of the AADE-certified e-invoicing provider.
 */
- (instancetype)initWithMark:(NSString *)mark
                    markData:(NSString *)markData
                  providerId:(NSInteger)providerId NS_DESIGNATED_INITIALIZER;

/**
 Initialize a builder for `SCPAadeModeAutonomous` mode.

 Use this initializer when the POS cannot reach the e-invoicing provider
 and must generate a local mark for later reconciliation with AADE.

 @param unboundPosReason The reason the POS is operating in autonomous mode.
 */
- (instancetype)initWithUnboundPosReason:(SCPAadeUnboundPosReason)unboundPosReason NS_DESIGNATED_INITIALIZER;

/**
 Build the `SCPAadeData` instance.
 */
- (nullable SCPAadeData *)build:(NSError **)error;

/**
 Use `initWithMark:markData:providerId:` or `initWithUnboundPosReason:`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithMark:markData:providerId:` or `initWithUnboundPosReason:`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
