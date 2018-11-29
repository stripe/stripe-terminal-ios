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

@class SCPCardPresentSource,
SCPCardSource,
SCPConfirmError,
SCPReader,
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
 A block called with a boolean value indicating whether the SDK should begin
 installing an available reader software update.

 If an update is initiated, the reader will become unresponsive until the
 update is complete. In some cases, you will need to restart the reader at the
 end of the update.

 @param installUpdate     A boolean value indicating whether the SDK should
 proceed with the udpate.
 */
NS_SWIFT_NAME(InstallUpdateBlock)
typedef void (^SCPInstallUpdateBlock)(BOOL installUpdate);

/**
 A block called with a card source.

 @param source      A card source.
 @param error       An error if one occurred, or nil.
 */
NS_SWIFT_NAME(CardSourceCompletionBlock)
typedef void (^SCPCardSourceCompletionBlock)(SCPCardSource * __nullable source, NSError * __nullable error);

/**
 A block called with a card present source.

 @param source      A card present source.
 @param error       An error if one occurred, or nil.
 */
NS_SWIFT_NAME(CardPresentSourceCompletionBlock)
typedef void (^SCPCardPresentSourceCompletionBlock)(SCPCardPresentSource * __nullable source, NSError * __nullable error);

/**
 A block called with an optional error.

 @param error       The error, or nil if no error occured.
 */
NS_SWIFT_NAME(ErrorCompletionBlock)
typedef void (^SCPErrorCompletionBlock)(NSError * __nullable error);

/**
 A block called with a PaymentIntent or a confirm error.

 @param intent      The PaymentIntent, or nil.
 @param error       An error if one occurred, or nil.
 */
NS_SWIFT_NAME(ConfirmPaymentIntentCompletionBlock)
typedef void (^SCPConfirmPaymentIntentCompletionBlock)(SCPPaymentIntent * __nullable intent, SCPConfirmError * __nullable error);

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

NS_ASSUME_NONNULL_END
