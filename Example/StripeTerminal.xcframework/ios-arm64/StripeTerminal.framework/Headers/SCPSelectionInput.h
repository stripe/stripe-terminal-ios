//
//  SCPSelectionInput.h
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
#import <StripeTerminal/SCPSelectionButton.h>
#import <StripeTerminal/SCPToggle.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains information about a Selection form to display on the reader

 @see https://stripe.com/docs/terminal/features/collect-inputs
 */
NS_SWIFT_NAME(SelectionInput)
@interface SCPSelectionInput : SCPInput

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
 Represents the selection buttons
 */
@property (nonatomic, readonly, copy) NSArray<SCPSelectionButton *> *selectionButtons;

/**
 Represents the toggles
 */
@property (nonatomic, readonly, copy) NSArray<SCPToggle *> *toggles;

/**
 Use `SCPSelectionInputBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPSelectionInputBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder class for `SCPSelectionInput`.
 */
NS_SWIFT_NAME(SelectionInputBuilder)
@interface SCPSelectionInputBuilder : SCPBuilder <SCPSelectionInput *>

/**
 Initializes a new instance of the `SCPSelectionInputBuilder` class with the provided
 title.
 */
- (instancetype)initWithTitle:(NSString *)title NS_DESIGNATED_INITIALIZER;

/// @see `SCPSelectionInput.title`
- (SCPSelectionInputBuilder *)setTitle:(NSString *)title;

/// @see `SCPSelectionInput.required`
- (SCPSelectionInputBuilder *)setRequired:(BOOL)required;

/// @see `SCPSelectionInput.stripeDescription`
- (SCPSelectionInputBuilder *)setStripeDescription:(NSString *)stripeDescription;

/// @see `SCPSelectionInput.skipButton`
- (SCPSelectionInputBuilder *)setSkipButtonText:(NSString *)skipButtonText;

/// @see `SCPSelectionInput.selectionButtons`
- (SCPSelectionInputBuilder *)setSelectionButtons:(NSArray<SCPSelectionButton *> *)selectionButton;

/// @see `SCPSelectionInput.toggles`
- (SCPSelectionInputBuilder *)setToggles:(NSArray<SCPToggle *> *)toggles;

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
