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

    /// Visa debit supporting both international and US Common Debit applications
    SCPSimulatedCardTypeVisaUsCommonDebit,

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

    /// Eftpos Australia
    SCPSimulatedCardTypeEftposAuDebit,

    /// Eftpos Australia/Visa
    SCPSimulatedCardTypeEftposAuVisaDebit,

    /// Eftpos Australia/Mastercard
    SCPSimulatedCardTypeEftposAuDebitMastercard,

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
    SCPSimulatedCardTypeRefundFailed,

    /// Payment attaches Online Pin to the transaction.
    /// cardholder_verification_method will be set to online_pin in the resulting paymentIntent
    /// WisePad3 only
    SCPSimulatedCardTypeOnlinePinCvm,

    /// This flow simulates an Online Pin scenario with SCA compliance.
    /// Payment is retried and user is prompted to input their pin.
    /// Next an online pin being entered is simulated.
    ///
    /// cardholder_verification_method will be set to online_pin in the resulting paymentIntent.
    /// WisePad3 only
    SCPSimulatedCardTypeOnlinePinScaRetry,

    /// Payment attaches Offline Pin to the transaction.
    /// cardholder_verification_method will be set to offline_pin in the resulting paymentIntent
    /// WisePad3 only
    SCPSimulatedCardTypeOfflinePinCvm,

    /// This flow simulates an Offline Pin scenario with SCA compliance.
    /// Payment is retried and user is prompted to insert their card.
    /// Next a contact retry and an offline pin being entered are simulated.
    ///
    /// cardholder_verification_method will be set to offline_pin in the resulting paymentIntent.
    /// WisePad3 only
    SCPSimulatedCardTypeOfflinePinScaRetry,

} NS_SWIFT_NAME(SimulatedCardType);

NS_ASSUME_NONNULL_END
