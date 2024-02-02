//
//  SCPBlocks.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/28/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPPaymentMethod,
    SCPCollectInputsResult,
    SCPConfirmPaymentIntentError,
    SCPConfirmRefundError,
    SCPReader,
    SCPLocation,
    SCPPaymentIntent,
    SCPRefundParameters,
    SCPRefund,
    SCPSetupIntent,
    SCPSetupIntentParameters,
    SCPConfirmSetupIntentError,
    SCPReaderSettings;

/**
 A block called with a connection token or an error from your backend.
 @see SCPConnectionTokenProvider

 @param token       The connection token from your backend server.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPConnectionTokenCompletionBlock)(NSString *__nullable token, NSError *__nullable error)
    NS_SWIFT_NAME(ConnectionTokenCompletionBlock);

/**
 A block called with a logline from the SDK.

 @param logline     An internal logline from the SDK.
 */
typedef void (^SCPLogListenerBlock)(NSString *_Nonnull logline)
    NS_SWIFT_NAME(LogListenerBlock);

/**
 A block called with a PaymentMethod.

 @param paymentMethod  A PaymentMethod object, or nil if an error occurred.
 @param error          An error if one occurred, or nil.
 */
typedef void (^SCPPaymentMethodCompletionBlock)(SCPPaymentMethod *__nullable paymentMethod, NSError *__nullable error)
    NS_SWIFT_NAME(PaymentMethodCompletionBlock);

/**
 A block called with an optional error.

 @param error       The error, or nil if no error occured.
 */
typedef void (^SCPErrorCompletionBlock)(NSError *__nullable error)
    NS_SWIFT_NAME(ErrorCompletionBlock);

/**
 A block called with a PaymentIntent or a ConfirmPaymentIntentError

 @param intent      The PaymentIntent, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPConfirmPaymentIntentCompletionBlock)(SCPPaymentIntent *__nullable intent, SCPConfirmPaymentIntentError *__nullable error)
    NS_SWIFT_NAME(ConfirmPaymentIntentCompletionBlock);

/**
 A block called with a Refund or a ConfirmRefundError.

 @param refund      The Refund, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPConfirmRefundCompletionBlock)(SCPRefund *__nullable refund, SCPConfirmRefundError *__nullable error)
    NS_SWIFT_NAME(ConfirmRefundCompletionBlock);

/**
 A block called with a Refund or an error.

 @param refund      The Refund, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPRefundCompletionBlock)(SCPRefund *__nullable refund, NSError *__nullable error)
    NS_SWIFT_NAME(RefundCompletionBlock);

/**
 A block called with a PaymentIntent or an error.

 @param intent      The PaymentIntent, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPPaymentIntentCompletionBlock)(SCPPaymentIntent *__nullable intent, NSError *__nullable error)
    NS_SWIFT_NAME(PaymentIntentCompletionBlock);

/**
A block called with a SetupIntent or an error.

@param intent      The SetupIntent, or nil.
@param error       An error if one occurred, or nil.
*/
typedef void (^SCPSetupIntentCompletionBlock)(SCPSetupIntent *__nullable intent, NSError *__nullable error)
    NS_SWIFT_NAME(SetupIntentCompletionBlock);

/**
 A block called with a SetupIntent or a ConfirmSetupIntentError.

 @param intent      The SetupIntent, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPConfirmSetupIntentCompletionBlock)(SCPSetupIntent *__nullable intent, SCPConfirmSetupIntentError *__nullable error)
    NS_SWIFT_NAME(ConfirmSetupIntentCompletionBlock);

/**
 A block called with a list of Locations or an error.

 @param locations A list of Locations, or nil.
 @param hasMore Indicates whether there are more locations for the account; use the pagination parameters in SCPListLocationsParameters to fetch more locations
 @param error An error if one occurred, or nil.
 */
typedef void (^SCPLocationsCompletionBlock)(NSArray<SCPLocation *> *__nullable locations, BOOL hasMore, NSError *__nullable error)
    NS_SWIFT_NAME(LocationsCompletionBlock);

/**
 A block called with a reader object or an error.

 @param reader      A reader object, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPReaderCompletionBlock)(SCPReader *__nullable reader, NSError *__nullable error)
    NS_SWIFT_NAME(ReaderCompletionBlock);

/**
 A block called with an array of collect inputs result or an error.

 @param collectInputsResults      The collect inputs results, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPCollectInputsCompletionBlock)(NSArray<SCPCollectInputsResult *> *__nullable collectInputsResults, NSError *__nullable error)
    NS_SWIFT_NAME(CollectInputsCompletionBlock);

/**
 A block called with a `SCPReaderSettings`.

 Success denotes the command was received by the
 reader and responded to. But the contents of
 ReaderSettings should be checked for reader
 errors setting the values.

 @param readerSettings  `SCPReaderSettings` object, or nil if an error occurred.
 @param error  An error if one occurred, or nil.
 */
typedef void (^SCPReaderSettingsCompletionBlock)(SCPReaderSettings *__nullable readerSettings, NSError *__nullable error)
    NS_SWIFT_NAME(ReaderSettingsCompletionBlock);

NS_ASSUME_NONNULL_END
