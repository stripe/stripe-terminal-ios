//
//  SCPAffirmDetails.h
//  StripeTerminal
//
//  Created by Henry Xu on 9/4/24.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains details about a user's affirm payment

 @see https://stripe.com/docs/api/payment_methods/object#payment_method_object-affirm
 */
NS_SWIFT_NAME(AffirmDetails)
@interface SCPAffirmDetails : NSObject <SCPJSONDecodable>

/**
 ID of the location that this transaction’s reader is assigned to.
 */
@property (nonatomic, nullable, readonly) NSString *location;

/**
 ID of the reader this transaction was made on.
 */
@property (nonatomic, nullable, readonly) NSString *reader;

/**
 Transaction ID of this particular Affirm transaction.
 */
@property (nonatomic, nullable, readonly) NSString *transactionId;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
