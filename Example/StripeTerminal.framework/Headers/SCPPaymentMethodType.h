//
//  SCPPaymentMethodType.h
//  StripeTerminal
//
//  Created by Daniel Jackson on 4/10/19.
//  Copyright © 2019 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The type of the PaymentMethod.

 @see https://stripe.com/docs/api/payment_methods/object#payment_method_object-type
 */
typedef NS_ENUM(NSUInteger, SCPPaymentMethodType) {
    /**
     A card payment method.
     */
    SCPPaymentMethodTypeCard,

    /**
     A card present payment method.
     */
    SCPPaymentMethodTypeCardPresent,

    /**
     An unknown type.
     */
    SCPPaymentMethodTypeUnknown,
};

NS_ASSUME_NONNULL_END
