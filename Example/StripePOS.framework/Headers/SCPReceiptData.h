//
//  SCPReceiptData.h
//  StripePOS
//
//  Created by Ben Guo on 6/21/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPJSONDecodable.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Receipt data for a card present transaction.
 */
@interface SCPReceiptData : NSObject <SCPJSONDecodable>

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
 Dedicated File Name
 */
@property (nonatomic, readonly) NSString *dedicatedFileName;

/**
 Application Preferred Name
 */
@property (nonatomic, readonly) NSString *applicationPreferredName;

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
 You cannot directly instantiate `SCPReceiptData`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPReceiptData`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
