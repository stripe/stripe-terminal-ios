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

#import <StripeTerminal/SCPCardBrand.h>
#import <StripeTerminal/SCPCardFundingType.h>
#import <StripeTerminal/SCPJSONDecodable.h>
#import <StripeTerminal/SCPReadMethod.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPReceiptDetails, SCPNetworks;
@class SCPWallet;

/**
 Represents the ability for a PaymentIntent to be incrementally authorized.

 @see https://stripe.com/docs/terminal/features/incremental-authorizations
 */
typedef NS_ENUM(NSUInteger, SCPIncrementalAuthorizationStatus) {
    /**
     It is undetermined whether or not this `PaymentIntent` will be eligible for incremental authorizations.
     You can only perform incremental authorizations on uncaptured payments after confirmation.
     */
    SCPIncrementalAuthorizationStatusUnknown,

    /**
     This PaymentIntent is not eligible for incremental authorizations, or it was not requested.
     */
    SCPIncrementalAuthorizationStatusNotSupported,

    /**
     This PaymentIntent is eligible for incremental authorizations.
     */
    SCPIncrementalAuthorizationStatusSupported,
};

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
 The cardholder name as read from the card, in ISO 7813 format. May include
 alphanumeric characters, special characters and first/last name separator (/).
 */
@property (nonatomic, nullable, readonly) NSString *cardholderName;

/**
 The card's funding type.
 */
@property (nonatomic, readonly) SCPCardFundingType funding;

/**
 The issuing brand of the card.
 */
@property (nonatomic, readonly) SCPCardBrand brand;

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
 Two-letter ISO code representing the country of the card. You could use this
 attribute to get a sense of the international breakdown of cards you’ve collected.

 Only available for interac_present payments.
 */
@property (nonatomic, copy, nullable, readonly) NSString *country;

/**
 EMV tag 5F2D. Preferred languages specified by the integrated circuit chip.

 Only available for interac_present payments.
 */
@property (nonatomic, copy, nullable, readonly) NSArray<NSString *> *preferredLocales;

/**
 Contains information about card networks that can be used to process the payment.

 Only available after collectPaymentMethod when using updatePaymentIntent on the CollectConfiguration.
 */
@property (nonatomic, copy, nullable, readonly) SCPNetworks *networks;

/**
 Identifies which network this charge was processed on.

 Contains SCPCardBrand represented as a nullable NSNumber.

 Only available after confirming the PaymentIntent.
 */
@property (nonatomic, copy, nullable, readonly) NSNumber *network;

/**
 * Whether this payment method is eligible for incremental authorizations.
 *
 * Note: This is only known if the PaymentIntent was confirmed.
 */
@property (nonatomic, assign, readonly) SCPIncrementalAuthorizationStatus incrementalAuthorizationStatus;

/**
 How the card was read in this transaction.
 */
@property (nonatomic, readonly, assign) SCPReadMethod readMethod;

/**
 If this payment is from a card wallet, this contains the details of the card wallet.
 */
@property (nonatomic, nullable, readonly) SCPWallet *wallet;

/**
 Issuer identification number of the card. (For internal use only and not typically available
 in standard API requests.)
 */
@property (nonatomic, copy, nullable, readonly) NSString *iin;

/**
 The name of the card's issuing bank. (For internal use only and not typically available in
 standard API requests.)
 */
@property (nonatomic, copy, nullable, readonly) NSString *issuer;

/**
 * A high-level description of the type of cards issued in this range. (For internal use only
 * and not typically available in standard API requests.)
 */
@property (nonatomic, copy, nullable, readonly) NSString *stripeDescription;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
