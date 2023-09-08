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

#ifdef SCP_OFFLINE_MODE

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPReceiptDetails;
@class SCPAmountDetails;

/**
 The payment details available via intent.offlineDetails when a payment is created
 or confirmed while offline.

 When an intent is created offline, the intent.stripeId will be nil. Use the
 intent.offlineDetails.stripeId as the unique identifier for this transaction.
 */
NS_SWIFT_NAME(OfflineDetails)
@interface SCPOfflineDetails : NSObject <NSCopying>

/**
 The unique identifier for this offline transaction.
 */
@property (nonatomic, readonly, strong) NSString *stripeId;

/**
 Time that the payment was collected.
 */
@property (nonatomic, nullable, readonly, strong) NSDate *collectedAt;

/**
 Set to `YES` if the PaymentIntent needs to be uploaded. The payment intent can be optionally captured after it is uploaded.
 */
@property (nonatomic, readwrite) BOOL requiresUpload;

/**
 The receipt details read from the card during the offline transaction.
 */
@property (nonatomic, nullable, readonly, strong) SCPReceiptDetails *receiptDetails;

/**
 The amount details read during collection. Includes tip
 */
@property (nonatomic, nullable, readonly, strong) SCPAmountDetails *amountDetails;

@end

NS_ASSUME_NONNULL_END

#endif // SCP_OFFLINE_MODE
