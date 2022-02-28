//
//  SCPCollectConfiguration.h
//  StripeTerminal
//
//  Created by Matthew Krager on 2/1/22.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The `CollectConfiguration` contains configuration information relevant to collecting a payment
 * method.
 */
NS_SWIFT_NAME(CollectConfiguration)
@interface SCPCollectConfiguration : NSObject

/**
 Bypass tipping selection if it would have otherwise been shown.
 You must be a part of the on-reader tipping beta for this to take effect.

 @see https://stripe.com/docs/terminal/features/collecting-tips/on-reader
*/
@property (nonatomic, assign) BOOL skipTipping;

/**
 Initialize a CollectConfiguration

 @param skipTipping Bypass tipping selection if it would have otherwise been shown.
 */
- (instancetype)initWithSkipTipping:(BOOL)skipTipping;

/**
 Use `initWithSkipTipping:skipTipping:`
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
