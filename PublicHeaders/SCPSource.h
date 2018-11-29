//
//  SCPSource.h
//  StripeTerminal
//
//  Created by Ben Guo on 9/17/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPJSONDecodable.h"

NS_ASSUME_NONNULL_BEGIN

/**
 An abstract class representing a Stripe Source object.

 @see https://stripe.com/docs/sources
 */
@interface SCPSource : NSObject <SCPJSONDecodable>

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
