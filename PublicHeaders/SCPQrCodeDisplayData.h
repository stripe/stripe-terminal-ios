//
//  SCPQrCodeDisplayData.h
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
 Contains data necessary for displaying a QR code during payment processing.
 */
NS_SWIFT_NAME(QrCodeDisplayData)
@interface SCPQrCodeDisplayData : NSObject <NSCopying>

/**
 The payment method type associated with this QR code.
 */
@property (nonatomic, readonly) SCPPaymentMethodType paymentMethodType;

/**
 The PNG image URL for the QR code.
 */
@property (nonatomic, readonly) NSString *qrCodeImageUrlPng;

/**
 The SVG image URL for the QR code, if available.
 */
@property (nonatomic, nullable, readonly) NSString *qrCodeImageUrlSvg;

/**
 The expiration timestamp (in milliseconds since epoch) for the QR code.
 */
@property (nonatomic, readonly) NSTimeInterval expiresAtMs;

/**
 You cannot directly instantiate `SCPQrCodeDisplayData`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPQrCodeDisplayData`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
