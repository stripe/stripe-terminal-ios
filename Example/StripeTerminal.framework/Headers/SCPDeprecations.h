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

#import "SCPCardPresentDetails.h"
#import "SCPCharge.h"
#import "SCPConnectionStatus.h"
#import "SCPDiscoveryConfiguration.h"
#import "SCPErrors.h"
#import "SCPPaymentIntent.h"
#import "SCPPaymentStatus.h"
#import "SCPReaderDisplayDelegate.h"
#import "SCPReaderSoftwareUpdate.h"
#import "SCPReadReusableCardParameters.h"
#import "SCPReceiptDetails.h"
#import "SCPTerminal.h"

NS_ASSUME_NONNULL_BEGIN

@class SCPProcessPaymentError;

/*
 This file contains deprecated symbols, to ease the update process.
 */

#pragma mark - Terminal Property Renames

@interface SCPTerminal ()
/// Deprecated: terminalDelegate has been renamed to delegate
@property (nonatomic, nullable, readwrite) id<SCPTerminalDelegate> terminalDelegate
__attribute__((deprecated("terminalDelegate has been renamed to delegate", "delegate")));

/// `clearConnectionToken` has been renamed to `clearCachedCredentials`
- (void)clearConnectionToken NS_SWIFT_NAME(clearConnectionToken())
__attribute__((deprecated("clearConnectionToken has been renamed to clearCachedCredentials",
                          "clearCachedCredentials")));
@end

#pragma mark - confirmPaymentIntent -> processPayment

NS_SWIFT_NAME(ConfirmError)
typedef SCPProcessPaymentError SCPConfirmError
__attribute__((deprecated("SCPConfirmError has been renamed to SCPProcessPaymentError", "SCPProcessPaymentError")));

NS_SWIFT_NAME(ConfirmPaymentIntentCompletionBlock)
typedef SCPProcessPaymentCompletionBlock SCPConfirmPaymentIntentCompletionBlock
__attribute__((deprecated("SCPConfirmPaymentIntentCompletionBlock has been replaced by SCPProcessPaymentCompletionBlock", "SCPProcessPaymentCompletionBlock")));

@interface SCPTerminal ()
- (void)confirmPaymentIntent:(SCPPaymentIntent *)paymentIntent
                  completion:(SCPConfirmPaymentIntentCompletionBlock)completion NS_SWIFT_NAME(confirmPaymentIntent(_:completion:))
__attribute__((deprecated("confirmPaymentIntent:completion: has been replaced by processPayment:completion:", "processPayment:completion:")));
@end

#pragma mark - PaymentIntent + PaymentMethod

extern const SCPPaymentIntentStatus SCPPaymentIntentStatusRequiresSource
__attribute__((deprecated("SCPPaymentIntentStatusRequiresSource has been replaced by SCPPaymentIntentStatusRequiresPaymentMethod", "SCPPaymentIntentStatusRequiresPaymentMethod")));

OBJC_UNAVAILABLE("StripeTerminal now uses PaymentMethods, not Sources")
@interface SCPSource
@end

NS_SWIFT_NAME(ReceiptData)
typedef SCPReceiptDetails SCPReceiptData
__attribute__((deprecated("SCPReceiptData has been replaced by SCPReceiptDetails", "SCPReceiptDetails")));

@interface SCPReceiptDetails ()

@property (nonatomic, readonly) NSString *mid
OBJC_UNAVAILABLE("`mid` property has been removed");

@property (nonatomic, readonly) NSString *tid
OBJC_UNAVAILABLE("`tid` property has been removed");

@end

