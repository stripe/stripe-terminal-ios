//
//  SCPCardPresentSource.h
//  StripeTerminal
//
//  Created by Ben Guo on 1/4/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPCardBrand.h"
#import "SCPCardFundingType.h"
#import "SCPSource.h"

NS_ASSUME_NONNULL_BEGIN

@class SCPReceiptData;

/**
 An object representing a card present source.

 @see https://stripe.com/docs/sources
 */
NS_SWIFT_NAME(CardPresentSource)
@interface SCPCardPresentSource : SCPSource <SCPJSONDecodable>

/**
 The unique identifier for the source.
 */
@property (nonatomic, readonly) NSString *stripeId;

/**
 The last 4 digits of the card.
 */
@property (nonatomic, readonly) NSString *last4;

/**
 The card's expiration month. 1-indexed (i.e. 1 == January)
 */
@property (nonatomic, readonly) NSUInteger expMonth;

/**
 The card's expiration year.
 */
@property (nonatomic, readonly) NSUInteger expYear;

/**
 The card's funding type.
 */
@property (nonatomic, readonly) SCPCardFundingType funding;

/**
 The cardholder's name.
 */
@property (nonatomic, nullable, readonly) NSString *name;

/**
 The issuing brand of the card.
 */
@property (nonatomic, readonly) SCPCardBrand brand;

/**
 A string uniquely identifying this card number.
 */
@property (nonatomic, readonly) NSString *fingerprint;

/**
 The receipt data for the card present transaction.
 */
@property (nonatomic, readonly) SCPReceiptData *receiptData;

/**
 Set of key-value pairs attached to the object.
 */
@property (nonatomic, nullable, readonly) NSDictionary *metadata;

/**
 (Only applicable to EMV payments) The authorization data from the card
 issuer.
 */
@property (nonatomic, nullable, readonly) NSString *emvAuthData;

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
