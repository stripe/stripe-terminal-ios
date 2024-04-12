//
//  SCPSelectionResult.h
//  StripeTerminal
//
//  Created by Stephen Lee on 11/06/23.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//
#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPCollectInputsResult.h>
#import <StripeTerminal/SCPToggle.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains data collected from a Selection form

 @see https://stripe.com/docs/terminal/features/collect-inputs
 */
NS_SWIFT_NAME(SelectionResult)
@interface SCPSelectionResult : SCPCollectInputsResult

/**
 Represents the selected button. This value is nil if the form was skipped.
 */
@property (nonatomic, nullable, readonly) NSString *selection;

/**
 Represents the collected toggles, a list of SCPToggleResult. The value is SCPToggleResultSkipped if a form is skipped.
 */
@property (nonatomic, readonly, copy) NSArray<NSNumber *> *toggles;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
