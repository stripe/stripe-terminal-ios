//
//  SCPOfflineDetails.h
//  StripeTerminal
//
//  Created by Brian Cooke on 12/13/21.
//  Copyright © 2021 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPAmountDetails;
@class SCPOfflineCardPresentDetails;

/**
 The payment details available via intent.offlineDetails when a payment is created
 or confirmed while offline.

 When an intent is created offline, the intent.stripeId will be nil. To keep track of
 offline payments, we recommend using the intent.metadata with your own identifiers.
 */
NS_SWIFT_NAME(OfflineDetails)
@interface SCPOfflineDetails : NSObject <NSCopying>

/**
 Time that the payment was collected.
 */
@property (nonatomic, nullable, readonly, strong) NSDate *collectedAt;

/**
 Set to `YES` if the PaymentIntent needs to be uploaded. The payment intent can be optionally captured after it is uploaded.
 */
@property (nonatomic, readwrite) BOOL requiresUpload;

/**
 The amount details read during collection. Includes tip.
 */
@property (nonatomic, nullable, readonly, strong) SCPAmountDetails *amountDetails;

/**
 Details about the card-present payment method used to process this PaymentIntent.
 */
@property (nonatomic, nullable, readonly, strong) SCPOfflineCardPresentDetails *cardPresentDetails;

@end

NS_ASSUME_NONNULL_END
