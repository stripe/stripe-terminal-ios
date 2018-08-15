//
//  NSError+StripePOS.h
//  StripePOS
//
//  Created by Ben Guo on 7/26/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The error domain for all errors originating from the StripePOS SDK.
 */
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
     An unexpected error occurred.
     */
    SCPErrorUnexpectedError = 0,
    /**
     Generic SDK error.
     */
    SCPErrorSDKError = 1,
    /**
     Generic reader error.
     */
    SCPErrorReaderError = 3,
    /**
     Generic card error.
     */
    SCPErrorCardError = 6,
    /**
     Generic network error.
     */
    SCPErrorNetworkError = 9,

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
     The reader declined the payment.
     */
    SCPErrorPaymentDeclinedByReader = 104,

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
     There was an error communicating with the ActivationTokenProvider.
     Make sure:
     - Your implementation of `getToken` calls the given completion block
     either a String or an error.
     - Your app strongly retains your SCPActivationTokenProvider.
     */
    SCPErrorActivationTokenProviderIntegrationError = 151,
    /**
     confirmPaymentIntent was called with an unknown or invalid PaymentIntent.
     You must confirm a payment intent immediately after attaching a source.
     */
    SCPErrorConfirmInvalidIntent = 153,
    /**
     attachSource or confirmPaymentIntent was called with a nil PaymentIntent.
     */
    SCPErrorNilPaymentIntent = 154,


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
     An incompatible reader was detected. Connect a reader matching the
     deviceType specified in SCPTerminalConfiguration.
     */
    SCPErrorIncompatibleReader = 302,
    /**
     No reader was discovered.
     */
    SCPErrorNoReadersDetected = 303,
    /**
     The reader is busy.
     */
    SCPErrorReaderBusy = 305,
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
     powered on and in range.
     */
    SCPErrorBluetoothConnectTimedOut = 324,
    /**
     Generic reader update error.
     */
    SCPErrorReaderUpdateFailed = 380,
    /**
     Updating the reader failed because the reader's battery is
     too low. Charge the reader before installing the update.
     */
    SCPErrorReaderUpdateFailedBatteryLow = 381,
    /**
     Updating the reader failed because no update is required.
     */
    SCPErrorNoReaderUpdateRequired = 382,

    /**
     CARD ERRORS
     */
    /**
     The card is not a chip card.
     */
    SCPErrorCardNotChipCard = 600,
    /**
     The swipe could not be read.
     */
    SCPErrorCardSwipeNotRead = 601,
    /**
     Reading a card timed out.
     */
    SCPErrorReadCardTimedOut = 602,
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
     The API response could not be decoded.
     */
    SCPErrorStripeAPIResponseDecodingError = 903,
};

#pragma mark - UserInfo keys

/**
 Use this enum to access userInfo keys for NSError objects under the
 SCPErrorDomain domain.
 */
typedef NSString *const SCPErrorKey NS_STRING_ENUM;

/** 
 An error message explaining what went wrong. You probably shouldn't show this
 to your users, but may want to use it yourself.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyMessage;

/**
 The decline code returned by the Stripe API.
 https://stripe.com/docs/api#errors-decline_code
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIDeclineCode;

/**
 If a Stripe API request failed, the failed request's id will be returned in the
 error under this key.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIRequestId;

/**
 The error code returned by the Stripe API.
 https://stripe.com/docs/api#errors-code
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIErrorCode;

/**
 The error type returned by the Stripe API.
 https://stripe.com/docs/api#errors-type
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIErrorType;

/**
 The parameter the error relates to if the error is parameter-specific.
 https://stripe.com/docs/api#errors-param
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIErrorParameter;

/**
 If a Stripe API request failed and the error has an associated payment intent,
 the payment intent will be returned under this key.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIPaymentIntent;

/**
 This error message comes from the reader. You probably shouldn't show this
 to your users, but may want to inspect it yourself.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyReaderErrorMessage;

NS_ASSUME_NONNULL_END
