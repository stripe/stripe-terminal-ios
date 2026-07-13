//
//  SCPLocaleConfig.h
//  StripeTerminal
//
//  Created by Callum Huang on 2026/5/18.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPBuilder.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Configures localization of API error messages returned through
 `SCPApiError.message`.

 API errors surfaced through `NSError`'s
 `SCPErrorKeyStripeAPIError` will have their `SCPApiError.message`
 translated to the resolved locale.

 For smart readers, reader software version 2.43 or later is required for localization.

 Note: The scope of localization may expand in future SDK releases.
 For example, `NSError.localizedDescription` and other SDK-originated
 strings may also be localized. Integrations should avoid relying on
 error message content for application logic. Use error codes such as
 `SCPError` and `SCPApiError.code` instead.
 */
NS_SWIFT_NAME(LocaleConfig)
@interface SCPLocaleConfig : NSObject <NSCopying>

/**
 Localizes API error messages to the cardholder's preferred language when
 available, falling back to the device locale otherwise. If either locale
 is not supported by Stripe's localization infrastructure, error messages
 will fall back to English (`en-US`).

 During a transaction, if the card provides a language preference and the
 connected reader supports extracting it, that language is used. Card language
 preference extraction is supported on smart readers (contact transactions,
 v2.43+). Tap to Pay on iPhone and mobile readers (Bluetooth/USB) always
 fall back to the device locale.

 Use this option when you want error messages to automatically follow the
 device locale, or in customer-facing scenarios where the cardholder needs
 to understand the card decline error message.
 */
@property (class, nonatomic, readonly) SCPLocaleConfig *cardLanguagePreferenceIfAvailable;

/**
 Unavailable. Use `cardLanguagePreferenceIfAvailable` or
 `SCPHardcodedLocaleConfigBuilder` to create a locale config.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. Use `cardLanguagePreferenceIfAvailable` or
 `SCPHardcodedLocaleConfigBuilder` to create a locale config.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

#pragma mark - Hardcoded locale

/**
 Localizes API error messages to a fixed locale tag.

 The locale tag must conform to the format `language[-script][-region]` where:
 - `language` is a 2-3 letter ISO 639 code (e.g., "en", "fil")
 - `script` (optional) is only "Hans" or "Hant"
 - `region` (optional) is a 2-letter ISO 3166-1 alpha-2 code (e.g., "US") or a
   3-digit UN M.49 code (e.g., "419")

 If the locale is not supported by Stripe's localization infrastructure,
 error messages will fall back to English (`en-US`).
 */
NS_SWIFT_NAME(HardcodedLocaleConfig)
@interface SCPHardcodedLocaleConfig : SCPLocaleConfig

/// The locale sent in the `Accept-Language` header.
@property (nonatomic, copy, readonly) NSString *locale;

/**
 Unavailable. Use `SCPHardcodedLocaleConfigBuilder` to create a hardcoded locale config.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. Use `SCPHardcodedLocaleConfigBuilder` to create a hardcoded locale config.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A builder class for `SCPHardcodedLocaleConfig`. The locale tag is validated
 by `build:`.
 */
NS_SWIFT_NAME(HardcodedLocaleConfigBuilder)
@interface SCPHardcodedLocaleConfigBuilder : SCPBuilder <SCPHardcodedLocaleConfig *>

/**
 Creates a builder initialized with the provided locale tag.
 */
- (instancetype)initWithLocale:(NSString *)locale NS_DESIGNATED_INITIALIZER;

/**
 Updates the locale tag to use when building the config.
 */
- (SCPHardcodedLocaleConfigBuilder *)setLocale:(NSString *)locale;

/**
 Unavailable. Use `initWithLocale:` instead.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Unavailable. Use `initWithLocale:` instead.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
