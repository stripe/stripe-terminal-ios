//
//  SCPBlocks.h
//  StripePOS
//
//  Created by Ben Guo on 7/28/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import "SCPCharge.h"
#import "SCPConnectionStatus.h"

NS_ASSUME_NONNULL_BEGIN

@class
CLLocation,
SCPAttachSourceError,
SCPCardPresentSource,
SCPCardSource,
SCPCharge,
SCPConfirmError,
SCPReader,
SCPPaymentIntent,
SCPRefund;

/**
 A block called with an activation token or an error.
 @see SCPActivationTokenProvider

 @param token       The activation_token from the reset Terminal response.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPActivationTokenCompletionBlock)(NSString * __nullable token, NSError * __nullable error);

/**
 A block called with a boolean value.

 @param success     Whether the operation was successful.
 */
typedef void (^SCPBoolCompletionBlock)(BOOL success);

/**
 A block called with a selected reader object.

 @param reader      The reader to select, or nil to cancel connecting to a reader.
 */
typedef void (^SCPSelectReaderCompletionBlock)(SCPReader * __nullable reader);

/**
 A block called with a card source.

 @param source      A card source.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPCardSourceCompletionBlock)(SCPCardSource * __nullable source, NSError * __nullable error);

/**
 A block called with a card present source.

 @param source      A card present source.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPCardPresentSourceCompletionBlock)(SCPCardPresentSource * __nullable source, NSError * __nullable error);

/**
 A block called with an optional error.

 @param error       The error, or nil if no error occured.
 */
typedef void (^SCPErrorCompletionBlock)(NSError * __nullable error);

/**
 A block called with payment intent or a confirm error.

 @param intent      The payment intent, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPConfirmPaymentIntentCompletionBlock)(SCPPaymentIntent * __nullable intent, SCPConfirmError * __nullable error);

/**
 A block called with payment intent or an error error.

 @param intent      The payment intent, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPPaymentIntentCompletionBlock)(SCPPaymentIntent * __nullable intent, NSError * __nullable error);

/**
 A block called with a location or an error.

 @param location    The location, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPLocationCompletionBlock)(CLLocation * __nullable location, NSError * __nullable error);

/**
 A block called with a refund or an error.

 @param refund      A refund object, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPRefundCompletionBlock)(SCPRefund * __nullable refund, NSError * __nullable error);

/**
 A block called with a reader object or an error.

 @param reader      A reader object, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPReaderCompletionBlock)(SCPReader * __nullable reader, NSError * __nullable error);

NS_ASSUME_NONNULL_END
