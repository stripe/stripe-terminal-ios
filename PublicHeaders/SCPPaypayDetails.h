//
//  SCPPaypayDetails.h
//  StripeTerminal
//
//  Created by Ryan Rose on 8/26/25.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains details about a user's PayPay payment

 @see https://stripe.com/docs/api/payment_methods/object#payment_method_object-paypay
 */
NS_SWIFT_NAME(PaypayDetails)
@interface SCPPaypayDetails : NSObject <SCPJSONDecodable>

/**
 ID of the location that this transaction’s reader is assigned to.
 */
@property (nonatomic, nullable, readonly) NSString *location;

/**
 ID of the reader this transaction was made on.
 */
@property (nonatomic, nullable, readonly) NSString *reader;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