/*
 Deprecated: SCPCardPresentSource has been removed.

 Depending on the the integration, it is now one of two different things:
 * On a PaymentIntent/Charge it has been replaced with SCPCardPresentDetails.
 * As the result of `readReusableCard:`, it has been replaced by SCPPaymentMethod.

 To help with migration, it's being typedef'd to SCPCardPresentDetails,
 which is approximately correct for the normal flow. For clients using
 the less common `readSource`/`readReusableCard` integration, this is
 now the *wrong* type, and needs to be manually changed to SCPPaymentMethod.
 Hypothesis is that since the `readReusableCard` completion block correctly
 vends SCPPaymentMethod objects, which have a `card` property with the
 data that used to be present on SCPCardPresentSource, this won't be
 too painful, even though we can't provide compiler help.
 */
NS_SWIFT_NAME(CardPresentSource)
typedef SCPCardPresentDetails SCPCardPresentSource
DEPRECATED_MSG_ATTRIBUTE("SCPCardPresentSource has been removed. On a PaymentIntent/Charge it has been replaced with SCPCardPresentDetails. As the result of `readReusableCard:`, it has been replaced by SCPPaymentMethod");

@interface SCPCardPresentDetails ()
@property (nonatomic, readonly) NSString *stripeId
OBJC_UNAVAILABLE("SCPCardPresentDetails objects do not have a stripeId. If you're using `readReusableCard` you need to change the type of this object to SCPPaymentMethod. Otherwise, the SCPCharge that these details came from have a stripeId");

@property (nonatomic, nullable, readonly) NSString *name
DEPRECATED_MSG_ATTRIBUTE("The cardholder's name is unavailable and will always be nil.");

// this also changed to nullable
@property (nonatomic, nullable, readonly) SCPReceiptData *receiptData
__attribute__((deprecated("receiptData has been replaced by receipt", "receipt")));

@property (nonatomic, nullable, readonly) NSDictionary *metadata
DEPRECATED_MSG_ATTRIBUTE("metadata is unavailable on this object, and will always be nil.");
@end

@interface SCPPaymentIntent ()

/**
 Deprecated: cardPresentSource has been removed.

 A very rough equivalent would be `charges.firstObject.paymentMethodDetails.cardPresent`.
 */
@property (nonatomic, nullable, readonly) SCPCardPresentSource *cardPresentSource
DEPRECATED_MSG_ATTRIBUTE("cardPresentSource has been removed. Use `paymentMethodDetails.cardPresent` on a SCPCharge instead");

@end

@interface SCPCharge ()

@property (nonatomic, nullable, readonly) SCPCardPresentSource *cardPresentSource
__attribute__((deprecated("cardPresentSource has been replaced by paymentMethodDetails.cardPresent", "paymentMethodDetails.cardPresent")));
@end

#pragma mark - readSource -> readReusableCard

NS_SWIFT_NAME(ReadSourceParameters)
typedef SCPReadReusableCardParameters SCPReadSourceParameters
__attribute__((deprecated("SCPReadSourceParameters has been replaced by SCPReadReusableCardParameters", "SCPReadReusableCardParameters")));

@interface SCPReadReusableCardParameters ()
@property (nonatomic, copy, nullable, readwrite) NSString *stripeAccount
DEPRECATED_MSG_ATTRIBUTE("stripeAccount is deprecated and has no effect. The account is set via the connection token from your SCPConnectionTokenProvider");
@end

NS_SWIFT_NAME(ReaderInputDelegate)
__attribute__((deprecated("SCPReaderInputDelegate has been replaced by SCPReaderDisplayDelegate. Both of the delegate methods have been renamed as well", "SCPReaderDisplayDelegate")))
@protocol SCPReaderInputDelegate <SCPReaderDisplayDelegate>
// afaik there isn't anything we can do to help with the delegate method renames :(
@end

NS_SWIFT_NAME(CardPresentSourceCompletionBlock)
typedef SCPPaymentMethodCompletionBlock SCPCardPresentSourceCompletionBlock
__attribute__((deprecated("SCPCardPresentSourceCompletionBlock has been replaced by SCPPaymentMethodCompletionBlock, which returns a PaymentMethod instead of a Source", "SCPPaymentMethodCompletionBlock")));

