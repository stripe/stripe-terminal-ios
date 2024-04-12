//
//  SCPTextInput.h
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
 Contains information about a Text form to display on the reader

 @see https://stripe.com/docs/terminal/features/collect-inputs
 */
NS_SWIFT_NAME(TextInput)
@interface SCPTextInput : SCPInput

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
 Use `SCPTextInputBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPTextInputBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder class for `SCPTextInput`.
 */
NS_SWIFT_NAME(TextInputBuilder)
@interface SCPTextInputBuilder : SCPBuilder <SCPTextInput *>

/**
 Initializes a new instance of the `SCPTextInputBuilder` class with the provided
 title.
 */
- (instancetype)initWithTitle:(NSString *)title NS_DESIGNATED_INITIALIZER;

/// @see `SCPTextInput.title`
- (SCPTextInputBuilder *)setTitle:(NSString *)title;

/// @see `SCPTextInput.required`
- (SCPTextInputBuilder *)setRequired:(BOOL)required;

/// @see `SCPTextInput.stripeDescription`
- (SCPTextInputBuilder *)setStripeDescription:(NSString *)stripeDescription;

/// @see `SCPTextInput.skipButton`
- (SCPTextInputBuilder *)setSkipButtonText:(NSString *)skipButtonText;

/// @see `SCPTextInput.submitButton`
- (SCPTextInputBuilder *)setSubmitButtonText:(NSString *)submitButtonText;

/// @see `SCPTextInput.toggles`
- (SCPTextInputBuilder *)setToggles:(NSArray<SCPToggle *> *)toggles;

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
