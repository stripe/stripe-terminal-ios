//
//  SCPCardPresentDetails.h
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
#import "SCPJSONDecodable.h"

NS_ASSUME_NONNULL_BEGIN

@class SCPReceiptDetails;

/**
 An object representing details from a transaction using a card_present
 payment method.

 @see https://stripe.com/docs/api/charges/object#charge_object-payment_method_details-card_present
 */
NS_SWIFT_NAME(CardPresentDetails)
@interface SCPCardPresentDetails : NSObject <SCPJSONDecodable>

/**
 The last 4 digits of the card.
 */
@property (nonatomic, readonly) NSString *last4;

/**
 The card's expiration month. 1-indexed (i.e. 1 == January)
 */
@property (nonatomic, readonly) NSInteger expMonth;

/**
 The card's expiration year.
 */
@property (nonatomic, readonly) NSInteger expYear;

/**
 The card's funding type.
 */
@property (nonatomic, readonly) SCPCardFundingType funding;

/**
 The issuing brand of the card.
 */
@property (nonatomic, readonly) SCPCardBrand brand;

/**
 A string uniquely identifying this card number.
 */
@property (nonatomic, readonly) NSString *fingerprint;

/**
 ID of a `card` PaymentMethod that may be attached to a Customer for future
 transactions. Only present if it was possible to generate a `card`
 PaymentMethod.

 @see https://stripe.com/docs/terminal/payments/saving-cards#saving-payment-intent-card
 */
@property (nonatomic, nullable, readonly) NSString *generatedCard;

/**
 Receipt information for the card present transaction. Only present for EMV
 transactions.
 */
@property (nonatomic, nullable, readonly) SCPReceiptDetails *receipt;

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
