//
//  SCPLocalizationResult.h
//  StripeTerminal
//
//  Created by Callum Huang on 2026/5/18.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPApiError.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Reports the outcome of localizing an `SCPApiError.message`.

 - `requestedLocale` reflects the locale the SDK sent in the
   `Accept-Language` request header.
 - `resolvedLocale` reflects the locale the message was localized to,
   taken from the `Content-Language` response header (defaults to `en-US`
   if the header is absent).

 The two may differ when the requested locale is not supported — in that
 case, the server falls back to `en-US`.
 */
NS_SWIFT_NAME(ApiError.LocalizationResult)
@interface SCPLocalizationResult : NSObject <NSCopying>

/// The locale sent in the `Accept-Language` request header.
@property (nonatomic, copy, readonly) NSString *requestedLocale;

/// The locale the message was localized to.
@property (nonatomic, copy, readonly) NSString *resolvedLocale;

/**
 Unavailable. `SCPLocalizationResult` is created internally by the SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. `SCPLocalizationResult` is created internally by the SDK.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
