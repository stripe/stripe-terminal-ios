//
//  SCPPaymentOption.h
//  StripeTerminal
//
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPPaymentMethodType.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Type of payment option.
 */
typedef NS_ENUM(NSUInteger, SCPPaymentOptionType) {
    /**
     Card payment option (any card-based payment method).
     */
    SCPPaymentOptionTypeCard,

    /**
     Non-card payment option (eg. qr code based payments).
     */
    SCPPaymentOptionTypeNonCard,
} NS_SWIFT_NAME(PaymentOptionType);

/**
 Represents a payment option available during payment collection.
 */
NS_SWIFT_NAME(PaymentOption)
@interface SCPPaymentOption : NSObject <NSCopying>

/**
 The type of this payment option.
 */
@property (nonatomic, readonly) SCPPaymentOptionType type;

/**
 For non-card payment options, the specific payment method type.
 Only set when type is `SCPPaymentOptionTypeNonCard`.
 */
@property (nonatomic, readonly) SCPPaymentMethodType paymentMethodType;

/**
 Creates a card payment option.
 */
+ (instancetype)cardPaymentOption;

/**
 Creates a non-card payment option with the specified payment method type.

 @param paymentMethodType The specific payment method type (must be a non-card type)
 */
+ (instancetype)nonCardPaymentOptionWithType:(SCPPaymentMethodType)paymentMethodType;

/**
 You cannot directly instantiate `SCPPaymentOption`.
 Use `cardPaymentOption` or `nonCardPaymentOptionWithType:` instead.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPPaymentOption`.
 Use `cardPaymentOption` or `nonCardPaymentOptionWithType:` instead.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
