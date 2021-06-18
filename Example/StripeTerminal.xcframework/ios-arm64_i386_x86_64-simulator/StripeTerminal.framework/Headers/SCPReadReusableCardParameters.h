//
//  SCPReadReusableCardParameters.h
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
 Parameters for reading a reusable card.

 **NOTE: Most integrations should not use `readReusableCard`.**

 You should create a `PaymentIntent` and use the associated `collectPaymentMethod`
 and `processPayment` methods if you are simply collecting a payment from
 a customer.

 You can use `-[SCPTerminal readReusableCard:delegate:completion:]` to read
 payment details and defer payment for later. The `SCPPaymentMethod` created by
 this method will have type `card`, suitable for use with online payments.

 Note that if you use this method to defer a payment, the transaction will
 *not* receive the beneficial rates and liability shift associated with card
 present transactions.

 @see https://stripe.com/docs/terminal/online-payments
 */
NS_SWIFT_NAME(ReadReusableCardParameters)
@interface SCPReadReusableCardParameters : NSObject

/**
 Optional parameter: attach the new PaymentMethod to Customer with this id
 */
@property (nonatomic, copy, nullable, readwrite) NSString *customer;

/**
 Optional set of key-value pairs attached to the object. The default is nil.
 */
@property (nonatomic, copy, nullable, readwrite) NSDictionary *metadata;

@end

NS_ASSUME_NONNULL_END
