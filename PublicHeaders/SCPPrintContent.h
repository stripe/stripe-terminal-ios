//
//  SCPPrintContent.h
//  StripeTerminal
//
//  Created by Philip Zhang on 6/16/25.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Content for a print operation.
 */
NS_SWIFT_NAME(PrintContent)
@interface SCPPrintContent : NSObject

/**
 The image to be printed.
 */
@property (nonatomic, readonly) UIImage *image;

/**
 Use `SCPPrintContentBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPPrintContentBuilder`.
*/
+ (instancetype)new NS_UNAVAILABLE;
@end

/**
 A builder class for `SCPPrintContent`
 */
NS_SWIFT_NAME(PrintContentBuilder)
@interface SCPPrintContentBuilder : SCPBuilder <SCPPrintContent *>

/**
 Initializes a new instance of the `SCPPrintContentBuilder` class with the provided image.
 */
- (instancetype)initWithImage:(UIImage *)image;

/**
 @see `SCPPrintContent.image`
 */
- (SCPPrintContentBuilder *)setImage:(UIImage *)image;

/**
 Use `initWithImage`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithImage`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
