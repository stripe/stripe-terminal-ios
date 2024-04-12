//
//  SCPToggle.h
//  StripeTerminal
//
//  Created by Zak Hu on 2/20/24.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPInput.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The possible toggle default values
 */
typedef NS_ENUM(NSUInteger, SCPToggleValue) {
    /**
     Toggle is checked
     */
    SCPToggleValueEnabled,
    /**
     Toggle is unchecked
     */
    SCPToggleValueDisabled,
} NS_SWIFT_NAME(ToggleValue);

/**
 The possible toggle result values
 */
typedef NS_ENUM(NSUInteger, SCPToggleResult) {
    /**
     Toggle is checked
     */
    SCPToggleResultEnabled,
    /**
     Toggle is unchecked
     */
    SCPToggleResultDisabled,
    /**
     The form is skipped
     */
    SCPToggleResultSkipped,
} NS_SWIFT_NAME(ToggleResult);

/**
 Contains information about a Toggle to display as part of a form

 @see https://stripe.com/docs/terminal/features/collect-inputs
 */
NS_SWIFT_NAME(Toggle)
@interface SCPToggle : NSObject

/**
 Represents the toggle's title, the larger style text
 */
@property (nonatomic, nullable, readonly) NSString *title;

/**
 Represents the toggle's description, the smaller style text
 */
@property (nonatomic, nullable, readonly) NSString *stripeDescription;

/**
 Default state of the toggle when first being displayed
 */
@property (nonatomic, assign, readonly) SCPToggleValue defaultValue;

/**
 Use `SCPToggleBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPToggleBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder class for `SCPToggle`.
 */
NS_SWIFT_NAME(ToggleBuilder)
@interface SCPToggleBuilder : SCPBuilder <SCPToggle *>

/**
 Initializes a new instance of the `SCPToggleBuilder` class with the provided default value.
 */
- (instancetype)initWithDefaultValue:(SCPToggleValue)defaultValue NS_DESIGNATED_INITIALIZER;

/// @see `SCPToggle.title`
- (SCPToggleBuilder *)setTitle:(NSString *)title;

/// @see `SCPToggle.stripeDescription`
- (SCPToggleBuilder *)setStripeDescription:(NSString *)stripeDescription;

/// @see `SCPToggle.defaultValue`
- (SCPToggleBuilder *)setDefaultValue:(SCPToggleValue)defaultValue;

/**
 Use `initWithStyle`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithStyle`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
