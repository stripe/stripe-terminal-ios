//
//  SCPEmailInput.h
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
 Contains information about an email form to display on the reader

 @see https://stripe.com/docs/terminal/features/collect-inputs
 */
NS_SWIFT_NAME(EmailInput)
@interface SCPEmailInput : SCPInput

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
 Use `SCPEmailInputBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPEmailInputBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder class for `SCPEmailInput`.
 */
NS_SWIFT_NAME(EmailInputBuilder)
@interface SCPEmailInputBuilder : SCPBuilder <SCPEmailInput *>

/**
 Initializes a new instance of the `SCPEmailInputBuilder` class with the provided
 title.
 */
- (instancetype)initWithTitle:(NSString *)title NS_DESIGNATED_INITIALIZER;

/// @see `SCPEmailInput.title`
- (SCPEmailInputBuilder *)setTitle:(NSString *)title;

/// @see `SCPEmailInput.required`
- (SCPEmailInputBuilder *)setRequired:(BOOL)required;

/// @see `SCPEmailInput.stripeDescription`
- (SCPEmailInputBuilder *)setStripeDescription:(NSString *)stripeDescription;

/// @see `SCPEmailInput.skipButton`
- (SCPEmailInputBuilder *)setSkipButtonText:(NSString *)skipButtonText;

/// @see `SCPEmailInput.submitButton`
- (SCPEmailInputBuilder *)setSubmitButtonText:(NSString *)submitButtonText;

/// @see `SCPEmailInput.toggles`
- (SCPEmailInputBuilder *)setToggles:(NSArray<SCPToggle *> *)toggles;

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
