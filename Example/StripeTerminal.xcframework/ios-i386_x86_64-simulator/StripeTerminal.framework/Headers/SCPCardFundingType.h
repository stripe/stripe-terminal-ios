//
//  SCPCardFunding.h
//  StripeTerminal
//
//  Created by Ben Guo on 3/5/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The various funding sources for a card.

 @see https://stripe.com/docs/api/cards/object#card_object-funding
 */
typedef NS_ENUM(NSInteger, SCPCardFundingType) {
    /**
     Debit
     */
    SCPCardFundingTypeDebit,

    /**
     Credit
     */
    SCPCardFundingTypeCredit,

    /**
     Prepaid
     */
    SCPCardFundingTypePrepaid,

    /**
     An other or unknown type of funding source
     */
    SCPCardFundingTypeOther,
} NS_SWIFT_NAME(CardFundingType);

NS_ASSUME_NONNULL_END
