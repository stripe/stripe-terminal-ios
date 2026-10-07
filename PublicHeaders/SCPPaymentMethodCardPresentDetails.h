//
//  SCPPaymentMethodCardPresentDetails.h
//  StripeTerminal
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPNetworks, SCPWallet;

/**
 Instrument details for a PaymentMethod of type `card_present` or
 `interac_present`.

 @see https://docs.stripe.com/api/payment_methods/object#payment_method_object-card_present
 */
NS_SWIFT_NAME(PaymentMethodCardPresentDetails)
@interface SCPPaymentMethodCardPresentDetails : NSObject

/**
 The issuing brand of the card.
 */
@property (nonatomic, copy, readonly) NSString *brand;

/**
 The product identifier for the card's brand.
 */
@property (nonatomic, copy, nullable, readonly) NSString *brandProduct;

/**
 The cardholder name as read from the card.
 */
@property (nonatomic, copy, nullable, readonly) NSString *cardholderName;

/**
 Two-letter ISO code representing the country of the card.
 */
@property (nonatomic, copy, nullable, readonly) NSString *country;

/**
 A high-level description of the type of cards issued in this range.
 */
@property (nonatomic, copy, nullable, readonly) NSString *stripeDescription;

/**
 The card's expiration month. 1-indexed (i.e. 1 == January).
 */
@property (nonatomic, copy, nullable, readonly) NSNumber *expMonth;

/**
 The card's expiration year.
 */
@property (nonatomic, copy, nullable, readonly) NSNumber *expYear;

/**
 The card's funding type.
 */
@property (nonatomic, copy, nullable, readonly) NSString *funding;

/**
 Issuer identification number of the card.
 */
@property (nonatomic, copy, nullable, readonly) NSString *iin;

/**
 The name of the card's issuing bank.
 */
@property (nonatomic, copy, nullable, readonly) NSString *issuer;

/**
 The last four digits of the card.
 */
@property (nonatomic, copy, nullable, readonly) NSString *last4;

/**
 Contains information about card networks that can be used to process the
 payment.
 */
@property (nonatomic, copy, nullable, readonly) SCPNetworks *networks;

/**
 EMV tag 5F2D. Preferred languages specified by the integrated circuit chip.
 */
@property (nonatomic, copy, nullable, readonly) NSArray<NSString *> *preferredLocales;

/**
 A unique identifier assigned by the card network to the underlying payment
 account. This value can identify the same account across a physical card and
 its wallet tokens.
 */
@property (nonatomic, copy, nullable, readonly) NSString *paymentAccountReference;

/**
 How the card details were read, using the value returned by the Stripe API
 (for example, `contact_emv` or `contactless_emv`).
 */
@property (nonatomic, copy, readonly) NSString *readMethod;

/**
 If this PaymentMethod is from a card wallet, this contains the wallet details.
 */
@property (nonatomic, nullable, readonly) SCPWallet *wallet;

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