@interface SCPTerminal ()
- (nullable SCPCancelable *)readSource:(SCPReadSourceParameters *)parameters
delegate:(id<SCPReaderInputDelegate>)delegate
completion:(SCPCardPresentSourceCompletionBlock)completion NS_SWIFT_NAME(readSource(_:delegate:completion:))
__attribute__((deprecated("readSource:delegate:completion: has been replaced by readReusableCard:delegate:completion:, which returns a PaymentMethod instead of a Source", "readReusableCard:delegate:completion:")));
@end

#pragma mark - ReaderInputPrompt -> ReaderDisplayMessage

NS_SWIFT_NAME(ReaderInputPrompt)
typedef SCPReaderDisplayMessage SCPReaderInputPrompt
__attribute__((deprecated("SCPReaderInputPrompt has been replaced by SCPReaderDisplayMessage", "SCPReaderDisplayMessage")));

// I don't think these need any NS_SWIFT_NAME annotations, because these are just
// prefix changes, and the swift shorthand version *doesn't change*:
// ReaderInputPrompt.retryCard => ReaderDisplayMessage.retryCard

extern const SCPReaderDisplayMessage SCPReaderInputPromptRetryCard
__attribute__((deprecated("SCPReaderInputPromptRetryCard has been replaced by SCPReaderDisplayMessageRetryCard", "SCPReaderDisplayMessageRetryCard")));
extern const SCPReaderDisplayMessage SCPReaderInputPromptInsertCard
__attribute__((deprecated("SCPReaderInputPromptInsertCard has been replaced by SCPReaderDisplayMessageInsertCard", "SCPReaderDisplayMessageInsertCard")));
extern const SCPReaderDisplayMessage SCPReaderInputPromptInsertOrSwipeCard
__attribute__((deprecated("SCPReaderInputPromptInsertOrSwipeCard has been replaced by SCPReaderDisplayMessageInsertOrSwipeCard", "SCPReaderDisplayMessageInsertOrSwipeCard")));
extern const SCPReaderDisplayMessage SCPReaderInputPromptSwipeCard
__attribute__((deprecated("SCPReaderInputPromptSwipeCard has been replaced by SCPReaderDisplayMessageSwipeCard", "SCPReaderDisplayMessageSwipeCard")));
extern const SCPReaderDisplayMessage SCPReaderInputPromptRemoveCard
__attribute__((deprecated("SCPReaderInputPromptRemoveCard has been replaced by SCPReaderDisplayMessageRemoveCard", "SCPReaderDisplayMessageRemoveCard")));
extern const SCPReaderDisplayMessage SCPReaderInputPromptMultipleContactlessCardsDetected
__attribute__((deprecated("SCPReaderInputPromptMultipleContactlessCardsDetected has been replaced by SCPReaderDisplayMessageMultipleContactlessCardsDetected", "SCPReaderDisplayMessageMultipleContactlessCardsDetected")));
extern const SCPReaderDisplayMessage SCPReaderInputPromptTryAnotherReadMethod
__attribute__((deprecated("SCPReaderInputPromptTryAnotherReadMethod has been replaced by SCPReaderDisplayMessageTryAnotherReadMethod", "SCPReaderDisplayMessageTryAnotherReadMethod")));
extern const SCPReaderDisplayMessage SCPReaderInputPromptTryAnotherCard
__attribute__((deprecated("SCPReaderInputPromptTryAnotherCard has been replaced by SCPReaderDisplayMessageTryAnotherCard", "SCPReaderDisplayMessageTryAnotherCard")));


@interface SCPTerminal ()
+ (NSString *)stringFromReaderInputPrompt:(SCPReaderInputPrompt)prompt
NS_SWIFT_NAME(stringFromReaderInputPrompt(_:))
__attribute__((deprecated("stringFromReaderInputPrompt: has been replaced by stringFromReaderDisplayMessage:", "stringFromReaderDisplayMessage:")));
@end

