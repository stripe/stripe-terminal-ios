//
//  SCPNumericInput.h
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
 Contains information about a numeric form to display on the reader

 @see https://stripe.com/docs/terminal/features/collect-inputs
 */
NS_SWIFT_NAME(NumericInput)
@interface SCPNumericInput : SCPInput

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
 Use `SCPNumericInputBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPNumericInputBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder class for `SCPNumericInput`.
 */
NS_SWIFT_NAME(NumericInputBuilder)
@interface SCPNumericInputBuilder : SCPBuilder <SCPNumericInput *>

/**
 Initializes a new instance of the `SCPNumericInputBuilder` class with the provided
 title.
 */
- (instancetype)initWithTitle:(NSString *)title NS_DESIGNATED_INITIALIZER;

/// @see `SCPNumericInput.title`
- (SCPNumericInputBuilder *)setTitle:(NSString *)title;

/// @see `SCPNumericInput.required`
- (SCPNumericInputBuilder *)setRequired:(BOOL)required;

/// @see `SCPNumericInput.stripeDescription`
- (SCPNumericInputBuilder *)setStripeDescription:(NSString *)stripeDescription;

/// @see `SCPNumericInput.skipButton`
- (SCPNumericInputBuilder *)setSkipButtonText:(NSString *)skipButtonText;

/// @see `SCPNumericInput.submitButton`
- (SCPNumericInputBuilder *)setSubmitButtonText:(NSString *)submitButtonText;

/// @see `SCPNumericInput.toggles`
- (SCPNumericInputBuilder *)setToggles:(NSArray<SCPToggle *> *)toggles;

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
