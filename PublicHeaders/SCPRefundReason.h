//
//  SCPRefundReason.h
//  StripeTerminal
//
//  Created by Stripe on 9/11/26.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The reason for a refund.
 */
typedef NSString *SCPRefundReason NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(RefundReason);

/**
 The Refund was created because the charge was duplicated.
 */
FOUNDATION_EXPORT SCPRefundReason const SCPRefundReasonDuplicate;

/**
 The Refund was created because the charge was fraudulent.
 */
FOUNDATION_EXPORT SCPRefundReason const SCPRefundReasonFraudulent;

/**
 The Refund was requested by the customer.
 */
FOUNDATION_EXPORT SCPRefundReason const SCPRefundReasonRequestedByCustomer;

NS_ASSUME_NONNULL_END
