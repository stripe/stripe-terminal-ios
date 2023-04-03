//
//  SCPReceiptDetails.h
//  StripeTerminal
//
//  Created by Ben Guo on 6/21/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Receipt details associated with a card present transaction.

 @see https://stripe.com/docs/api/charges/object#charge_object-payment_method_details-card_present-receipt
 */
NS_SWIFT_NAME(ReceiptDetails)
@interface SCPReceiptDetails : NSObject <SCPJSONDecodable, NSCopying>

/**
 The type of account being debited or credited
 */
@property (nonatomic, nullable, readonly) NSString *accountType;

/**
 Also known as "Application Name". Required on EMV receipts.
 */
@property (nonatomic, readonly) NSString *applicationPreferredName;

/**
 Also known as "AID". Required on EMV receipts.
 */
@property (nonatomic, readonly) NSString *dedicatedFileName;

/**
 Identifier for this transaction
 */
@property (nonatomic, nullable, readonly) NSString *authorizationCode;

/**
 Authorization Response Code
 */
@property (nonatomic, readonly) NSString *authorizationResponseCode;

/**
 Application Cryptogram
 */
@property (nonatomic, readonly) NSString *applicationCryptogram;

/**
 TVR
 */
@property (nonatomic, readonly) NSString *terminalVerificationResults;

/**
 TSI
 */
@property (nonatomic, readonly) NSString *transactionStatusInformation;

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
