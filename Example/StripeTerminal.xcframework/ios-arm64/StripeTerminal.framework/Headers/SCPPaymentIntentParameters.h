//
//  SCPPaymentIntentParameters.h
//  StripeTerminal
//
//  Created by Ben Guo on 8/2/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPPaymentMethodOptionsParameters.h>

NS_ASSUME_NONNULL_BEGIN

/**
 @abstract Controls when the funds will be captured from the customer’s account.

 @see https://stripe.com/docs/terminal/payments/collect-payment?terminal-sdk-platform=ios#capture-payment
 */
typedef NS_ENUM(NSUInteger, SCPCaptureMethod) {
    /// Place a hold on the funds when the customer authorizes the payment, but don’t
    /// capture the funds until later. Will require an explicit call to capture payments.
    /// (Not all payment methods support this.)
    SCPCaptureMethodManual,

    /// Stripe automatically captures funds when the customer authorizes the payment.
    SCPCaptureMethodAutomatic,
} NS_SWIFT_NAME(CaptureMethod);

/**
 Parameters for creating an `SCPPaymentIntent`. Pass an object of this type
 into `Terminal.shared.createPaymentIntent()`.

 @see https://stripe.com/docs/api/payment_intents/create
 */
NS_SWIFT_NAME(PaymentIntentParameters)
@interface SCPPaymentIntentParameters : NSObject

/**
 The amount of the payment, provided in the currency's smallest unit.
 */
@property (nonatomic, readonly) NSUInteger amount;

/**
 Three-letter ISO currency code, in lowercase. Must be a supported currency.
 */
@property (nonatomic, readonly) NSString *currency;

/**
 The list of payment method types that this PaymentIntent is allowed to use.
 The default is value for this is ["card_present"].
 */
@property (nonatomic, readonly) NSArray<NSString *> *paymentMethodTypes;

/**
 The capture method that this PaymentIntent should use. Defaults to `SCPCaptureMethodManual`.
 */
@property (nonatomic, readonly) SCPCaptureMethod captureMethod;

/**
 Set of key-value pairs that you can attach to an object. This can be useful for
 storing additional information about the object in a structured format.

 @see https://stripe.com/docs/api#metadata
 */
@property (nonatomic, nullable, readonly) NSDictionary<NSString *, NSString *> *metadata;

/**
 An arbitrary string attached to the object. If you send a receipt email for
 this payment, the email will include the description.
 */
@property (nonatomic, nullable, readonly) NSString *stripeDescription;

/**
 A string to be displayed on your customer's credit card statement. This may be
 up to 22 characters. The statement descriptor must contain at least one letter,
 may not include `<>"'` characters, and will appear on your customer's statement
 in capital letters. Non-ASCII characters are automatically stripped. While
 most banks and card issuers display this information consistently, some may
 display it incorrectly or not at all.
 */
@property (nonatomic, nullable, readonly) NSString *statementDescriptor;

/**
 A string to specify details about the transaction so your customer can understand it clearly on their statement.
 The suffix is concatenated with the `statementDescriptor`, the `*` symbol, and a space to form the complete statement
 descriptor that your customer sees. Maximum 22 characters for the final concatenated descriptor.

 @see https://stripe.com/docs/account/statement-descriptors
 */
@property (nonatomic, nullable, readonly) NSString *statementDescriptorSuffix;

/**
 Email address that the receipt for the resulting payment will be sent to.

 @see https://stripe.com/docs/terminal/checkout/receipts
 */
@property (nonatomic, nullable, readonly) NSString *receiptEmail;

/**
 The ID of the Customer this PaymentIntent is for, if one exists.

 @see https://stripe.com/docs/api/customers
 */
@property (nonatomic, nullable, readonly) NSString *customer;

/**
 The amount of the application fee (if any) that will be applied to the
 payment and transferred to the application owner’s Stripe account. To use an
 application fee, the request must be made on behalf of another account,
 using the stripeAccount property or an OAuth key.

 The amount is a boxed UInt in the currency's smallest unit.

 @see https://stripe.com/docs/connect/direct-charges#collecting-fees
 */
@property (nonatomic, nullable, readonly) NSNumber *applicationFeeAmount;

/**
 A string that identifies the resulting payment as part of a group.

 @see https://stripe.com/docs/connect/charges-transfers#grouping-transactions
 */
@property (nonatomic, nullable, readonly) NSString *transferGroup;

/**
 The account (if any) the payment will be attributed to for tax reporting, and
 where funds from the payment will be transferred to upon payment success.

 At capture time, use `transfer_data[amount]` to specify the amount that will be
 transferred automatically when a charge succeeds.

 When `transferDataDestination` is specified, `onBehalfOf` must also be
 specified and must match the destination of the transfer.
 */
@property (nonatomic, nullable, readonly) NSString *transferDataDestination;

/**
 The Stripe account ID for which these funds are intended.

 When `transferDataDestination` is specified, `onBehalfOf` must also be
 specified and must match the destination of the transfer.

 @see https://stripe.com/docs/connect/charges-transfers#on-behalf-of
 */
@property (nonatomic, nullable, readonly) NSString *onBehalfOf;

