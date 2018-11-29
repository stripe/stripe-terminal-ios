//
//  NSError+StripeTerminal.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/26/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The error domain for all errors originating from the Stripe Terminal SDK.
 */
NS_SWIFT_NAME(ErrorDomain)
FOUNDATION_EXPORT NSString * const SCPErrorDomain;

#pragma mark - SCPError

/**
 Possible error codes for NSError objects under the SCPErrorDomain domain.
 */
typedef NS_ERROR_ENUM(SCPErrorDomain, SCPError) {
    /**
     GENERIC ERRORS
     */
    /**
     Unexpected SDK error.
     */
    SCPErrorUnexpectedSdkError = 1,
    /**
     Unexpected reader error.
     */
    SCPErrorUnknownReaderError = 3,
    /**
     Unexpected network error.
     */
    SCPErrorUnknownNetworkError = 9,

    /**
     SDK ERRORS
     */
    /**
     The SDK is busy executing another command.
     */
    SCPErrorBusy = 100,
    /**
     The command was canceled.
     */
    SCPErrorCanceled = 102,
    /**
     The Stripe API declined the payment.
     Inspect SCPConfirmError's requestError property for more information about
     the decline, including the decline code.
     */
    SCPErrorPaymentDeclinedByStripeAPI = 103,
    /**
     The reader declined the payment. Try another card.
     */
    SCPErrorPaymentDeclinedByReader = 104,
    /**
     The reader terminated the command. This can occur if a card from a previous
     payment was left in the reader.
     */
    SCPErrorTerminatedByReader = 105,

    /**
     Integration errors
     */
    /**
     Access to location services is currently disabled. This may be because:
     - The user disabled location services in the system settings.
     - The user denied access to location services for your app.
     - The user's device is in Airplane Mode and unable to gather location data.
     */
    SCPErrorLocationServicesDisabled = 150,
    /**
     There was an error communicating with the ConnectionTokenProvider.
     Make sure:
     - Your implementation of `fetchConnectionToken` calls the given completion block
     either a String or an error.
     - Your app strongly retains your ConnectionTokenProvider.
     */
    SCPErrorConnectionTokenProviderIntegrationError = 151,
    /**
     confirmPaymentIntent was called with an unknown or invalid PaymentIntent.
     You must confirm a PaymentIntent immediately after collecting a payment method.
     */
    SCPErrorConfirmInvalidIntent = 153,
    /**
     collectPaymentMethod or confirmPaymentIntent was called with a nil PaymentIntent.
     */
    SCPErrorNilPaymentIntent = 154,
    /**
     Canceling a command failed.
     */
    SCPErrorCancelFailed = 155,
    /**
     A PaymentIntent was referenced using an invalid client secret.
     */
    SCPErrorInvalidClientSecret = 156,

    /**
     READER ERRORS
     */
    /**
     No reader is connected. Connect to a reader before trying again.
     */
    SCPErrorNotConnectedToReader = 300,
    /**
     Already connected to a reader.
     */
    SCPErrorAlreadyConnectedToReader = 301,
    /**
     An incompatible reader was detected. You can only use the Stripe Terminal
     iOS SDK with one of Stripe's pre-certified readers. For more information,
     see https://stripe.com/docs/terminal/readers
     */
    SCPErrorIncompatibleReader = 302,
    /**
     The reader is busy.
     */
    SCPErrorReaderBusy = 305,
    /**
     Could not communicate with the reader.
     */
    SCPErrorReaderCommunicationError = 306,
    /**
     The reader is waiting for input.
     */
    SCPErrorReaderWaitingForInput = 307,
    /**
     Generic bluetooth error.
     */
    SCPErrorBluetoothError = 320,
    /**
     Bluetooth disabled on mobile device. Enable bluetooth in Settings.
     */
    SCPErrorBluetoothDisabled = 321,
    /**
     Scanning for bluetooth devices timed out.
     */
    SCPErrorBluetoothScanTimedOut = 322,
    /**
     The Bluetooth device was disconnected during an operation.
     */
    SCPErrorBluetoothDisconnected = 323,
    /**
     Connecting to the bluetooth device timed out. Make sure the device is
     powered on, in range, and not connected to another app or device. If this
     error continues to occur, you may need to charge the device.
     */
    SCPErrorBluetoothConnectTimedOut = 324,
    /**
     Generic reader software update error.
     */
    SCPErrorReaderSoftwareUpdateFailed = 380,
    /**
     Updating the reader software failed because the reader's battery is
     too low. Charge the reader before trying again.
     */
    SCPErrorReaderSoftwareUpdateFailedBatteryLow = 381,
    /**
     No reader software updates are available.
     */
    SCPErrorNoAvailableReaderSoftwareUpdate = 382,
    /**
     Updating the reader software failed because there was an error
     communicating with the reader.
     */
    SCPErrorReaderSoftwareUpdateFailedReaderError = 383,
    /**
     Updating the reader software failed because there was an error
     communicating with the update server.
     */
    SCPErrorReaderSoftwareUpdateFailedServerError = 384,
    /**
     Updating the reader software failed because the update was interrupted.
     */
    SCPErrorReaderSoftwareUpdateFailedInterrupted = 385,

    /**
     CARD ERRORS
     */
    /**
     The card is not a chip card.
     */
    SCPErrorCardInsertNotRead = 600,
    /**
     The swipe could not be read.
     */
    SCPErrorCardSwipeNotRead = 601,
    /**
     Reading a card timed out.
     */
    SCPErrorCardReadTimedOut = 602,
    /**
     The card was removed during the transaction.
     */
    SCPErrorCardRemoved = 603,
    /**
     The text field contained invalid card cata. Make sure
     [STPPaymentCardTextField isValid] returns YES before passing it to
     `createKeyedSource`.
     */
    SCPErrorInvalidPaymentCardTextField = 650,

    /**
     NETWORK ERRORS
     */
    /**
     The SDK is not connected to the internet.
     */
    SCPErrorNotConnectedToInternet = 900,
    /**
     The underlying request timed out.
     */
    SCPErrorRequestTimedOut = 901,
    /**
     The underlying request returned an API error.
     */
    SCPErrorStripeAPIError = 902,
    /**
     The API response from Stripe could not be decoded.
     */
    SCPErrorStripeAPIResponseDecodingError = 903,
} NS_SWIFT_NAME(ErrorCode);

