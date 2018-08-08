//
//  SCPCharge.h
//  StripePOS
//
//  Created by Ben Guo on 7/27/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import "SCPJSONDecodable.h"

NS_ASSUME_NONNULL_BEGIN

/**
 The possible statuses for a charge
 */
typedef NS_ENUM(NSUInteger, SCPChargeStatus) {
    /**
     The charge succeeded.
     */
    SCPChargeStatusSucceeded,
    /**
     The charge succeeded.
     */
    SCPChargeStatusPending,
    /**
     The charge failed.
     */
    SCPChargeStatusFailed,
};

@class SCPCardPresentSource;

/**
 An object representing a Stripe charge.

 @see https://stripe.com/docs/api#charges
 */
@interface SCPCharge : NSObject <SCPJSONDecodable>

/**
 The amount of the charge.
 */
@property (nonatomic, readonly) NSUInteger amount;

/**
 The currency of the charge.
 */
@property (nonatomic, readonly) NSString *currency;

/**
 The status of the charge.
 */
@property (nonatomic, readonly) SCPChargeStatus status;

/**
 The card present source associated with the charge.
 */
@property (nonatomic, nullable, readonly) SCPCardPresentSource *cardPresentSource;

/**
 A string describing the charge, displayed in the Stripe dashboard and in
 email receipts.
 */
@property (nonatomic, nullable, readonly) NSString *stripeDescription;

/**
 Metadata associated with the charge.
 */
@property (nonatomic, readonly) NSDictionary *metadata;

/**
 The email that the receipt for this charge was sent to.
 */
@property (nonatomic, nullable, readonly) NSString *receiptEmail;

/**
 The statement descriptor for the charge.
 */
@property (nonatomic, nullable, readonly) NSString *statementDescriptor;

/**
 The unique identifier for the charge.
 */
@property (nonatomic, readonly) NSString *stripeId;

/**
 Use stripeDescription for the string attached to the charge object.
 */
@property (nonatomic, copy, readonly) NSString *description DEPRECATED_MSG_ATTRIBUTE("Did you mean to use stripeDescription?");

/**
 You cannot directly instantiate `SCPCharge`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPCharge`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
