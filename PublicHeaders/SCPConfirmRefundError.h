//
//  SCPConfirmRefundError.h
//  StripeTerminal
//
//  Created by James Little on 2/20/20.
//  Copyright © 2020 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPErrors.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPRefund;
@class SCPRefundParameters;

/**
 An error from `-[SCPTerminal confirmRefund:completion:]`.

 @see https://stripe.com/docs/terminal/canada#interac-refunds
 */
NS_SWIFT_NAME(ConfirmRefundError)
@interface SCPConfirmRefundError : NSError

/**
 If `confirmRefund` failed after the refund was created, this property contains
 the failing refund.

 @see https://stripe.com/docs/api/refunds/object
 */
@property (nonatomic, nullable, readonly) SCPRefund *refund;

/**
 If `confirmRefund` failed because the underlying network request errored,
 this property contains additional details about the error.
*/
@property (nonatomic, nullable, readonly) NSError *requestError;

/**
 You cannot directly instantiate this class.
 */
+ (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
