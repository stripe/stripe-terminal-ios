//
//  SCPReaderSettings.h
//  StripeTerminal
//
//  Created by Max Afonov on 12/6/23.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <StripeTerminal/SCPReaderAccessibility.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Class representing the current settings of the reader.
 */
NS_SWIFT_NAME(ReaderSettings)
@interface SCPReaderSettings : NSObject

/**
 Accessibility status of the reader.
 */
@property (nonatomic, readonly) SCPReaderAccessibility *accessibility;

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
