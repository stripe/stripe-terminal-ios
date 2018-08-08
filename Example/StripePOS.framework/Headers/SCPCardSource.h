//
//  SCPCardSource.h
//  StripePOS
//
//  Created by Ben Guo on 2/22/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPCardBrand.h"
#import "SCPCardFundingType.h"
#import "SCPJSONDecodable.h"

NS_ASSUME_NONNULL_BEGIN

/**
 An object representing a card source.
 */
@interface SCPCardSource : NSObject <SCPJSONDecodable>

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
 Two-letter ISO code representing the issuing country of the card.
 */
@property (nonatomic, nullable, readonly) NSString *country;

/**
 You cannot directly instantiate `SCPCardSource`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPCardSource`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
