//
//  SCPSelectionButton.h
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

NS_ASSUME_NONNULL_BEGIN

/**
 The possible selection button styles
 */
typedef NS_ENUM(NSUInteger, SCPSelectionButtonStyle) {
    /**
     Button will use a highlighted accent color
     */
    SCPSelectionButtonStylePrimary,
    /**
     Button will use a subdued secondary color
     */
    SCPSelectionButtonStyleSecondary,
} NS_SWIFT_NAME(SelectionButtonStyle);

/**
 Contains information about a Selection form to display on the reader

 @see https://stripe.com/docs/terminal/features/collect-inputs
 */
NS_SWIFT_NAME(SelectionButton)
@interface SCPSelectionButton : NSObject

/**
 Style of a selection form button
 */
@property (nonatomic, assign, readonly) SCPSelectionButtonStyle style;

/**
 Represents the text on the button
 */
@property (nonatomic, readonly) NSString *text;

/**
 Use `SCPSelectionButtonBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPSelectionButtonBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Builder class for `SCPSelectionButton`.
 */
NS_SWIFT_NAME(SelectionButtonBuilder)
@interface SCPSelectionButtonBuilder : SCPBuilder <SCPSelectionButton *>

/**
 Initializes a new instance of the `SCPSelectionButtonBuilder` class with the provided
 title.
 */
- (instancetype)initWithStyle:(SCPSelectionButtonStyle)style
                         text:(NSString *)text NS_DESIGNATED_INITIALIZER;

/// @see `SCPSelectionButton.style`
- (SCPSelectionButtonBuilder *)setStyle:(SCPSelectionButtonStyle)style;

/// @see `SCPSelectionButton.text`
- (SCPSelectionButtonBuilder *)setText:(NSString *)text;

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
