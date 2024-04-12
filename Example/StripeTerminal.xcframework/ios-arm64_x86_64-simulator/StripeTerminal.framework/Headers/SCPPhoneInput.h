//
//  SCPPhoneInput.h
//  StripeTerminal
//
//  Created by Stephen Lee on 11/06/23.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPInput.h>
#import <StripeTerminal/SCPToggle.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains information about a phone form to display on the reader

 @see https://stripe.com/docs/terminal/features/collect-inputs
 */
NS_SWIFT_NAME(PhoneInput)
@interface SCPPhoneInput : SCPInput

/**
 Represents the form's title
 */
@property (nonatomic, readonly) NSString *title;

/**
 Represents the form's description
 */
@property (nonatomic, nullable, readonly) NSString *stripeDescription;

/**
 Represents the skip button text
 */
@property (nonatomic, nullable, readonly) NSString *skipButtonText;

/**
 Represents the submit button text
 */
@property (nonatomic, nullable, readonly) NSString *submitButtonText;

/**
 Represents the toggles
 */
@property (nonatomic, readonly, copy) NSArray<SCPToggle *> *toggles;

/**
 Use `SCPPhoneInputBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPPhoneInputBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder class for `SCPPhoneInput`.
 */
NS_SWIFT_NAME(PhoneInputBuilder)
@interface SCPPhoneInputBuilder : SCPBuilder <SCPPhoneInput *>

/**
 Initializes a new instance of the `SCPPhoneInputBuilder` class with the provided
 title.
 */
- (instancetype)initWithTitle:(NSString *)title NS_DESIGNATED_INITIALIZER;

/// @see `SCPPhoneInput.title`
- (SCPPhoneInputBuilder *)setTitle:(NSString *)title;

/// @see `SCPPhoneInput.required`
- (SCPPhoneInputBuilder *)setRequired:(BOOL)required;

/// @see `SCPPhoneInput.stripeDescription`
- (SCPPhoneInputBuilder *)setStripeDescription:(NSString *)stripeDescription;

/// @see `SCPPhoneInput.skipButton`
- (SCPPhoneInputBuilder *)setSkipButtonText:(NSString *)skipButtonText;

/// @see `SCPPhoneInput.submitButton`
- (SCPPhoneInputBuilder *)setSubmitButtonText:(NSString *)submitButtonText;

/// @see `SCPPhoneInput.toggles`
- (SCPPhoneInputBuilder *)setToggles:(NSArray<SCPToggle *> *)toggles;

/**
 Use `initWithTitle`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithTitle`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
