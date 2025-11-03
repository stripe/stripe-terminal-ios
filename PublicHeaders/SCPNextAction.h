//
//  SCPNextAction.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2025-08-29.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPWechatPayDisplayQrCode, SCPRedirectToUrl, SCPUseStripeSdk;

/**
 Represents the next action that should be taken for a PaymentIntent.

 @see https://stripe.com/docs/api/payment_intents/object#payment_intent_object-next_action
 */
NS_SWIFT_NAME(NextAction)
@interface SCPNextAction : NSObject <NSCopying>

/**
 The type of next action to perform.
 */
@property (nonatomic, nullable, readonly) NSString *type;

/**
 Contains instructions for displaying a QR code for WeChat Pay payments.
 */
@property (nonatomic, nullable, readonly) SCPWechatPayDisplayQrCode *wechatPayDisplayQrCode;

/**
 Contains instructions for redirecting the customer to another URL.
 */
@property (nonatomic, nullable, readonly) SCPRedirectToUrl *redirectToUrl;

/**
 When confirming a PaymentIntent with Stripe.js, Stripe.js depends on the contents of this object to invoke authentication flows.
 */
@property (nonatomic, nullable, readonly) SCPUseStripeSdk *useStripeSdk;

/**
 You cannot directly instantiate `SCPNextAction`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPNextAction`. You should only use
 one that has been returned by our SDK.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
