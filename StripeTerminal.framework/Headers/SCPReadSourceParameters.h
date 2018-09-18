//
//  SCPReadSourceParameters.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/11/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Parameters for reading a source.
 */
NS_SWIFT_NAME(ReadSourceParameters)
@interface SCPReadSourceParameters : NSObject

/**
 To create the source on a conected account, set this property to the ID of the
 account for which the request is being made. The default is nil.
 
 @see https://stripe.com/docs/connect/authentication#authentication-via-the-stripe-account-header
 */
@property (nonatomic, copy, nullable, readwrite) NSString *stripeAccount;

@end

NS_ASSUME_NONNULL_END
