//
//  SCPBlocks.h
//  StripePOS
//
//  Created by Ben Guo on 7/28/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPCardPresentSource,
SCPCardSource,
SCPConfirmError,
SCPReader,
SCPPaymentIntent;

/**
 A block called with an activation token or an error.
 @see SCPActivationTokenProvider

 @param token       The activation_token from the reset Terminal response.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPActivationTokenCompletionBlock)(NSString * __nullable token, NSError * __nullable error);

/**
 A block called with a boolean value indicating whether the SDK should install an available update.

 @param installUpdate     A boolean value indicating whether the SDK should install the available
 update.
 */
typedef void (^SCPInstallUpdateCompletionBlock)(BOOL installUpdate);

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
 A block called with a reader object or an error.

 @param reader      A reader object, or nil.
 @param error       An error if one occurred, or nil.
 */
typedef void (^SCPReaderCompletionBlock)(SCPReader * __nullable reader, NSError * __nullable error);

NS_ASSUME_NONNULL_END
