//
//  SCPReceiptData.h
//  StripeTerminal
//
//  Created by Ben Guo on 6/21/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPJSONDecodable.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Receipt data associated with a CardPresentSource.
 */
NS_SWIFT_NAME(ReceiptData)
@interface SCPReceiptData : NSObject <SCPJSONDecodable>

/**
 Also known as "Application Name". Required on EMV receipts.
 */
@property (nonatomic, readonly) NSString *applicationPreferredName;

/**
 Also known as "AID". Required on EMV receipts.
 */
@property (nonatomic, readonly) NSString *dedicatedFileName;

/**
 Merchant Identification Number
 */
@property (nonatomic, readonly) NSString *mid;

/**
 Terminal Identification Number
 */
@property (nonatomic, readonly) NSString *tid;

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
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
