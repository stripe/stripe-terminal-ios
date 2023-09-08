//
//  SCPCardDetails.h
//  StripeTerminal
//
//  Created by Daniel Jackson on 4/10/19.
//  Copyright © 2019 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPCardBrand.h>
#import <StripeTerminal/SCPCardFundingType.h>
#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains details about a user's credit card.

 @see https://stripe.com/docs/api/payment_methods/object#payment_method_object-card
 */
NS_SWIFT_NAME(CardDetails)
@interface SCPCardDetails : NSObject <SCPJSONDecodable>

/**
 The issuer of the card.
 */
@property (nonatomic, readonly) SCPCardBrand brand;

/**
 Two-letter ISO code representing the country of the card.
 */
@property (nonatomic, nullable, readonly) NSString *country;

/**
 Two-digit number representing the card’s expiration month.
 0 if the expiration month was missing.
 */
@property (nonatomic, readonly) NSInteger expMonth;

/**
 Four-digit number representing the card’s expiration year.
 0 if the expiration year was missing.
 */
@property (nonatomic, readonly) NSInteger expYear;

/**
 Card funding type. Ex: credit, debit, etc.
 */
@property (nonatomic, readonly) SCPCardFundingType funding;

/**
 The last four digits of the card.
 */
@property (nonatomic, nullable, readonly) NSString *last4;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
