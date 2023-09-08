//
//  SCPBuilder.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2023-08-14.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Base class for all builders. Defines the `build` method that all builders must implement.
 */
@interface SCPBuilder<__covariant T> : NSObject

/**
 @param error Error out-parameter in the `SCPErrorDomain`.
 @return A new instance of the object with the attributes set.
   If any fields are invalid, returns `nil` and populates the reason in the `error` out-parameter.
 */
- (nullable T)build:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
