//
//  SCPRefundNextAction.h
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
 Details about an email containing refund instructions.
 */
NS_SWIFT_NAME(RefundNextActionDisplayDetailsEmailSent)
@interface SCPRefundNextActionDisplayDetailsEmailSent : NSObject <NSCopying>

/**
 The time when the email was sent.
 */
@property (nonatomic, nullable, readonly) NSDate *emailSentAt;

/**
 The email address to which the instructions were sent.
 */
@property (nonatomic, nullable, copy, readonly) NSString *emailSentTo;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Details to display while a Refund requires additional action.
 */
NS_SWIFT_NAME(RefundNextActionDisplayDetails)
@interface SCPRefundNextActionDisplayDetails : NSObject <NSCopying>

/**
 Information about the refund-instructions email.
 */
@property (nonatomic, nullable, readonly) SCPRefundNextActionDisplayDetailsEmailSent *emailSent;

/**
 The time when the refund instructions expire.
 */
@property (nonatomic, nullable, readonly) NSDate *expiresAt;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Describes an action required to continue processing a Refund.

 @see https://docs.stripe.com/api/refunds/object#refund_object-next_action
 */
NS_SWIFT_NAME(RefundNextAction)
@interface SCPRefundNextAction : NSObject <NSCopying>

/**
 The type of action required.
 */
@property (nonatomic, nullable, copy, readonly) NSString *type;

/**
 Details that should be displayed to the customer.
 */
@property (nonatomic, nullable, readonly) SCPRefundNextActionDisplayDetails *displayDetails;

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
