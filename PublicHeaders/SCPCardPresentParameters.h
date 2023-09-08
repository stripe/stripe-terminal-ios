//
//  SCPCardPresentParameters.h
//  StripeTerminal
//
//  Created by Matthew Krager on 2/9/22.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Capture Method values that can be used as card-present payment method options.
 */
typedef NS_ENUM(NSUInteger, SCPCardPresentCaptureMethod) {
    /**
     Use manual_preferred if you prefer manual `capture_method` for the SCPPaymentIntent's `capture_method` but support
     falling back to automatic based on the presented payment method.
     */
    SCPCardPresentCaptureMethodManualPreferred,
} NS_SWIFT_NAME(CardPresentCaptureMethod);

/**
 Network routing priority on co-branded EMV cards supporting domestic debit and international card schemes.
 */
typedef NS_ENUM(NSUInteger, SCPCardPresentRouting) {
    /**
     Prioritize domestic debit network routing on payment method collection.
     */
    SCPCardPresentRoutingDomestic,

    /**
     Prioritize international network routing on payment method collection.
     */
    SCPCardPresentRoutingInternational,
} NS_SWIFT_NAME(CardPresentRouting);

/**
 Parameters that will be applied to the card present PaymentIntent.

 @see https://stripe.com/docs/api/payment_intents/create#create_payment_intent-payment_method_options-card_present
 */
NS_SWIFT_NAME(CardPresentParameters)
@interface SCPCardPresentParameters : NSObject

/**
 Using the extended authorizations feature, users in eligible categories can capture up to 31 days later, depending on the card brand.
 @see https://stripe.com/docs/terminal/features/extended-authorizations#authorization-validity
*/
@property (nonatomic, assign, readonly) BOOL requestExtendedAuthorization;

/**
 Allows you to increase the authorized amount on a confirmed PaymentIntent before you capture it. This means you can update the amount on a payment if the estimated price changes or goods and services are added. Before capture, each incremental authorization appears on your customer’s credit card statement as an additional pending charge.
 @see https://stripe.com/docs/terminal/features/incremental-authorizations
*/
@property (nonatomic, assign, readonly) BOOL requestIncrementalAuthorizationSupport;

/**
 `SCPCardPresentCaptureMethod` as a nullable NSNumber.
 */
@property (nonatomic, strong, nullable, readonly) NSNumber *captureMethod;

/**
 `SCPCardPresentRouting` as a nullable NSNumber.
 */
@property (nonatomic, strong, nullable, readonly) NSNumber *requestedPriority;

/**
 Use `SCPCardPresentParametersBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPCardPresentParametersBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder class for `SCPCardPresentParameters`.
 */
NS_SWIFT_NAME(CardPresentParametersBuilder)
@interface SCPCardPresentParametersBuilder : SCPBuilder <SCPCardPresentParameters *>

/// @see `SCPCardPresentParameters.requestExtendedAuthorization`
- (SCPCardPresentParametersBuilder *)setRequestExtendedAuthorization:(BOOL)requestExtendedAuthorization;

/// @see `SCPCardPresentParameters.requestIncrementalAuthorizationSupport`
- (SCPCardPresentParametersBuilder *)setRequestIncrementalAuthorizationSupport:(BOOL)requestIncrementalAuthorizationSupport;

/// @see `SCPCardPresentParameters.captureMethod`
- (SCPCardPresentParametersBuilder *)setCaptureMethod:(SCPCardPresentCaptureMethod)captureMethod;

/// @see `SCPCardPresentParameters.requestedPriority`
- (SCPCardPresentParametersBuilder *)setRequestedPriority:(SCPCardPresentRouting)requestedPriority;

@end

NS_ASSUME_NONNULL_END
