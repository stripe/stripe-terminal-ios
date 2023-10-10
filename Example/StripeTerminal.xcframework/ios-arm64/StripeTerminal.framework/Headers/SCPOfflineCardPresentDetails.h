//
//  SCPOfflineCardPresentDetails.h
//  StripeTerminal
//
//  Created by Mindy Lou on 8/21/23.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPCardBrand.h>
#import <StripeTerminal/SCPReadMethod.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPReceiptDetails;

/**
 Contains details about the payment method used to process a PaymentIntent offline.
 */
NS_SWIFT_NAME(OfflineCardPresentDetails)
@interface SCPOfflineCardPresentDetails : NSObject <NSCopying>

/**
 The issuer of the card. In some cases, the brand may not be available until
 the PaymentIntent is forwarded to Stripe.
 */
@property (nonatomic, readonly, assign) SCPCardBrand brand;

/**
 Two-digit number representing the card’s expiration month.
 0 if the expiration month was missing.
 */
@property (nonatomic, readonly, assign) NSInteger expMonth;

/**
 Four-digit number representing the card’s expiration year.
 0 if the expiration year was missing.
 */
@property (nonatomic, readonly, assign) NSInteger expYear;

/**
 The last four digits of the card.
 */
@property (nonatomic, nullable, readonly) NSString *last4;

/**
 How the card was read in this transaction.
 */
@property (nonatomic, readonly, assign) SCPReadMethod readMethod;

/**
 The cardholder name as read from the card, in ISO 7813 format. May include
 alphanumeric characters, special characters and first/last name separator (/).
 In some cases, the cardholder name may not be available depending on how the
 issuer has configured the card. Cardholder name is typically not available on
 swipe or contactless payments.
 */
@property (nonatomic, nullable, readonly) NSString *cardholderName;

/**
 The receipt details read from the card during the offline transaction.
 */
@property (nonatomic, nullable, readonly, strong) SCPReceiptDetails *receiptDetails;

/**
 You cannot directly instantiate `SCPOfflineCardPresentDetails`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPOfflineCardPresentDetails`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
