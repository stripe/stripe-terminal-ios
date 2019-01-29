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
     INTEGRATION ERRORS
     */
    /**
     The SDK is busy executing another command. The SDK can only execute a
     single command at a time. You can use the `paymentStatus` or
     `connectionStatus` properties on your `SCPTerminal` instance (or the
     corresponding delegate methods) to determine if the SDK is ready to accept
     another command.
     */
    SCPErrorBusy = 100,
    /**
     The command was canceled by your app.
     */
    SCPErrorCanceled = 102,
    /**
     Access to location services is currently disabled. This may be because:
     - The user disabled location services in the system settings.
     - The user denied access to location services for your app.
     - The user's device is in Airplane Mode and unable to gather location data.
     */
    SCPErrorLocationServicesDisabled = 150,
    /**
     Your implementation of `fetchConnectionToken` called the completion block
     with (nil, nil). Please make sure your integration completes with either
     a connection token or an error.
     */
    SCPErrorConnectionTokenProviderCompletedWithNothing = 151,
    /**
     Your implementation of `fetchConnectionToken` called the completion block
     with an error.
     */
    SCPErrorFetchConnectionTokenCompletedWithError = 152,
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
     The SDK must be actively Discovering Readers in order to successfully
     connect to a reader. See documentation on `SCPTerminal` methods
     `discoverReaders:delegate:completion:` and `connectReader:completion:`
     */
    SCPErrorMustBeDiscoveringToConnect = 157,
    /**
     Before connecting to a reader, it must have already been discovered in the
     current discovery session. Trying to connect to a reader from a previous
     discovery session is not supported.
     */
    SCPErrorCannotConnectToUndiscoveredReader = 158,

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
     UNEXPECTED ERRORS
     */
    /**
     Unexpected SDK error.
     */
    SCPErrorUnexpectedSdkError = 500,

    /**
     PAYMENT ERRORS
     */
    /**
     The Stripe API declined the payment.
     Inspect SCPConfirmError's requestError property for more information about
     the decline, including the decline code.
     */
    SCPErrorPaymentDeclinedByStripeAPI = 600,
    /**
     The reader declined the payment. Try another card.
     */
    SCPErrorPaymentDeclinedByReader = 650,
    /**
     The card is not a chip card.
     */
    SCPErrorCardInsertNotRead = 651,
    /**
     The swipe could not be read.
     */
    SCPErrorCardSwipeNotRead = 652,
    /**
     Reading a card timed out.
     */
    SCPErrorCardReadTimedOut = 653,
    /**
     The card was removed during the transaction.
     */
    SCPErrorCardRemoved = 654,


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
    /**
     Generic network error
     */
    SCPErrorInternalNetworkError = 904,
    
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
