//
//  SCPDynamicCurrencyConversion.h
//  StripeTerminal
//
//  Created by Henry Xu on 10/1/24.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An object representing the dynamic currency conversion details for a transaction.

 @see https://docs.corp.stripe.com/api/charges/object#charge_object-payment_method_details-card_present-dynamic_currency_conversion
 */
NS_SWIFT_NAME(DynamicCurrencyConversion)
@interface SCPDynamicCurrencyConversion : NSObject <SCPJSONDecodable, NSCopying>

/**
 Exchange rate received by the cardholder, including markup.
 */
@property (nonatomic, nullable, readonly) NSNumber *cardholderRate;

/**
 Time at which the provided exchange rates were determined.
 */
@property (nonatomic, nullable, readonly) NSDate *fxAsOf;

/**
 Amount in the original currency before conversion.
 */
@property (nonatomic, readonly) NSUInteger originalAmount;

/**
 Original currency before conversion.
 */
@property (nonatomic, nullable, readonly) NSString *originalCurrency;

/**
 Reference exchange rate published by a regulatory body for cardholder disclosure.
 Present only for transactions where the merchant and cardholder are both in the European Economic Area (EEA).
 */
@property (nonatomic, nullable, readonly) NSNumber *referenceFxRate;

/**
 Markup percentage added to the reference_fx_rate to get the cardholder_rate.
 Used for cardholder disclosure and present only for transactions where the merchant and cardholder are both in the European Economic Area (EEA).
 */
@property (nonatomic, nullable, readonly) NSNumber *referenceMarkupPercent;

/**
 Whether dynamic currency conversion was performed on this transaction.
 */
@property (nonatomic, readonly) NSString *status;

/**
 Exchange rate applied to the transaction, excluding markup.
 */
@property (nonatomic, nullable, readonly) NSNumber *transactionFxRate;

/**
 Markup percentage added to the transaction_fx_rate to get the cardholder_rate.
 */
@property (nonatomic, nullable, readonly) NSNumber *transactionMarkupPercent;

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