#pragma mark - Adding DiscoveryConfiguration.simulated property

extern const SCPDeviceType SCPDeviceTypeReaderSimulator
OBJC_UNAVAILABLE("Choosing a simulated reader has moved to SCPDiscoveryConfiguration.init");

@interface SCPDiscoveryConfiguration ()

- (instancetype)initWithDeviceType:(SCPDeviceType)deviceType
OBJC_UNAVAILABLE("Use `initWithDeviceType:simulated:` instead");

- (nullable instancetype)initWithDeviceType:(SCPDeviceType)deviceType method:(SCPDiscoveryMethod)method
OBJC_UNAVAILABLE("Use `initWithDeviceType:discoveryMethod:simulated:` instead");

@property (nonatomic, readonly) SCPDiscoveryMethod method
__attribute__((deprecated("`method` has been replaced by `discoveryMethod`", "discoveryMethod")));
@end

#pragma mark - SCPError Changes

extern const SCPError SCPErrorCancelFailed
OBJC_UNAVAILABLE(".cancelFailed has been split into .cancelFailedAlreadyCompleted and .cancelFailedReaderBusy");

extern const SCPError SCPErrorConfirmInvalidIntent
__attribute__((deprecated("SCPErrorConfirmInvalidIntent has been replaced by SCPErrorProcessInvalidPaymentIntent", "SCPErrorProcessInvalidPaymentIntent")));

extern const SCPError SCPErrorFetchConnectionTokenCompletedWithError
__attribute__((deprecated("SCPErrorFetchConnectionTokenCompletedWithError has been replaced by SCPErrorConnectionTokenProviderCompletedWithError", "SCPErrorConnectionTokenProviderCompletedWithError")));

extern const SCPError SCPErrorReaderWaitingForInput
OBJC_UNAVAILABLE("SCPErrorReaderWaitingForInput never happened, and was removed");

#pragma mark - SCPPaymentStatus

extern const SCPPaymentStatus SCPPaymentStatusCollectingPaymentMethod
__attribute__((deprecated("SCPPaymentStatusCollectingPaymentMethod has been removed. You may want SCPPaymentStatusWaitingForInput instead", "SCPPaymentStatusWaitingForInput")));

extern const SCPPaymentStatus SCPPaymentStatusConfirmingPaymentIntent
__attribute__((deprecated("SCPPaymentStatusConfirmingPaymentIntent has been removed. You may want SCPPaymentStatusProcessing instead", "SCPPaymentStatusProcessing")));

#pragma mark - SCPConnectionStatus

extern const SCPConnectionStatus SCPConnectionStatusBusy
DEPRECATED_MSG_ATTRIBUTE("SCPConnectionStatusBusy has been removed and will never be returned");

#pragma mark - Software Update

@interface SCPTerminal ()

- (nullable SCPCancelable *)checkForReaderSoftwareUpdate:(id<SCPReaderSoftwareUpdateDelegate>)delegate
                                              completion:(SCPErrorCompletionBlock)completion
NS_SWIFT_NAME(checkForReaderSoftwareUpdate(delegate:completion:))
DEPRECATED_MSG_ATTRIBUTE("checkForReaderSoftwareUpdate:delegate:completion: has been replaced by checkForUpdate: and installUpdate:delegate:completion:. This method does nothing in this release.");

@end

NS_SWIFT_NAME(InstallUpdateBlock)
typedef void (^SCPInstallUpdateBlock)(BOOL installUpdate)
__attribute__((deprecated("SCPInstallUpdateBlock has been deleted.")));

@interface SCPReaderSoftwareUpdate ()

+ (NSString *)stringFromUpdateTimeExtimate:(SCPUpdateTimeEstimate)estimate
__attribute__((deprecated("The typo `extimate` been fixed, use `estimate` instead", "stringFromUpdateTimeEstimate:")));

@end

NS_ASSUME_NONNULL_END
