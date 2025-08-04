//
//  SCPPaynowDetails.h
//  StripeTerminal
//
//  Created by Qiang Jiang on 6/27/25.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains details about a user's paynow payment

 @see https://stripe.com/docs/api/payment_methods/object#payment_method_object-paynow
 */
NS_SWIFT_NAME(PaynowDetails)
@interface SCPPaynowDetails : NSObject <SCPJSONDecodable>

/**
 ID of the location that this transaction’s reader is assigned to.
 */
@property (nonatomic, nullable, readonly) NSString *location;

/**
 ID of the reader this transaction was made on.
 */
@property (nonatomic, nullable, readonly) NSString *reader;

/**
 Reference number associated with this PayNow payment.
 */
@property (nonatomic, nullable, readonly) NSString *reference;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
