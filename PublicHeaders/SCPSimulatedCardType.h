//
//  SCPSimulatedCardType.h
//  StripeTerminal
//
//  Created by Catriona Scott on 2/17/21.
//  Copyright © 2021 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Enum used to simulate various types of cards and error cases.

 @see https://stripe.com/docs/terminal/testing#simulated-test-cards
 */
typedef NS_ENUM(NSUInteger, SCPSimulatedCardType) {
    /// Visa
    SCPSimulatedCardTypeVisa = 0,

    /// Visa (debit)
    SCPSimulatedCardTypeVisaDebit,

    /// Mastercard
    SCPSimulatedCardTypeMastercard,

    /// Mastercard (debit)
    SCPSimulatedCardTypeMasterDebit,

    /// Mastercard (prepaid)
    SCPSimulatedCardTypeMastercardPrepaid,

    /// American Express
    SCPSimulatedCardTypeAmex,

    /// American Express
    SCPSimulatedCardTypeAmex2,

    /// Discover
    SCPSimulatedCardTypeDiscover,

    /// Discover
    SCPSimulatedCardTypeDiscover2,

    /// Diners Club
    SCPSimulatedCardTypeDiners,

    /// Diners Club (14 digit card)
    SCPSimulatedCardTypeDiners14Digit,

    /// JCB
    SCPSimulatedCardTypeJcb,

    /// UnionPay
    SCPSimulatedCardTypeUnionPay,

    /// Interac
    SCPSimulatedCardTypeInterac,

    /// Charge is declined with a card_declined code.
    SCPSimulatedCardTypeChargeDeclined,

    /// Charge is declined with a card_declined code. The decline_code
    /// attribute is insufficient_funds.
    SCPSimulatedCardTypeChargeDeclinedInsufficientFunds,

    /// Charge is declined with a card_declined code. The decline_code
    /// attribute is lost_card.
    SCPSimulatedCardTypeChargeDeclinedLostCard,

    /// Charge is declined with a card_declined code. The decline_code
    /// attribute is stolen_card.
    SCPSimulatedCardTypeChargeDeclinedStolenCard,

    /// Charge is declined with an expired_card code.
    SCPSimulatedCardTypeChargeDeclinedExpiredCard,

    /// Charge is declined with a processing_error code.
    SCPSimulatedCardTypeChargeDeclinedProcessingError,

    /// Refund is declined with a refund_fail error.
    SCPSimulatedCardTypeRefundFailed

} NS_SWIFT_NAME(SimulatedCardType);

NS_ASSUME_NONNULL_END
