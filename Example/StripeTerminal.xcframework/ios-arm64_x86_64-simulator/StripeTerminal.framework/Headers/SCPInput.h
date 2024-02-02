//
//  SCPInput.h
//  StripeTerminal
//
//  Created by Stephen Lee on 2023-10-20.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Represents a single input form
 */
NS_SWIFT_NAME(Input)
@interface SCPInput : NSObject

/**
 If YES, the skip button won't be displayed on the input form.

 Defaults to NO.
 */
@property (nonatomic, readonly) BOOL required;

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
