//
//  SCPWechatPayDisplayQrCode.h
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

/**
 Contains instructions for displaying a QR code for WeChat Pay payments.
 */
NS_SWIFT_NAME(WechatPayDisplayQrCode)
@interface SCPWechatPayDisplayQrCode : NSObject <NSCopying>

/**
 The QR code data string that should be displayed to the customer.
 */
@property (nonatomic, nullable, readonly) NSString *data;

/**
 The URL to hosted payment instructions for the customer.
 */
@property (nonatomic, nullable, readonly) NSString *hostedInstructionsUrl;

/**
 A data URL containing the QR code image.
 */
@property (nonatomic, nullable, readonly) NSString *imageDataUrl;

/**
 The PNG image URL for the QR code.
 */
@property (nonatomic, nullable, readonly) NSString *imageUrlPng;

/**
 The SVG image URL for the QR code.
 */
@property (nonatomic, nullable, readonly) NSString *imageUrlSvg;

/**
 You cannot directly instantiate `SCPWechatPayDisplayQrCode`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPWechatPayDisplayQrCode`. You should only use
 one that has been returned by our SDK.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
