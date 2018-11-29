//
//  SCPReadSourceParameters.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/11/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Parameters for reading a source.

 **NOTE: Most integrations should **not** use `readSource`.**

 You should create a `PaymentIntent` and use the associated `collectPaymentMethod`
 and `confirmPaymentIntent` methods if you are simply collecting a payment from
 a customer.

 You can use `readSource` to read payment details and defer payment for later.
 To do this, you will need to turn the "card present" source into a
 "card not present" source, which you can use to charge the customer online.

 Note that if you use this method to defer a payment, the transaction will
 *not* receive the beneficial rates and liability shift associated with card
 present transactions.
 */
NS_SWIFT_NAME(ReadSourceParameters)
@interface SCPReadSourceParameters : NSObject

/**
 Optional set of key-value pairs attached to the object. The default is nil.
 */
@property (nonatomic, copy, nullable, readwrite) NSDictionary *metadata;

/**
 To create the source on a conected account, set this property to the ID of the
 account for which the request is being made. The default is nil.
 
 @see https://stripe.com/docs/connect/authentication#authentication-via-the-stripe-account-header
 */
@property (nonatomic, copy, nullable, readwrite) NSString *stripeAccount;

@end

NS_ASSUME_NONNULL_END