#pragma mark - UserInfo keys

/**
 Use this enum to access userInfo keys for NSError objects under the
 SCPErrorDomain domain.
 */
NS_SWIFT_NAME(ErrorKey)
typedef NSString *const SCPErrorKey NS_STRING_ENUM;

/** 
 An error message explaining what went wrong. You probably shouldn't show this
 to your users, but may want to use it yourself.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyMessage;

/**
 The decline code returned by the Stripe API.

 @see https://stripe.com/docs/api#errors-decline_code
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIDeclineCode;

/**
 If a Stripe API request failed, the failed request's id will be returned in the
 error under this key.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIRequestId;

/**
 The error code returned by the Stripe API.

 @see https://stripe.com/docs/api#errors-code
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIErrorCode;

/**
 The error type returned by the Stripe API.

 @see https://stripe.com/docs/api#errors-type
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIErrorType;

/**
 The documentation URL for the error returned by the Stripe API.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIDocUrl;

/**
 The parameter the error relates to if the error is parameter-specific.

 @see https://stripe.com/docs/api#errors-param
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIErrorParameter;

/**
 The HTTP status code of the response.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyHttpStatusCode;

/**
 If a Stripe API request failed and the error has an associated PaymentIntent,
 the PaymentIntent will be returned under this key.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIPaymentIntent;

/**
 This error message comes from the reader. You probably shouldn't show this
 to your users, but may want to inspect it yourself.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyReaderMessage;

NS_ASSUME_NONNULL_END
