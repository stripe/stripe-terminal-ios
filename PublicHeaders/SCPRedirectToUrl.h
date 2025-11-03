//
//  SCPRedirectToUrl.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2025-08-29.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains instructions for redirecting the customer to another URL.
 */
NS_SWIFT_NAME(RedirectToUrl)
@interface SCPRedirectToUrl : NSObject <NSCopying>

/**
 The URL you must redirect your customer to in order to authenticate the payment.
 */
@property (nonatomic, nullable, readonly) NSString *url;

/**
 If the customer does not exit their browser while authenticating, they will be redirected to this specified URL after completion.
 */
@property (nonatomic, nullable, readonly) NSString *returnUrl;

/**
 You cannot directly instantiate `SCPRedirectToUrl`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPRedirectToUrl`. You should only use
 one that has been returned by our SDK.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
