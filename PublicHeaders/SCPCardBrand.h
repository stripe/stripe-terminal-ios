//
//  SCPCardBrand.h
//  StripeTerminal
//
//  Created by Ben Guo on 2/22/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The various card brands for a card.

 @see https://stripe.com/docs/api/cards/object#card_object-brand
 */
typedef NS_ENUM(NSInteger, SCPCardBrand) {
    /**
     Visa card
     */
    SCPCardBrandVisa,

    /**
     American Express card
     */
    SCPCardBrandAmex,

    /**
     MasterCard card
     */
    SCPCardBrandMasterCard,

    /**
     Discover card
     */
    SCPCardBrandDiscover,

    /**
     JCB card
     */
    SCPCardBrandJCB,

    /**
     Diners Club card
     */
    SCPCardBrandDinersClub,

    /**
     An unknown card brand
     */
    SCPCardBrandUnknown,
} NS_SWIFT_NAME(CardBrand);

NS_ASSUME_NONNULL_END
