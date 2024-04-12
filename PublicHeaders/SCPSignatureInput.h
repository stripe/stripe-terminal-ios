//
//  SCPSignatureInput.h
//  StripeTerminal
//
//  Created by Stephen Lee on 10/20/23.
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
 Contains information about a signature form to display on the reader

 @see https://stripe.com/docs/terminal/features/collect-inputs
 */
NS_SWIFT_NAME(SignatureInput)
@interface SCPSignatureInput : SCPInput

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
 Use `SCPSignatureInputBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPSignatureInputBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder class for `SCPSignatureInput`.
 */
NS_SWIFT_NAME(SignatureInputBuilder)
@interface SCPSignatureInputBuilder : SCPBuilder <SCPSignatureInput *>

/**
 Initializes a new instance of the `SCPSignatureInputBuilder` class with the provided
 title.
 */
- (instancetype)initWithTitle:(NSString *)title NS_DESIGNATED_INITIALIZER;

/// @see `SCPSignatureInput.title`
- (SCPSignatureInputBuilder *)setTitle:(NSString *)title;

/// @see `SCPSignatureInput.required`
- (SCPSignatureInputBuilder *)setRequired:(BOOL)required;

/// @see `SCPSignatureInput.stripeDescription`
- (SCPSignatureInputBuilder *)setStripeDescription:(NSString *)stripeDescription;

/// @see `SCPSignatureInput.skipButton`
- (SCPSignatureInputBuilder *)setSkipButtonText:(NSString *)skipButtonText;

/// @see `SCPSignatureInput.submitButton`
- (SCPSignatureInputBuilder *)setSubmitButtonText:(NSString *)submitButtonText;

/// @see `SCPSignatureInput.toggles`
- (SCPSignatureInputBuilder *)setToggles:(NSArray<SCPToggle *> *)toggles;

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
