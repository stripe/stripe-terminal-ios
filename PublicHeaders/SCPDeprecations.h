//
//  SCPDeprecations.h
//  StripeTerminal
//
//  Created by Daniel Jackson on 4/17/19.
//  Copyright © 2019 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPTerminal.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This file contains deprecated symbols, to ease the update process.
 */

@interface SCPTerminal (Deprecations)

/**
 Initiates an in-person refund with a given set of `SCPRefundParameters` by
 collecting the payment method that is to be refunded.

 Some payment methods, like Interac Debit payments, require that in-person payments
 also be refunded while the cardholder is present. The cardholder must present
 the Interac card to the card reader; these payments cannot be refunded via the
 dashboard or the API.

 For payment methods that don't require the cardholder be present, see
 https://stripe.com/docs/terminal/payments/refunds

 This method, along with `confirmRefund`, allow you to design an in-person refund
 flow into your app.

 If collecting a payment method fails, the completion block will be called with
 an error. After resolving the error, you may call `collectRefundPaymentMethod`
 again to either try the same card again, or try a different card.

 If collecting a payment method succeeds, the completion block will be called
 with an `nil` error. At that point, you can call `confirmRefund` to finish
 refunding the payment method.

 Calling any other SDK methods between `collectRefundPaymentMethod` and
 `confirmRefund` will result in undefined behavior.

 Note that if `collectRefundPaymentMethod` is canceled, the completion block
 will be called with a `Canceled` error.

 @see https://stripe.com/docs/terminal/canada#interac-refunds

 @param refundParams  The SCPRefundParameters object that describes how the
 refund will be created.
 @param completion  The completion block called when the command completes.
 */
- (nullable SCPCancelable *)collectRefundPaymentMethod:(SCPRefundParameters *)refundParams
                                            completion:(SCPErrorCompletionBlock)completion
    NS_SWIFT_NAME(collectRefundPaymentMethod(_:completion:))
        DEPRECATED_MSG_ATTRIBUTE("collectRefundPaymentMethod has been replaced by processRefund");

/**
 Initiates an in-person refund with a given set of `SCPRefundParameters` by
 collecting the payment method that is to be refunded.

 Some payment methods, like Interac Debit payments, require that in-person payments
 also be refunded while the cardholder is present. The cardholder must present
 the Interac card to the card reader; these payments cannot be refunded via the
 dashboard or the API.

 For payment methods that don't require the cardholder be present, see
 https://stripe.com/docs/terminal/payments/refunds

 This method, along with `confirmRefund`, allow you to design an in-person refund
 flow into your app.

 If collecting a payment method fails, the completion block will be called with
 an error. After resolving the error, you may call `collectRefundPaymentMethod`
 again to either try the same card again, or try a different card.

 If collecting a payment method succeeds, the completion block will be called
 with an `nil` error. At that point, you can call `confirmRefund` to finish
 refunding the payment method.

 Calling any other SDK methods between `collectRefundPaymentMethod` and
 `confirmRefund` will result in undefined behavior.

 Note that if `collectRefundPaymentMethod` is canceled, the completion block
 will be called with a `Canceled` error.

 @see https://stripe.com/docs/terminal/canada#interac-refunds

 @param refundParams  The SCPRefundParameters object that describes how the
 refund will be created.
 @param refundConfig An optional SCPCollectRefundConfiguration to configure per-refund overrides.
 @param completion  The completion block called when the command completes.
 */
- (nullable SCPCancelable *)collectRefundPaymentMethod:(SCPRefundParameters *)refundParams
                                          refundConfig:(nullable SCPCollectRefundConfiguration *)refundConfig
                                            completion:(SCPErrorCompletionBlock)completion
    NS_SWIFT_NAME(collectRefundPaymentMethod(_:refundConfig:completion:))
        DEPRECATED_MSG_ATTRIBUTE("collectRefundPaymentMethod has been replaced by processRefund");

/**
 Confirms an in-person refund after the refund payment method has been collected.

 The completion block will either be called with the successful `SCPRefund` or
 with an `SCPConfirmRefundError`.

 When `confirmRefund` fails, the SDK returns an error that either includes the
 failed `SCPRefund` or the `SCPRefundParameters` that led to a failure.
 Your app should inspect the `SCPConfirmRefundError` to decide how to proceed.

 1. If the refund property is `nil`, the request to Stripe's servers timed
 out and the refund's status is unknown. We recommend that you retry
 `confirmRefund` with the original `SCPRefundParameters`.

 2. If the `SCPConfirmRefundError` has a `failure_reason`, the refund was declined.
 We recommend that you take action based on the decline code you received.

 @note `collectRefundPaymentMethod:completion` and `confirmRefund` are only
 available for payment methods that require in-person refunds. For all other
 refunds, use the Stripe Dashboard or the Stripe API.

 @see https://stripe.com/docs/terminal/canada#interac-refunds

 @param completion  The completion block called when the command completes.
 */
- (nullable SCPCancelable *)confirmRefund:(SCPConfirmRefundCompletionBlock)completion
    NS_SWIFT_NAME(confirmRefund(completion:))
        DEPRECATED_MSG_ATTRIBUTE("confirmRefund has been replaced by processRefund");

@end

NS_ASSUME_NONNULL_END
