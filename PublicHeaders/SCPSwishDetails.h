//
//  SCPSwishDetails.h
//  StripeTerminal
//
//  Created by yanayuan on 9/10/26.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains details about a user's Swish payment.

 @see https://stripe.com/docs/api/payment_methods/object#payment_method_object-swish
 */
NS_SWIFT_NAME(SwishDetails)
@interface SCPSwishDetails : NSObject

/**
 ID of the location that this transaction's reader is assigned to.
 */
@property (nonatomic, nullable, readonly) NSString *location;

/**
 ID of the reader this transaction was made on.
 */
@property (nonatomic, nullable, readonly) NSString *reader;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
