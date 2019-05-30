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
SCPProcessPaymentError,
SCPReader,
SCPReaderSoftwareUpdate,
SCPPaymentIntent;

/**
 A block called with a connection token or an error from your backend.
 @see SCPConnectionTokenProvider

 @param token       The connection token from your backend server.
 @param error       An error if one occurred, or nil.
 */
NS_SWIFT_NAME(ConnectionTokenCompletionBlock)
typedef void (^SCPConnectionTokenCompletionBlock)(NSString * __nullable token, NSError * __nullable error);

/**
 A block called with a logline from the SDK.

 @param logline     An internal logline from the SDK.
 */
NS_SWIFT_NAME(LogListenerBlock)
typedef void (^SCPLogListenerBlock)(NSString * _Nonnull logline);



/**
 A block called with a PaymentMethod.

 @param paymentMethod  A PaymentMethod object, or nil if an error occurred.
 @param error          An error if one occurred, or nil.
 */
NS_SWIFT_NAME(PaymentMethodCompletionBlock)
typedef void (^SCPPaymentMethodCompletionBlock)(SCPPaymentMethod * __nullable paymentMethod, NSError * __nullable error);

/**
 A block called with an optional error.

 @param error       The error, or nil if no error occured.
 */
NS_SWIFT_NAME(ErrorCompletionBlock)
typedef void (^SCPErrorCompletionBlock)(NSError * __nullable error);

/**
 A block called with a PaymentIntent or a ProcessPaymentError

 @param intent      The PaymentIntent, or nil.
 @param error       An error if one occurred, or nil.
 */
NS_SWIFT_NAME(ProcessPaymentCompletionBlock)
typedef void (^SCPProcessPaymentCompletionBlock)(SCPPaymentIntent * __nullable intent, SCPProcessPaymentError * __nullable error);

/**
 A block called with a PaymentIntent or an error.

 @param intent      The PaymentIntent, or nil.
 @param error       An error if one occurred, or nil.
 */
NS_SWIFT_NAME(PaymentIntentCompletionBlock)
typedef void (^SCPPaymentIntentCompletionBlock)(SCPPaymentIntent * __nullable intent, NSError * __nullable error);

/**
 A block called with a reader object or an error.

 @param reader      A reader object, or nil.
 @param error       An error if one occurred, or nil.
 */
NS_SWIFT_NAME(ReaderCompletionBlock)
typedef void (^SCPReaderCompletionBlock)(SCPReader * __nullable reader, NSError * __nullable error);

/**
 A block called with a ReaderSoftwareUpdate or an error. If there is no update
 and no error the block will be called with `(nil, nil)`.

 @param update      An update object, or nil.
 @param error       An error if one occurred, or nil.
 */
NS_SWIFT_NAME(ReaderSoftwareUpdateCompletionBlock)
typedef void (^SCPReaderSoftwareUpdateCompletionBlock)(SCPReaderSoftwareUpdate * __nullable update, NSError * __nullable error);

NS_ASSUME_NONNULL_END
