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
     Error reported while forwarding offline payments when the connection token
     provider neither returns a token nor an error.
     */
    SCPErrorConnectionTokenProviderCompletedWithNothingWhileForwarding = 1511,
    /**
     `confirmPaymentIntent` was called with an unknown or invalid PaymentIntent.
     You must confirm a payment immediately after collecting a payment method.
     */
    SCPErrorConfirmInvalidPaymentIntent = 1530,
    /**
     `collectPaymentMethod` or `confirmPaymentIntent` was called with a `nil` PaymentIntent.
     */
    SCPErrorNilPaymentIntent = 1540,
    /**
     `collectSetupIntentPaymentMethod` or `confirmSetupIntent` was called with
     a `nil` SetupIntent.
     */
    SCPErrorNilSetupIntent = 1542,
    /**
     `confirmRefund` was called without calling `collectRefundPaymentMethod`
     beforehand.
     */
    SCPErrorNilRefundPaymentMethod = 1550,
    /**
     The RefundParameters object has invalid values. The Charge ID (ch_123abc) or PaymentIntent ID (pi_123abc)
     can be found on the `PaymentIntent` object, which you should get from
     your backend. You must have only one of a charge or payment intent ID set.
     */
    SCPErrorInvalidRefundParameters = 1555,
    /**
     A PaymentIntent or SetupIntent was referenced using an invalid client secret.
     */
    SCPErrorInvalidClientSecret = 1560,
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
     `installUpdate` was passed an update that is for a different reader. Updates can only
     be installed on the reader that was connected when the update was announced.
     */
    SCPErrorInvalidReaderForUpdate = 1861,
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

    /**
     This feature is not currently available.
     More details available in the error's `userInfo` in the `SCPErrorKeyMessage` key
     */
    SCPErrorFeatureNotAvailable = 1890,

    /**
     The ListLocationsParameters object has invalid values.
     */
    SCPErrorInvalidListLocationsLimitParameter = 1900,

    /**
     The locationId parameter to BluetoothConnectionConfiguration is required but a valid one was not provided.
     */
    SCPErrorBluetoothConnectionInvalidLocationIdParameter = 1910,

    /**
     A required parameter was invalid or missing.
     */
    SCPErrorInvalidRequiredParameter = 1920,

    /**
     The PaymentIntent uses `on_behalf_of` but the Connected Account ID was not set in SCPLocalMobileConnectionConfiguration:
     https://stripe.com/docs/terminal/payments/connect-reader?terminal-sdk-platform=ios&reader-type=tap-to-pay#connect-reader
     */
    SCPErrorInvalidRequiredParameterOnBehalfOf = 1921,

    /**
     Error reported when forwarding stored offline payments. The fetched connection
     token was generated with a different account ID than the stored payment.
     */
    SCPErrorAccountIdMismatchWhileForwarding = 1930,

    /**
     Error reported when calling collectPaymentMethod with an offline PaymentIntent
     and a CollectConfiguration with updatePaymentIntent set to true.
     */
    SCPErrorUpdatePaymentIntentUnavailableWhileOffline = 1935,

    /**
     Error reported when calling collectPaymentMethod with offline mode enabled
     and a CollectConfiguration with updatePaymentIntent set to true.
     */
    SCPErrorUpdatePaymentIntentUnavailableWhileOfflineModeEnabled = 1936,

    /**
     Error reported when a test payment attempted to forward while operating
     in livemode. The testmode transaction will be deleted.
     */
    SCPErrorForwardingTestModePaymentInLiveMode = 1937,

    /**
     Error reported when a live payment attempted to forward while operating
     in testmode. Reconnect to this account with livemode keys to resume
     forwarding livemode transactions.
     */
    SCPErrorForwardingLiveModePaymentInTestMode = 1938,

    /**
     An invalid ConnectionConfiguration was passed through `connect`.
     */
    SCPErrorReaderConnectionConfigurationInvalid = 1940,

    /**
     Error reported when calling collectPaymentMethod with request dynamic currency conversion
     and a CollectConfiguration with updatePaymentIntent set to false.
     */
    SCPErrorRequestDynamicCurrencyConversionRequiresUpdatePaymentIntent = 1941,

    /**
     Dynamic Currency Conversion is not currently available.
     */
    SCPErrorDynamicCurrencyConversionNotAvailable = 1942,

    /**
     An invalid usage of `eligibleAmount` or `skipTipping` was passed into `collect`.
     */
    SCPErrorReaderTippingParameterInvalid = 1950,

    /**
     The provided location ID parameter was invalid.
     */
    SCPErrorInvalidLocationIdParameter = 1960,


    /**
     * An invalid parameter was used to start a collect inputs operation.
     */
    SCPErrorCollectInputsInvalidParameter = 1997,

    /**
     * Error reported when the connected account does not have access to this feature, or the reader/SDK version is
     * not compatible with the collect inputs operation.
     */
    SCPErrorCollectInputsUnsupported = 1998,

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
     Bluetooth is turned on on the device, but access to Bluetooth has been denied
     for your app. The user needs to go to Settings > Your App > and enable Bluetooth
     */
    SCPErrorBluetoothAccessDenied = 2321,
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
     Updating the reader software failed because the update has expired. Please disconnect and
     reconnect from the reader to retrieve a new update.
     */
    SCPErrorReaderSoftwareUpdateFailedExpiredUpdate = 2670,
    /**
     The reader has a critically low battery and cannot connect to the
     iOS device. Charge the reader before trying again.
     */
    SCPErrorBluetoothConnectionFailedBatteryCriticallyLow = 2680,
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
    /**
     Error reported when the offline payments database has too many records.

     The offline device should be brought back online to sync payments before collecting more.
     */
    SCPErrorOfflinePaymentsDatabaseTooLarge = 2860,

    /**
     Connecting to the reader failed because the most recently connected account
     hasn't connected to a reader of this type while online. To connect to a reader offline,
     the SDK must have connected to a reader of the same type and location within the past 30 days.
     */
    SCPErrorReaderConnectionNotAvailableOffline = 2870,

    /**
     Connecting to the reader failed because the reader was most recently connected
     to a different location while online.
     */
    SCPErrorReaderConnectionOfflineLocationMismatch = 2871,

    /**
     The device software version running on this reader is out of date. You must connect to this
     reader while online to install required updates before this reader can be used for offline payments.
     */
    SCPErrorReaderConnectionOfflineNeedsUpdate = 2872,

    /**
     Connecting to unseen readers offline is disabled. You must connect to this
     reader at this location while online before it can be used for offline payments.
     */
    SCPErrorReaderConnectionOfflinePairingUnseenDisabled = 2873,

    /**
     The SDK has not activated a reader online yet, meaning there is no account
     with which the SDK can associate offline operations.
     */
    SCPErrorNoLastSeenAccount = 2880,

    /**
     Error reported when the PaymentIntent's amount exceeds the configured allowable maximum
     amount for offline transactions.
     */
    SCPErrorAmountExceedsMaxOfflineAmount = 2890,

    /**
     Error reported when the PaymentIntent's currency is not configured as a valid currency
     for offline transactions.
     */
    SCPErrorInvalidOfflineCurrency = 2891,

    /**
     The reader failed to read the data from the presented payment method. If you encounter
     this error repeatedly, the reader may be faulty.
     */
    SCPErrorMissingEMVData = 2892,

    /**
     The command was not permitted to execute by the operating system.
     This can happen for a number of reasons, but most commonly:
     - Your application does not have the necessary entitlements.
     - Your application bundle is invalid.
     */
    SCPErrorCommandNotAllowed = 2900,
    /**
     The mobile device on which the app is running is in an unsupported
     configuration. Verify that the device is running a supported version of
     iOS and that the mobile device has the capability you are attempting to use.
     */
    SCPErrorUnsupportedMobileDeviceConfiguration = 2910,
    /**
     The mobile device on which the app is running must have a passcode set.
     */
    SCPErrorPasscodeNotEnabled = 2920,
    /**
     The card reader cannot be used while a phone call is active.
     */
    SCPErrorCommandNotAllowedDuringCall = 2930,
    /**
     An attempt was made to charge an amount not supported by the reader.
     */
    SCPErrorInvalidAmount = 2940,
    /**
     An attempt was made to charge an amount in a currency not supported by the reader.
     */
    SCPErrorInvalidCurrency = 2950,
    /**
     Failed to accept reader-specific terms of service because there is no iCloud
     user signed in. Direct the user to sign into an appropriate iCloud account
     via iOS Settings and try again.
     */
    SCPErrorAppleBuiltInReaderTOSAcceptanceRequiresiCloudSignIn = 2960,
    /**
     The user cancelled reader-specific terms of service acceptance.
     */
    SCPErrorAppleBuiltInReaderTOSAcceptanceCanceled = 2970,

    /**
     A timeout occurred while processing a collect inputs operation.
     */
    SCPErrorCollectInputsTimedOut = 2971,

    /**
     Scanning for USB devices timed out.

     @see `SCPUsbDiscoveryConfiguration.timeout`
     */
    SCPErrorUsbDiscoveryTimedOut = 2972,

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
     NFC functionality is disabled.
     Among other things, it may indicate that the app does not have permission to use NFC.
     */
    SCPErrorNFCDisabled = 3100,
    /**
     Generic Bluetooth error.

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
     Bluetooth pairing error, the reader has removed this device pairing information.
     Forget the reader in iOS Settings.
     */
    SCPErrorBluetoothPeerRemovedPairingInformation = 3240,
    /**
     The Bluetooth reader is already paired to another device. The Bluetooth reader
     must have its pairing reset to connect to this device.
     */
    SCPErrorBluetoothAlreadyPairedWithAnotherDevice = 3241,
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
     `confirmPaymentIntent` was called from a reader with an unsupported reader
     version. You will need to update your reader to the most recent version in
     order to accept payments. We suggest you prompt your user
     to disconnect and reconnect their reader in order to update the reader.

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

    /**
     The Bluetooth reader has disconnected and we are attempting to reconnect.
     */
    SCPErrorBluetoothReconnectStarted = 3890,

    /**
     An attempt was made to interact with the reader while the the app is in the background.
     */
    SCPErrorReaderNotAccessibleInBackground = 3900,
    /**
     Preparing the Apple Built-In reader to collect payments failed.
     Try connecting again.
     */
    SCPErrorAppleBuiltInReaderFailedToPrepare = 3910,
    /**
     This device cannot be used to process using the Apple Built-In reader as it has been banned.
     */
    SCPErrorAppleBuiltInReaderDeviceBanned = 3920,
    /**
     The operation could not be completed because the reader-specific terms of service have
     not yet been accepted. Try connecting again.
     */
    SCPErrorAppleBuiltInReaderTOSNotYetAccepted = 3930,
    /**
     Failed to accept reader-specific terms of service using the signed-in Apple ID.
     Ensure the Apple ID is still active and in a good standing and try again.
     */
    SCPErrorAppleBuiltInReaderTOSAcceptanceFailed = 3940,
    /**
     This merchant account cannot be used with Apple Built-In reader as it has been blocked.
     */
    SCPErrorAppleBuiltInReaderMerchantBlocked = 3950,
    /**
     This merchant account cannot be used with the Apple Built-In reader as it is invalid.
     */
    SCPErrorAppleBuiltInReaderInvalidMerchant = 3960,

    /**
     An error that indicates the linked Apple ID account has been deactivated by the merchant.
     */
    SCPErrorAppleBuiltInReaderAccountDeactivated = 3970,

    /**
     The reader is missing encryption keys required for taking payments and has disconnected. Reconnect to the reader
     to attempt to re-install the keys. If the error persists, contact support.
     */
    SCPErrorReaderMissingEncryptionKeys = 3980,

    /**
     The USB device was disconnected unexpectedly.
     */
    SCPErrorUsbDisconnected = 3990,

    /*
     UNEXPECTED ERRORS
     */

    /**
     Unexpected SDK error.
     */
    SCPErrorUnexpectedSdkError = 5000,
    /**
     Unexpected reader error.
     */
    SCPErrorUnexpectedReaderError = 5001,
    /**
     Encryption key failed to initialize. Offline payments not available.

     The encryption key needed to decrypt the payment records is not available. This can happen if an iOS backup
     that included offline payment records was restored on a new device. Those records must be forwarded from
     the original device and the records must be deleted from this device.

     Please contact support at https://support.stripe.com/ for more help.
     */
    SCPErrorEncryptionKeyFailure = 5002,
    /**
     Encryption key still initializing. Offline payments are not yet available, please try again.
     */
    SCPErrorEncryptionKeyStillInitializing = 5003,
    /**
     * An unexpected error occurred while processing a collectInputs operation.
     */
    SCPErrorCollectInputsApplicationError = 5004,

    /*
     PAYMENT ERRORS
     */

    /**
     The Stripe API declined the transaction.
     Inspect the error's `requestError` property for more information about
     the decline, including the decline code.
     */
    SCPErrorDeclinedByStripeAPI = 6000,
    /**
     The reader declined the transaction. Try another card.
     */
    SCPErrorDeclinedByReader = 6500,
    /**
     The cardholder must give consent in order for this operation to succeed.
     */
    SCPErrorCommandRequiresCardholderConsent = 6700,
    /**
     The refund failed. The customer’s bank or card issuer was unable to process
     it correctly (e.g., a closed bank account or a problem with the card)
     */
    SCPErrorRefundFailed = 6800,

    /**
     Error reported when collectPaymentMethod or confirmPaymentIntent was called while
     offline and the card was read using the swipe method.

     Payment method data collected using the Swipe card read method cannot be processed online.

     Retry the payment by calling `collectPaymentMethod()` again.
     */
    SCPErrorCardSwipeNotAvailable = 6900,

    /**
     Error reported when collectPaymentMethod or confirmPaymentIntent was called while
     offline and the presented card was an Interac card.

     Retry the payment by calling `collectPaymentMethod()` again.
     */
    SCPErrorInteracNotSupportedOffline = 6901,

    /**
     Confirming a payment while offline and the card was identified as being expired.
     */
    SCPErrorOfflineAndCardExpired = 6902,

    /**
     Confirming a payment while offline and the card's verification failed.

     Retry the payment by calling `collectPaymentMethod()` again and try a different card if the error persists.
     */
    SCPErrorOfflineTransactionDeclined = 6903,

    /**
     Error reported when collectPaymentMethod was called while online
     and confirmPaymentIntent was called while offline.

     Retry the payment by calling `collectPaymentMethod()` again.
     */
    SCPErrorOfflineCollectAndConfirmMismatch = 6904,

    /**
     Error reported when confirmPaymentIntent was called while
     offline and the presented card was authenticated with an online PIN.
     Retry the payment with another card.
     */
    SCPErrorOnlinePinNotSupportedOffline = 6905,

    /**
     Error reported when the card used is a known test card and the SDK is operating in livemode.
     */
    SCPErrorOfflineTestCardInLivemode = 6906,

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
     Error reported while forwarding offline payments when the connection token
     provider returns an error.
     */
    SCPErrorConnectionTokenProviderCompletedWithErrorWhileForwarding = 9051,
    /**
     Your implementation of `-[SCPConnectionTokenProvider fetchConnectionToken:]`
     did not call the provided completion block within 60 seconds.
     */
    SCPErrorConnectionTokenProviderTimedOut = 9052,

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
     * `-[SCPTerminal collectPaymentMethod:delegate:completion:]` if connected to an Internet reader
     * `-[SCPTerminal confirmPaymentIntent:completion:]`
     * `-[SCPTerminal cancelPaymentIntent:completion:]`
     * `-[SCPTerminal collectRefundMethod:parameters]` if connected to an Internet reader
     * `-[SCPTerminal confirmRefund:completion]`
     * `-[SCPTerminal createSetupIntent:completion:]`
     * `-[SCPTerminal collectSetupIntentPaymentMethod:customerConsentCollected:completion:]` if connected to an Internet reader
     * `-[SCPTerminal confirmSetupIntent:completion:]`
     * `-[SCPTerminal cancelSetupIntent:completion:]`
     * `-[SCPTerminal collectInputs:completion:]`

     */
    SCPErrorSessionExpired = 9060,
    /**
     Error reported when the iOS device is offline and the PaymentIntent was created with
     `offlineBehavior` set to `requireOnline`.
     */
    SCPErrorNotConnectedToInternetAndOfflineBehaviorRequireOnline = 10106,

    /**
     Error reported when a `SCPPaymentIntent` was created with `SCPOfflineBehaviorForceOffline`
     and the reader in use is not configured to operate offline. Use the Terminal Configuration API to enable
     the functionality or retry with another value for `SCPOfflineBehavior`.
     */
    SCPErrorOfflineBehaviorForceOfflineWithFeatureDisabled = 10107,

} NS_SWIFT_NAME(ErrorCode);

#pragma mark - UserInfo keys

/**
 Use this enum to access `userInfo` keys for `NSError` objects under the
 `SCPErrorDomain` domain.
 */
typedef NSString *const SCPErrorKey NS_STRING_ENUM NS_SWIFT_NAME(ErrorKey);

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
 If a decline occurs while offline, the reason for the failure.
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyOfflineDeclineReason;

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

/**
 If an Apple Built-In reader fails to connect due to a device ban and the error
 has an associated ban expiry date, the `NSDate` will be returned
 under this key.
 @see SCPErrorAppleBuiltInReaderDeviceBanned
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyDeviceBannedUntilDate;

/**
 If an Apple Built-In reader fails to prepare and includes an associated reason string,
 the associated `NSString` will be returned under this key.
 @see SCPErrorAppleBuiltInReaderFailedToPrepare
 */
FOUNDATION_EXPORT SCPErrorKey SCPErrorKeyPrepareFailedReason;

NS_ASSUME_NONNULL_END
