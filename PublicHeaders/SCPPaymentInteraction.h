//
//  SCPPaymentInteraction.h
//  StripeTerminal
//
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

@class SCPPaymentIntent;
@class SCPPaymentOption;
@class SCPQrCodeDisplayData;

NS_ASSUME_NONNULL_BEGIN

/**
 A payment interaction that requires your application to display UI and provide a response before
 the payment can continue.

 Use the concrete subclasses to handle each interaction type.
 */
NS_SWIFT_NAME(PaymentInteraction)
@interface SCPPaymentInteraction : NSObject

/**
 You cannot directly instantiate `SCPPaymentInteraction`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPPaymentInteraction`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 An interaction that requires the customer to select a payment method during payment collection.
 */
NS_SWIFT_NAME(PaymentMethodSelectionInteraction)
@interface SCPPaymentMethodSelectionInteraction : SCPPaymentInteraction

/**
 The PaymentIntent being processed.
 */
@property (nonatomic, strong, readonly) SCPPaymentIntent *paymentIntent;

/**
 The payment options available for selection.
 */
@property (nonatomic, copy, readonly) NSArray<SCPPaymentOption *> *availableOptions;

/**
 Completes the interaction with either the selected payment option or an error.

 @param paymentOption The selected payment option, or nil if selection failed.
 @param error         An error if selection failed, or nil if successful.
 */
- (void)completeWithPaymentOption:(nullable SCPPaymentOption *)paymentOption
                            error:(nullable NSError *)error NS_SWIFT_NAME(complete(paymentOption:error:));

@end

/**
 An interaction that requires a QR code to be displayed during payment confirmation.
 */
NS_SWIFT_NAME(QrCodeDisplayInteraction)
@interface SCPQrCodeDisplayInteraction : SCPPaymentInteraction

/**
 The PaymentIntent being processed.
 */
@property (nonatomic, strong, readonly) SCPPaymentIntent *paymentIntent;

/**
 The data required to display the QR code.
 */
@property (nonatomic, strong, readonly) SCPQrCodeDisplayData *qrData;

/**
 Completes the interaction after the QR code is displayed, or reports an error.

 @param error An error if QR code display failed, or nil if successful.
 */
- (void)completeWithError:(nullable NSError *)error NS_SWIFT_NAME(complete(error:));

@end

NS_ASSUME_NONNULL_END
