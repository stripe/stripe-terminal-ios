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
FOUNDATION_EXPORT NSString *const SCPErrorDomain;

#pragma mark - SCPError

/**
 Possible error codes for NSError objects under the SCPErrorDomain domain.
 */
typedef NS_ERROR_ENUM(SCPErrorDomain, SCPError){

    /*
     INTEGRATION ERRORS
     */

    /**
     The SDK is busy executing another command. The SDK can only execute a
     single command at a time. You can use the `paymentStatus` or
     `connectionStatus` properties on your `SCPTerminal` instance (or the
     corresponding delegate methods) to determine if the SDK is ready to accept
     another command.
     */
    SCPErrorBusy = 1000,
    /**
     Canceling a command failed because the command already completed.
     */
    SCPErrorCancelFailedAlreadyCompleted = 1010,
    /**
     No reader is connected. Connect to a reader before trying again.
     */
    SCPErrorNotConnectedToReader = 1100,
    /**
     Already connected to a reader.
     */
    SCPErrorAlreadyConnectedToReader = 1110,
    /**
     Your implementation of `fetchConnectionToken` called the completion block
     with `(nil, nil)`. Please make sure your integration completes with either
     a connection token or an error.
     */
    SCPErrorConnectionTokenProviderCompletedWithNothing = 1510,
    /**
     `processPayment` was called with an unknown or invalid PaymentIntent.
     You must process a payment immediately after collecting a payment method.
     */
    SCPErrorProcessInvalidPaymentIntent = 1530,
    /**
     `collectPaymentMethod` or `processPayment` was called with a `nil` PaymentIntent.
     */
    SCPErrorNilPaymentIntent = 1540,
    /**
     `processRefund` was called without calling `collectRefundPaymentMethod`
     beforehand.
     */
    SCPErrorNilRefundPaymentMethod = 1550,
    /**
     The RefundParameters object has invalid values. The Charge ID (ch_123abc)
     can be found on the `PaymentIntent` object, which you should get from
     your backend.
     */
    SCPErrorInvalidRefundParameters = 1555,
    /**
     A PaymentIntent was referenced using an invalid client secret.
     */
    SCPErrorInvalidClientSecret = 1560,
    /**
     The SDK must be actively Discovering Readers in order to successfully
     connect to a reader. See documentation on
     `-[SCPTerminal discoverReaders:delegate:completion:]`
     and `-[SCPTerminal connectReader:completion:]`
     */
    SCPErrorMustBeDiscoveringToConnect = 1570,
    /**
     Before connecting to a reader, it must have already been discovered in the
     current discovery session. Trying to connect to a reader from a previous
     discovery session is not supported.
     */
    SCPErrorCannotConnectToUndiscoveredReader = 1580,
    /**
     `discoverReaders` was called using an invalid SCPDiscoveryConfiguration.
     Your app selected a discovery method that is either incompatible with the
     selected device type or attemped to use `simulated` or `locationId` with a
     reader which does not support `simulated` or `locationId`. Currently
     `chipper2X` is the only reader which supports `simulated` and
     `verifoneP400` is the only reader which supports use of `locationId` for
     location filtering.

     @see `SCPDiscoveryConfiguration` for valid configurations.
     */
    SCPErrorInvalidDiscoveryConfiguration = 1590,
    /**
     No longer used
     */
    SCPErrorInvalidCart = 1600,
    /**
     `collectPaymentMethod` was called with a `nil` `SCPReaderDisplayDelegate`, but
     the `SCPTerminal.connectedReader` does not have a built-in display, and requires that
     your app support displaying messages from the reader to your user.
     */
    SCPErrorNilReaderDisplayDelegate = 1850,
    /**
     `installUpdate` was passed a `nil` `SCPReaderSoftwareUpdate`.
     */
    SCPErrorNilUpdate = 1860,
    /**
     `-[SCPTerminal connectReader:completion:]` was called from an unsupported version
     of the SDK. In order to fix this you will need to update your app to the most recent
     version of the SDK. We suggest you prompt your user to update their app,
     assuming there is an update app version with a supported version of our SDK.

     @see https://github.com/stripe/stripe-terminal-ios/releases/latest
     */
    SCPErrorUnsupportedSDK = 1870,
    /**
     This feature is currently not available for the selected reader.
     */
    SCPErrorFeatureNotAvailableWithConnectedReader = 1880,

    /*
     USER ERRORS
     */

    /**
     The command was canceled by your app.
     */
    SCPErrorCanceled = 2020,

    /**
     Access to location services is currently disabled. This may be because:
     - The user disabled location services in the system settings.
     - The user denied access to location services for your app.
     - The user's device is in Airplane Mode and unable to gather location data.
     */
    SCPErrorLocationServicesDisabled = 2200,
    /**
     This error indicates that Bluetooth is turned off, and the user should use
     Settings to turn Bluetooth on.

     If Bluetooth is on but the app does not have permission to use it,
     a different error (`SCPErrorBluetoothError`) occurs.
     */
    SCPErrorBluetoothDisabled = 2320,
    /**
     Scanning for bluetooth devices timed out.

     @see `SCPDiscoveryConfiguration.timeout`
     */
    SCPErrorBluetoothScanTimedOut = 2330,
    /**
     Bluetooth Low Energy is unsupported on this iOS device. Use a different
     iOS device that supports BLE (also known as Bluetooth 4.0)
     */
    SCPErrorBluetoothLowEnergyUnsupported = 2340,
    /**
     Updating the reader software failed because the reader's battery is
     too low. Charge the reader before trying again.
     */
    SCPErrorReaderSoftwareUpdateFailedBatteryLow = 2650,
    /**
     Updating the reader software failed because the update was interrupted.
     */
    SCPErrorReaderSoftwareUpdateFailedInterrupted = 2660,
    /**
     The card is not a chip card.
     */
    SCPErrorCardInsertNotRead = 2810,
    /**
     The swipe could not be read.
     */
    SCPErrorCardSwipeNotRead = 2820,
    /**
     Reading a card timed out.
     */
    SCPErrorCardReadTimedOut = 2830,
    /**
     The card was removed during the transaction.
     */
    SCPErrorCardRemoved = 2840,
    /**
     A card can only be used for one transaction, and must be removed after
     being read. Otherwise, subsequent `collectPaymentMethod` attempts will fail
     with this error.

     Your terminal delegate will receive `-[SCPTerminalDelegate terminal:didReportReaderEvent:info:]`
     with `SCPReaderEventCardRemoved` when the card is removed.

     The Chipper 2x and WisePad 3 will beep until the card is removed.
     */
    SCPErrorCardLeftInReader = 2850,

    /*
     READER ERRORS
     */

    /**
     The reader is busy.
     */
    SCPErrorReaderBusy = 3010,
    /**
     An incompatible reader was detected. You can only use the Stripe Terminal
     iOS SDK with one of Stripe's pre-certified readers.
     
     @see https://stripe.com/docs/terminal/readers
     */
    SCPErrorIncompatibleReader = 3030,
    /**
     Could not communicate with the reader.
     */
    SCPErrorReaderCommunicationError = 3060,
    /**
     Generic bluetooth error.

     Among other things, it may indicate that the app does not have permission
     to use Bluetooth (iOS 13+).
     */
    SCPErrorBluetoothError = 3200,
    /**
     Connecting to the bluetooth device timed out. Make sure the device is
     powered on, in range, and not connected to another app or device. If this
     error continues to occur, you may need to charge the device.
     */
    SCPErrorBluetoothConnectTimedOut = 3210,
    /**
     The Bluetooth device was disconnected unexpectedly.
     */
    SCPErrorBluetoothDisconnected = 3230,
    /**
     Generic reader software update error.
     */
    SCPErrorReaderSoftwareUpdateFailed = 3800,
    /**
     Updating the reader software failed because there was an error
     communicating with the reader.
     */
    SCPErrorReaderSoftwareUpdateFailedReaderError = 3830,
    /**
     Updating the reader software failed because there was an error
     communicating with the update server.
     */
    SCPErrorReaderSoftwareUpdateFailedServerError = 3840,
    /**
     `-[SCPTerminal processPayment:completion:]` was called from a reader with an
     unsupported reader version. You will need to update your reader to the most
     recent version in order to accept payments. We suggest you prompt your user
     update the reader via the update flow that you have implemented using
     `-[SCPTerminal checkForUpdate:]` and
     `-[SCPTerminal installUpdate:delegate:completion:]`.

     @see https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt#updating-reader-software
     @see https://stripe.com/docs/terminal/readers/bbpos-wisepad3#updating-reader-software
     */
    SCPErrorUnsupportedReaderVersion = 3850,

    /**
     The reader returned from discovery does not have an IP address and cannot
     be connected to. The IP address should have been set by the SDK during
     registration of the reader. Try registering the reader again.

     @see https://stripe.com/docs/terminal/readers/connecting/verifone-p400#register-reader
     */
    SCPErrorUnknownReaderIpAddress = 3860,

    /**
     Connecting to reader over the internet timed out. Make sure your device and
     reader are on the same Wifi network and your reader is connected to the
     Wifi network.
     
     @see https://stripe.com/docs/terminal/readers/verifone-p400#troubleshooting
     */
    SCPErrorInternetConnectTimeOut = 3870,

    /**
     Connecting to the reader failed because it is currently in use
     and `SCPConnectionConfiguration.failIfInUse` was set to `true`.

     Try to connect again with `failIfInUse = false`, or choose a different
     reader.

     A reader is in use while it's collecting a payment.
     @see https://stripe.com/docs/terminal/readers/connecting/verifone-p400#connect-reader-ios
     */
    SCPErrorConnectFailedReaderIsInUse = 3880,

    /*
     UNEXPECTED ERRORS
     */

    /**
     Unexpected SDK error.
     */
    SCPErrorUnexpectedSdkError = 5000,

    /*
     PAYMENT ERRORS
     */

    /**
     The Stripe API declined the payment.
     Inspect `SCPProcessPaymentError.requestError` property for more information about
     the decline, including the decline code.
     */
    SCPErrorPaymentDeclinedByStripeAPI = 6000,
    /**
     The reader declined the payment. Try another card.
     */
    SCPErrorPaymentDeclinedByReader = 6500,
    /**
     The refund failed. The customer’s bank or card issuer was unable to process
     it correctly (e.g., a closed bank account or a problem with the card)
     */
    SCPErrorRefundFailed = 6800,

    /*
     NETWORK ERRORS
     */

    /**
     The SDK is not connected to the internet.
     */
    SCPErrorNotConnectedToInternet = 9000,
    /**
     The underlying request timed out.
     */
    SCPErrorRequestTimedOut = 9010,
    /**
     The underlying request returned an API error.
     */
    SCPErrorStripeAPIError = 9020,
    /**
     The API response from Stripe could not be decoded.
     */
    SCPErrorStripeAPIResponseDecodingError = 9030,
    /**
     Generic network error
     */
    SCPErrorInternalNetworkError = 9040,
    /**
     Your implementation of `-[SCPConnectionTokenProvider fetchConnectionToken:]`
     called the completion block with an error.
     */
    SCPErrorConnectionTokenProviderCompletedWithError = 9050,

    /**
     The current session has expired and the reader must be disconnected and
     reconnected. The SDK will attempt to auto-disconnect for you and you should
     instruct your user to reconnect it.
     `-[SCPTerminalDelegate terminal:didReportUnexpectedReaderDisconnect:]`
     will be called if the SDK is able to successfully auto-disconnect. If it
     does not successfully auto-disconnect (`didReportUnexpectedReaderDisconnect`
     will not be called and `SCPTerminal.connectionStatus` will still be
     `SCPConnectionStatusConnected`) you can attempt again via
     `-[SCPTerminal disconnectReader:]` or you can instruct your user
     to disconnect manually by turning the reader off.

     Note this error will only occur in one of the following calls:

     * `-[SCPTerminal createPaymentIntent:completion:]`
     * `-[SCPTerminal retrievePaymentIntent:completion:]`
     * `-[SCPTerminal collectPaymentMethod:delegate:completion:]` if connected to a Verifone P400 or a BBPOS WisePOS E
     * `-[SCPTerminal processPayment:completion:]`
     * `-[SCPTerminal cancelPaymentIntent:completion:]`
     * `-[SCPTerminal readReusableCard:delegate:completion:]`
     * `-[SCPTerminal collectRefundMethod:parameters]`
     * `-[SCPTerminal processRefund:completion]`

     */
    SCPErrorSessionExpired = 9060,

} NS_SWIFT_NAME(ErrorCode);

#pragma mark - UserInfo keys

/**
 Use this enum to access `userInfo` keys for `NSError` objects under the
 `SCPErrorDomain` domain.
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
 If a refund fails, the reason for refund failure if known. Possible values
 are `lost_or_stolen_card`, `expired_or_canceled_card`, or `unknown`.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIFailureReason;

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
 the `SCPPaymentIntent` will be returned under this key.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyStripeAPIPaymentIntent;

/**
 This error message comes from the reader. You probably shouldn't show this
 to your users, but may want to inspect it yourself.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyReaderMessage;

NS_ASSUME_NONNULL_END