/**
 Indicates that you intend to make future payments with this PaymentIntent’s payment method.

 Providing this parameter will attach the payment method to the PaymentIntent’s Customer,
 after the PaymentIntent is confirmed and any required actions from the user are complete.
 If no Customer was provided, the payment method can still be attached to a Customer after
 the transaction completes.

 Possible values:
 "on_session": Use "on_session" if you intend to only reuse the payment method when your
 customer is present in your checkout flow.
 "off_session": Use "off_session" if your customer may or may not be present in your checkout flow.

 @see https://stripe.com/docs/api/payment_intents/create#create_payment_intent-setup_future_usage
 */
@property (nonatomic, nullable, readonly) NSString *setupFutureUsage;

/**
 Specific options used during the creation of the PaymentMethod.
 */
@property (nonatomic, readonly) SCPPaymentMethodOptionsParameters *paymentMethodOptionsParameters;

/**
 Use `SCPPaymentIntentParametersBuilder`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPPaymentIntentParametersBuilder`
 */
+ (instancetype)new NS_UNAVAILABLE;

/**
 Use stripeDescription for the string attached to the object.
 */
@property (nonatomic, copy, readonly) NSString *description DEPRECATED_MSG_ATTRIBUTE("Did you mean to use stripeDescription?");

@end

/**
 Builder class for `SCPPaymentIntentParameters`.
 */
NS_SWIFT_NAME(PaymentIntentParametersBuilder)
@interface SCPPaymentIntentParametersBuilder : SCPBuilder <SCPPaymentIntentParameters *>

/**
 Initializes SCPPaymentIntentParametersBuilder with the given parameters.

 @param amount      The amount of the payment, provided in the currency's
 smallest unit. @see `SCPPaymentIntentParameters.amount`

 @param currency    The currency of the payment. @see `SCPPaymentIntentParameters.currency`
 */
- (instancetype)initWithAmount:(NSUInteger)amount
                      currency:(NSString *)currency;

/// @see `SCPPaymentIntentParameters.amount`
- (SCPPaymentIntentParametersBuilder *)setAmount:(NSUInteger)amount;

/// @see `SCPPaymentIntentParameters.currency`
- (SCPPaymentIntentParametersBuilder *)setCurrency:(NSString *)currency;

/// @see `SCPPaymentIntentParameters.paymentMethodTypes`
- (SCPPaymentIntentParametersBuilder *)setPaymentMethodTypes:(NSArray<NSString *> *)paymentMethodTypes;

/// @see `SCPPaymentIntentParameters.captureMethod`
- (SCPPaymentIntentParametersBuilder *)setCaptureMethod:(SCPCaptureMethod)captureMethod;

/// @see `SCPPaymentIntentParameters.metadata`
- (SCPPaymentIntentParametersBuilder *)setMetadata:(nullable NSDictionary<NSString *, NSString *> *)metadata;

/// @see `SCPPaymentIntentParameters.stripeDescription`
- (SCPPaymentIntentParametersBuilder *)setStripeDescription:(nullable NSString *)stripeDescription;

/// @see `SCPPaymentIntentParameters.statementDescriptor`
- (SCPPaymentIntentParametersBuilder *)setStatementDescriptor:(nullable NSString *)statementDescriptor;

/// @see `SCPPaymentIntentParameters.statementDescriptorSuffix`
- (SCPPaymentIntentParametersBuilder *)setStatementDescriptorSuffix:(nullable NSString *)statementDescriptorSuffix;

/// @see `SCPPaymentIntentParameters.receiptEmail`
- (SCPPaymentIntentParametersBuilder *)setReceiptEmail:(nullable NSString *)receiptEmail;

/// @see `SCPPaymentIntentParameters.customer`
- (SCPPaymentIntentParametersBuilder *)setCustomer:(nullable NSString *)customer;

/// @see `SCPPaymentIntentParameters.applicationFeeAmount`
- (SCPPaymentIntentParametersBuilder *)setApplicationFeeAmount:(nullable NSNumber *)applicationFeeAmount;

/// @see `SCPPaymentIntentParameters.transferGroup`
- (SCPPaymentIntentParametersBuilder *)setTransferGroup:(nullable NSString *)transferGroup;

/// @see `SCPPaymentIntentParameters.transferDataDestination`
- (SCPPaymentIntentParametersBuilder *)setTransferDataDestination:(nullable NSString *)transferDataDestination;

/// @see `SCPPaymentIntentParameters.onBehalfOf`
- (SCPPaymentIntentParametersBuilder *)setOnBehalfOf:(nullable NSString *)onBehalfOf;

/// @see `SCPPaymentIntentParameters.setupFutureUsage`
- (SCPPaymentIntentParametersBuilder *)setSetupFutureUsage:(nullable NSString *)setupFutureUsage;

/// @see `SCPPaymentIntentParameters.paymentMethodOptionsParameters`
- (SCPPaymentIntentParametersBuilder *)setPaymentMethodOptionsParameters:(SCPPaymentMethodOptionsParameters *)paymentMethodOptionsParameters;

/**
 Use `initWithAmount:currency:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithAmount:currency:`
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
