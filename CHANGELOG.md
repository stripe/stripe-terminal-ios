# Stripe Terminal iOS SDK changelog

This document details changes made to the SDK by version. The current status
of each release can be found in the [Support Lifecycle](SUPPORT.md).

If you are using CocoaPods, update your Podfile:
```
pod 'StripeTerminal', '~> 3.0'
```
# 3.0.0 2023-09-08
3.0.0 includes breaking changes in both symbols and behavior. See the [migration guide](https://stripe.com/docs/terminal/references/sdk-migration-guide?terminal-sdk-platform=ios) for more details.

* Built with Xcode 14.3, Swift version 5.8.
* New: Private beta support for offline payments.
    * See [Collect payments while offline](https://stripe.com/docs/terminal/features/operate-offline/collect-payments) for details.
* Update: Minimum deployment target updated from iOS 11.0 to iOS 13.0. 
* Update: `SCPPaymentIntent.stripeId` is now nullable to support offline payments.
* Update: `Terminal.processPayment` has been renamed to `Terminal.confirmPaymentIntent`.
* Update: `Terminal.processRefund` has been renamed to `Terminal.confirmRefund`.
* Update: `ReconnectionDelegate` methods now provide the instance of the `Reader` that is being reconnected to instead of the `Terminal` instance.
* Update: Removed the `SCPErrorBusy` error. The SDK will now queue incoming commands if another command is already running.
* Update: Removed `SCPErrorCannotConnectToUndiscoveredReader` and `SCPErrorMustBeDiscoveringToConnect` errors. The SDK now supports connecting to an `SCPReader` instance that was previously discovered without needing to restart discovery.
* Update: Removed `Terminal.readReusableCard`. This functionality is replaced by [SetupIntents](https://stripe.com/docs/terminal/features/saving-cards/save-cards-directly?terminal-sdk-platform=ios).
* Update: `discoverReaders` is now completed when `connectReader` is called. This is a behavior change from 2.x where `discoverReaders` would continue running until connect succeeded. If connect fails you can retry connecting to a previously discovered `SCPReader` or restart `discoverReaders`.
* Update: Canceling `discoverReaders` now completes with an `SCPErrorCanceled` error. Previously no error was provided when canceled.
* Update: `DiscoveryConfiguration` is now a protocol with concrete classes for each discovery method: `BluetoothScanDiscoveryConfiguration`, `BluetoothProximityDiscoveryConfiguration`, `InternetDiscoveryConfiguration`, and `LocalMobileDiscoveryConfiguration`. Each class has a `Builder` exposing only the configuration values that apply to that discovery method.
* Update: Configuration and parameter classes are now immutable and need to be built with builders. Example: To create `SCPPaymentIntentParameters` use `SCPPaymentIntentParametersBuilder` which has setters for all the parameters and a `build:` method to create the `SCPPaymentIntentParameters` instance.
* Update: Removed `CardDetails.fingerprint` and `CardPresentDetails.fingerprint`. You will still be able to access the fingerprint server-side using [Stripe server-side SDKs](https://stripe.com/docs/libraries#server-side-libraries).
* Fixes [#240](https://github.com/stripe/stripe-terminal-ios/issues/240): `SCPDiscoveryConfiguration.timeout` is now respected when using simulated Bluetooth scan.

# 2.23.2 2023-09-18
* Built with Xcode 14.3, Swift version 5.8.
* Fixes an issue where the SDK wouldn't announce an unexpected disconnect if an internet reader receives an invalid session error. This can happen after the reader reboots while the SDK is in the background.
* Fixes [#252](https://github.com/stripe/stripe-terminal-ios/issues/252): `SCPLocalMobileConnectionConfiguration` `- initWithLocationId:merchantDisplayName:onBehalfOf:tosAcceptancePermitted:` now correctly sets the `tosAcceptancePermitted` value in the retuned configuration.

# 2.23.1 2023-08-08
* Built with Xcode 14.3, Swift version 5.8.
* Fixes a regression in 2.21.0 where the SDK could get stuck running `discoverReaders` if `connectBluetoothReader` failed and the discovery cancelable was canceled in the connect completion block.

# 2.23.0 2023-07-31
* Built with Xcode 14.3, Swift version 5.8.
* Support for CVM PIN transactions when using Tap to Pay on iPhone. See [Tap to Pay on iPhone docs](https://stripe.com/docs/terminal/payments/setup-reader/tap-to-pay?platform=ios) for specifics on supported countries and payment methods.
* Fixes a bug where connecting to an internet reader after being connected to a Bluetooth reader could error with "ConnectionToken has already been redeemed".
* Provides additional debugging information when an Apple Built-In reader fails to prepare. See the new `SCPErrorKeyPrepareFailedReason` error key.
* Fixes a regression where `SCPErrorUnexpectedSdkError` would be returned when connecting to a reader without `discoverReaders` running. Now returns a specific error, `SCPErrorMustBeDiscoveringToConnect`.

# 2.22.0 2023-07-05
* Built with Xcode 14.3, Swift version 5.8.
* Tap to Pay on iPhone now returns card read results immediately by default on iOS 16.4+ to reduce transaction time.
* Fixes [#229](https://github.com/stripe/stripe-terminal-ios/issues/229): `connectedReader` and `connectionStatus` is now correctly set when the `disconnectReader` completion block is run when using the simulated Bluetooth reader.
* Fixes [#232](https://github.com/stripe/stripe-terminal-ios/issues/232): `didReportBatteryLevel` now correctly reports `batteryLevel` as a float between 0 and 1 as documented.

# 2.21.0 2023-06-05
* Built with Xcode 14.1, Swift version 5.7.1.
* Fixes a bug where `collectPaymentMethod` could have failed with "Transaction is cancelled by the user" shortly after calling `collectPaymentMethod`.
* Reduces the latency of subsequent attempts to connect to an Apple Built-In reader.
* Fixes a crash if the `discoverReaders` cancelable was canceled in `didUpdateDiscoveredReaders` after `connectReader` failed connecting to the reader.
* Added a new simulated test card `.visaUsCommonDebit` [`SCPSimulatedCardType`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPSimulatedCardType.html).
* Fixes a bug where `processPayment` could result in an error stating "This PaymentIntent could not be updated because it has a status of succeeded" on slow networks.
* Fixes a crash if the reader disconnects during the `/confirm` API request as part of `processPayment`.

# 2.20.2 2023-05-24
* Fixes a regression in 2.20.0 where `retrieveSetupIntent` would fail with an API error stating "The provided key 'pss_test_*****************' does not have the required permissions for this endpoint"

# 2.20.1 2023-05-16
* Fixes a latent bug where closing and reopening the app several times leads to increased CPU usage.

# 2.20.0 2023-05-01
* Fixes a possible crash if a Bluetooth reader disconnects while `connectBluetoothReader` is running.
* Fixes a bug where a `PaymentIntent` created with `captureMethod` set to `automatic` may, under poor network conditions, have a `status` of `requires_capture`, when it should have had a `status` of `succeeded`.
* Added error [`SCPErrorConnectionTokenProviderTimedOut`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorConnectionTokenProviderTimedOut). Returned when the [`SCPConnectionTokenProvider`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPConnectionTokenProvider.html#/c:objc(pl)SCPConnectionTokenProvider(im)fetchConnectionToken:) does not call the provided completion block within 60 seconds.
* Throws an error when attempting to use the simulated `.eftposAuDebit` card with an unsupported PaymentIntent capture method. Use this card with the capture method set to `SCPCaptureMethodAutomatic` or `SCPCardPresentCaptureMethodManualPreferred`.
* Added `SCPReaderDisplayMessageCardRemovedTooEarly` sent when a card is removed too early during a contact payment.
* Fixes a bug where the SDK would fail `processPayment` with `SCPErrorDeclinedByStripeAPI` if the WisePad 3 timed out in between `collectPaymentMethod` and `processPayment`. This will now error with `SCPErrorCardReadTimedOut`. 
* Fixes a bug where `SCPReaderEventCardInserted` could be announced multiple times for a single card insert.

# 2.19.1 2023-04-10
* Fixes an issue where the SDK could get stuck in an "AlreadyConnectedToReader" state when using Tap to Pay on iPhone.

# 2.19.0 2023-04-03
* New: Cancel `PaymentIntent` and `SetupIntent` via the SDK when connected to an internet reader by calling [`cancelPaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)cancelPaymentIntent:completion:) or [`cancelSetupIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)cancelSetupIntent:completion:) instead of using your backend.
    * _Note: This feature requires version `2.11.0.24` or later to be installed on your internet reader._
* Added [`authorizationCode`](https://stripe.com/docs/api/charges/object#charge_object-payment_method_details-card_present-receipt-authorization_code) to [`SCPReceiptDetails`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPReceiptDetails.html).
* Added support for simulating an on-reader tip amount to the [`SCPSimulatorConfiguration`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPSimulatorConfiguration.html) when collecting and processing a payment using a simulated reader.
* Add two new simulated test cards: `.eftposAuVisaDebit` & `.eftposAuDebitMastercard` to [ `SCPSimulatedCardType`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPSimulatedCardType.html)
* Added [`captureMethod`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPPaymentIntent.html#/c:objc(cs)SCPPaymentIntent(py)captureMethod) property to `SCPPaymentIntent`.

# 2.18.1 2023-03-15
* Fixes an issue where the SDK may report a failure during `processPayment` when using a WisePad 3 and the reader times out waiting for the /confirm response from the Stripe API. The SDK will now will report success if the PaymentIntent status moved to `requires_capture` or `succeeded`.

# 2.18.0 2023-03-06
* New: Create `PaymentIntent` and `SetupIntent` via the SDK when connected to an internet reader by calling [`createPaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)createPaymentIntent:completion:) or [`createSetupIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)createSetupIntent:completion:) instead of using your backend.
    * _Note: This feature requires version `2.10.1.0` or later to be installed on your internet reader._
* Fixed bug where the SDK may have not called [`reader:didReportReaderEvent:info:`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)reader:didReportReaderEvent:info:) or [`reader:didRequestReaderInput:`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)reader:didRequestReaderInput:) when it should have.
* Fixed an issue where faulty readers may fail `processPayment` with "You passed an empty string for 'payment_method_data[card_present][emv_data]'". These readers will now fail `collectPaymentMethod` with error code `SCPErrorMissingEMVData`.

# 2.17.1 2023-02-07
* Fixes an issue where the SDK may report a failure during `processPayment` if a reader error or disconnect is received while process is in-progress but the /confirm request was successful. The SDK will now wait for the /confirm API response and will report success if the PaymentIntent status moved to `requires_capture` or `succeeded`.

# 2.17.0 2023-01-30
* Added [`amountTip`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPPaymentIntent.html#/c:objc(cs)SCPPaymentIntent(py)amountTip) to `PaymentIntent` that represents the on-reader tip amount, if any, in the Payment Intent returned after `collectPaymentMethod` when using [`updatePaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPCollectConfiguration#/c:objc(cs)SCPCollectConfiguration(py)updatePaymentIntent).
* Added missing type annotations of `<NSString *, NSString *>` to all `metadata` dictionaries.
* Added support for creating Payment Intents with a requested routing priority (`SCPCardPresentRouting`) set on the [`SCPCardPresentParameters`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPCardPresentParameters.html).
* Added [`CardPresentDetails.incrementalAuthorizationStatus`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPIncrementalAuthorizationStatus.html) which indicates whether incremental authorizations are supported or not after the `PaymentIntent` has been confirmed.
* Added Statement descriptor suffix field added to `PaymentIntentParameters`, `PaymentIntent`, and `Charge`.
* Added calculated statement descriptor field to `Charge`.
* Added more supported currency symbols when collecting payments with a WisePad 3.
* Fixes [#145](https://github.com/stripe/stripe-terminal-ios/issues/145): Tip amounts are now accessible through the [`PaymentIntent.amountDetails`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPPaymentIntent.html#/c:objc(cs)SCPPaymentIntent(py)amountDetails) object.
* Fixes [#119](https://github.com/stripe/stripe-terminal-ios/issues/119): `metadata` on `RefundParameters` is now correctly set when collecting a refund with a WisePOS E.
* Fixes [#184](https://github.com/stripe/stripe-terminal-ios/issues/184): `SCPAppleBuiltInReaderErrorCodeNotAllowed` is now returned more consistently when attempting to discover Tap to Pay on iPhone readers on apps with a missing entitlement.
* Fixes [#199](https://github.com/stripe/stripe-terminal-ios/issues/199): `deviceSoftwareVersion` on `Reader` could start returning `fw-config-ksid` instead of the reader's correct software version.

# 2.16.1 2022-12-20
* Fixes an on-reader tipping issue when collecting tips using WisePad 3 readers. If a cardholder selected a tip, they presented their card contactlessly, and the transaction was soft declined due to Strong Customer Authentication (SCA), the tip amount was not included in the authorization amount.

# 2.16.0 2022-12-12
* Added `-no-serialize-debugging-options` to Swift flags to fix lldb "couldn't IRGen expression" issue when trying to do anything in lldb.
* Fixed an issue where the SDK could stop responding or incorrectly report `CardLeftInReader` if an unsupported card was inserted during the previous transaction.

# 2.15.0 2022-11-21
* Added support for creating Payment Intents with `SCPCardPresentCaptureMethodManualPreferred` capture method set on the [`SCPCardPresentParameters`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPCardPresentParameters.html).
* Fixes an issue where `processRefund` and `confirmSetupIntent` were returning error `SCPErrorUnexpectedSdkError` instead of `SCPErrorBusy` or `SCPErrorNotConnectedToReader` for those error cases.

# 2.14.0 2022-10-31
* Minimum deployment target changed from iOS 10.0 to iOS 11.0
* Added support for [Tap to Pay on iPhone](https://stripe.com/docs/terminal/payments/setup-reader/tap-on-mobile-ios#get-started).
* Added new [`SCPTippingConfiguration`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTippingConfiguration.html) property on `SCPCollectConfiguration`, which allows for per-transaction tip-eligible amounts to be set on the BBPOS WisePos E. See [Stripe documentation](https://stripe.com/docs/terminal/features/collecting-tips/on-reader#tip-eligible) for details.
* Fixes [Issue #176](https://github.com/stripe/stripe-terminal-ios/issues/176): Fixed warning from the SDK umbrella header, StripeTerminal.h, missing an import.

# 2.13.0 2022-10-03
* Added new [`updatePaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPCollectConfiguration.html#/c:objc(cs)SCPCollectConfiguration(py)updatePaymentIntent) to `SCPCollectConfiguration` which will attach a PaymentMethod to the server-side PaymentIntent and provide that [`SCPPaymentMethod`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPPaymentIntent.html#/c:objc(cs)SCPPaymentIntent(py)paymentMethod) on the `SCPPaymentIntent` returned during `collectPaymentMethod`. See [Stripe documentation](https://stripe.com/docs/terminal/payments/collect-payment?terminal-sdk-platform=ios#collect-inspect-payment-method) for details.
* Added new [`networks`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPNetworks.html) to `SCPCardPresentDetails`. The networks property will only be present in the PaymentIntent returned during collect when using `updatePaymentIntent` set to true.
* Fixed an issue where `CardLeftInReader` could incorrectly be returned during `collectPaymentMethod` if the card was inserted prior to the collect call.

# 2.12.0 2022-08-29
* Bug fix: Attempting to connect to a smart reader after an unexpected disconnect no longer errors with "The Stripe Terminal ConnectionToken has already been redeemed".
* Added support for new currency: Czech koruna ( CZK ) in the Example Terminal app.
* Added better handling for intermittent network connectivity during payment confirmation.
* Fixes [Issue #166](https://github.com/stripe/stripe-terminal-ios/issues/166): Removed asserts for missing Info.plist keys if running in a test environment.
* Bug fix: `platform_api_key_expired` API errors now get reported as `SCPErrorSessionExpired` instead of `SCPErrorStripeAPIError`.
* Increased the collectPaymentMethod timeout from 5 minutes to 60 minutes.
* WisePad 3 only: Increased account type selection timeout from 60 seconds to 90 seconds to match application selection timeout of 90 seconds.

# 2.11.0 2022-07-25
* Added an automatic capture toggle to example app on the collect card payment view controller.
* Added `autoReconnectOnUnexpectedDisconnect` and `autoReconnectionDelegate` to the [`SCPBluetoothConnectionConfiguration`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPBluetoothConnectionConfiguration.html). When `autoReconnectOnUnexpectedDisconnect` is enabled, the SDK will attempt to restore connection upon any unexpected disconnect to a reader. See [Stripe documentation](https://stripe.com/docs/terminal/payments/connect-reader?terminal-sdk-platform=ios&reader-type=bluetooth#automatic-reconnection) for details.

# 2.10.0 2022-06-27
* Added `[SCPPaymentIntentParameters initWithAmount:currency:paymentMethodTypes:captureMethod:]` and `[SCPPaymentIntentParameters initWithAmount:currency:captureMethod:]`. Allows users to opt-in to automatically capturing payments. Existing integrations are unaffected as they will continue to default to manual capture, `SCPCaptureMethodManual`.

# 2.9.1 2022-06-02
* Fixes [Issue #155](https://github.com/stripe/stripe-terminal-ios/issues/155): Bluetooth readers would not correctly identify the `SCPErrorCardLeftInReader` error if the previous transactions card was left in the reader when calling `collectPaymentMethod`.

# 2.9.0 2022-05-23
* Added compatibility work to support our upcoming React Native SDK.

# 2.8.0 2022-04-25

* Added error, `SCPErrorInvalidRequiredParameter`, reported when a required parameter was invalid or missing. This does not replace more specific errors like `SCPErrorNilPaymentIntent` and `SCPErrorProcessInvalidPaymentIntent`, but will be returned when other unexpected inputs were invalid, such as passing a nil or empty string as the client secret into `retrievePaymentIntent:completion:`.
* Bug fix: Previously, `SCPErrorUnexpectedSdkError` was returned when retrying `processPaymentIntent:` after a previous `processPaymentIntent:` completed with an error. Now, this behavior should not fail.
* Bug fix: Location requests no longer time out if Terminal is initialized on a background thread. Previously, even if the device had an accurate location a location request could time out and cause a 5 second delay during `processPayment`. This was reported in #143.

# 2.7.0 2022-03-28

* Bug fix: In certain conditions, after connecting to a reader that had previously been connected to a different device, operations would erroneously fail with an error indicating an API key had expired.
* Updated the Bluetooth proximity discovery method error reported when Bluetooth permission is unauthorized from generic BluetoothError to the more specific BluetoothAccessDenied.
* Updated internal dependencies.
* Beta: Incremental or extended authorization can be requested with `CardPresentParameters` and
  `PaymentMethodOptionsParameters` objects. See [extended authorizations](https://stripe.com/docs/terminal/features/extended-authorizations#authorization-validity) and [incremental authorizations](https://stripe.com/docs/terminal/features/incremental-authorizations)


# 2.6.0 2022-02-28
* Adds support for using [SimulatedCard](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPSimulatorConfiguration.html#/c:objc(cs)SCPSimulatorConfiguration(py)simulatedCard) with simulated Internet readers. Note the `SimulatedCard` is still not supported when performing a card-present refund with a simulated Internet reader.
* Simulated Bluetooth Proximity discovery will now return a simulated Stripe Reader M2 device instead of a BBPOS Chipper 2X BT.
* Addressses [Issue #133](https://github.com/stripe/stripe-terminal-ios/issues/133): Fixes a bug where connecting to an internet reader then calling `cancel()` on the discovery cancelable would cause the SCPTerminal singleton to not reset state properly if that connection fails. As a result, the SCPTerminal singleton would prevent you from restarting discovery.
* Adds `CollectConfiguration` object to provide an option to skip tipping during `collectPaymentMethod`. See [Collect on-reader tips](https://stripe.com/docs/terminal/features/collecting-tips/on-reader) for details. Note that on-reader tips is in beta.
* Adds `CollectConfiguration` as a parameter on `collectPaymentMethod` to suppress [on-reader tipping on the BBPOS WisePOS E](https://stripe.com/docs/terminal/features/collecting-tips/on-reader)

# 2.5.0 2022-01-24
* Adds a new error code, `SCPErrorBluetoothConnectionFailedBatteryLow`, that is passed into the `connectBluetoothReader` completion handler when connection failed due to the reader's battery being critically low.
* Fixes [Issue #124](https://github.com/stripe/stripe-terminal-ios/issues/124): Crash when Bluetooth reader reports low battery but BluetoothReaderDelegate was released.
* Fixes [Issue #121](https://github.com/stripe/stripe-terminal-ios/issues/121): `SCPReader` `isCharging` and `batteryLevel` weren't being updated if the `SCPBluetoothReaderDelegate` `didReportBatteryLevel:` wasn't implemented.

# 2.4.0 2021-11-15
* Add 4 new simulated test cards: `.onlinePinCvm`, `.onlinePinScaRetry`, ` .offlinePinCvm`, & `.offlinePinScaRetry` to [ `SCPSimulatedCardType`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPSimulatedCardType.html)
* Fixes [Issue #119](https://github.com/stripe/stripe-terminal-ios/issues/119): Refund metadata not being set. The fix only applies to Bluetooth readers for now. Internet readers will still be missing the metadata.

# 2.3.0 2021-10-18

* Update: WisePad 3 processing timeout increased from 15 seconds to 30 seconds.
* Update: Added a simulated Stripe M2 device during simulated Bluetooth scan discovery.
* Bug fix: Fixed `SCPSimulateReaderUpdateLowBattery` so it more closely matches a real update and announces `didStartInstallingUpdate` and `didFinishInstallingUpdate`.
* [Issue #115](https://github.com/stripe/stripe-terminal-ios/issues/115): Fixed requests to cancel `collectPaymentMethod` with a WisePad 3 during application, PIN, or account selection now cancel immediately.
* [Issue #104](https://github.com/stripe/stripe-terminal-ios/issues/104): Fixed missing call to `didUpdateDiscoveredReaders:` with an empty array if the last Bluetooth reader was turned off or goes out of range.
* [Issue #114](https://github.com/stripe/stripe-terminal-ios/issues/114): Fixed possible missing calls to `didReportReaderEvent:` when removing a card during `collectPaymentMethod`.
* Updated internal dependencies.

# 2.2.0 2021-09-20

* Bug fix: Fixed a possible deadlock when calling `readReusableCard` and `processPayment` from background threads.
* [Issue #111](https://github.com/stripe/stripe-terminal-ios/issues/111): Replaced `__IPHONE_OS_VERSION_MIN_REQUIRED` that was causing some trouble with `API_AVAILABLE(ios(10.0))`.
* Updated internal dependencies.
* Added public convenience methods `stringFromCardBrand:` and `stringFromPaymentIntentStatus:`.

# 2.1.1 2021-08-30

* Bug fix: Fixed a crash if a Bluetooth reader disconnected during `processPayment`.

# 2.1.0 2021-08-23

* Added [`SCPSimulateReaderUpdateLowBattery`](https://site-admin.stripe.com/docs/terminal/testing#simulated-reader-updates) which can be used to simulate an update that fails due to a reader's low battery level.
* Added [`setupFutureUsage`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPPaymentIntentParameters.html#/c:objc(cs)SCPPaymentIntentParameters(py)setupFutureUsage) to `SCPPaymentIntentParameters`.
* Invite only: Added support for [`SetupIntents`](https://stripe.com/docs/api/setup_intents) with the WisePos E, Chipper 2X BT, and Stripe Reader M2 (SetupIntents was previously only supported with the WisePad 3).
* Updated example app to show both Read Reusable Card and Create Setup Intent (beta) workflows.
* Updated example app with more currencies in the payment flow and more countries when creating locations from the app.
* Bug fix: Calling `discoverReaders` via `.bluetoothScan` early in application startup should now always discover nearby readers fixing a bug where the discover call may not return the nearby readers.
* Bug fix: Calling `processPayment` after the WisePad 3 has timed out now correctly returns a declined error instead of `UnexpectedSDKError`.
* Bug fix: When connecting to a simulated Bluetooth reader and simulating a required update, canceling the update now correctly restarts the simulated discovery process and re-discovers simulated readers.
* Updated internal dependencies.

# 2.0.1 2021-07-14

* Bug fix: When using the WisePad 3, not calling `processPayment` after a successful `collectPaymentMethod` could cause the SDK to become unresponsive. This is now fixed.
* Bug fix: When disconnected from an Internet reader the `connectionStatus` is now correctly `.notConnected` when the `disconnectReader` completion block is called.

# 2.0.0 2021-06-23

This changelog includes a more detailed list of all the API and behavior changes since version 1.4.0 of the Stripe Terminal iOS SDK. In addition to this changelog, we've prepared a [migration guide](https://stripe.com/docs/terminal/sdk-migration-guide) that will help you upgrade your integration and explain the differences between the two SDKs.

## iOS Compatibility
The 2.0.0 Stripe Terminal iOS SDK requires iOS 10 and above.

## Connecting to a Reader
`connectReader` is now split into two separate methods: [`connectBluetoothReader`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)connectBluetoothReader:delegate:connectionConfig:completion:) and [`connectInternetReader`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)connectInternetReader:connectionConfig:completion:).

### `connectBluetoothReader`
[`connectBluetoothReader`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)connectBluetoothReader:delegate:connectionConfig:completion:) should be used to connect to any Bluetooth reader like the BBPOS WisePad 3 and BBPOS Chipper 2X BT.

* [`connectBluetoothReader`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)connectBluetoothReader:delegate:connectionConfig:completion:) requires providing a new [`BluetoothReaderDelegate`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html) which is used to report all reader events.
* The `terminal:didReportReaderEvent:info:` and `terminalDidReportLowBatteryWarning:` events have been moved from the `TerminalDelegate` into the [`BluetoothReaderDelegate`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html) .
* The `ReaderDisplayDelegate` has been removed and the [`didRequestReaderInput:`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)reader:didRequestReaderInput:) and [`didRequestReaderDisplayMessage:`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)reader:didRequestReaderDisplayMessage:) have moved to the [`BluetoothReaderDelegate`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html) .
* The `ReaderSoftwareUpdateDelegate` has been removed and the [`BluetoothReaderDelegate`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html) is used for communicating to your app about updates for the reader.

See [Updating reader software: Required updates](https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt#required-updates) for more details.

### `connectInternetReader`

[`connectInternetReader`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)connectInternetReader:connectionConfig:completion:) should be used to connect to Internet connected countertop readers like the Verifone P400 and the BBPOS WisePOS E. There are no changes required between `connectReader` and [`connectInternetReader`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)connectInternetReader:connectionConfig:completion:) for your countertop reader integration.

## Bluetooth Reader Updates
The `checkForUpdate` method has been removed. The Stripe Terminal SDK now checks for required and optional updates during reader connection.

Required update installation is reported to the new [`BluetoothReaderDelegate`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html) with the [`didStartInstallingUpdate`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)reader:didStartInstallingUpdate:cancelable:) method. Progress will be reported to that same delegate with [`didReportReaderSoftwareUpdateProgress`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)reader:didReportReaderSoftwareUpdateProgress:). When the installation of the required update finishes the delegate will receive the [`didFinishInstallingUpdate`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)reader:didFinishInstallingUpdate:error:).

For more information about implementing reader updates, see [Updating reader software](https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt#updating-reader-software) and [Testing Bluetooth reader updates](https://stripe.com/docs/terminal/testing#simulated-reader-updates).

## Collecting Payments
`collectPaymentMethod` and `readReusableCard` no longer require a `ReaderDisplayDelegate`. Instead, the [`BluetoothReaderDelegate`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html) , provided during [`connectBluetoothReader`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)connectBluetoothReader:delegate:connectionConfig:completion:), is used to communicate the [`didRequestReaderInput:`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)reader:didRequestReaderInput:) and [`didRequestReaderDisplayMessage:`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)reader:didRequestReaderDisplayMessage:) methods. These methods are only needed when using a Bluetooth connected reader and do not apply when using [`connectInternetReader`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)connectInternetReader:connectionConfig:completion:).

## Bluetooth Reader Locations
Like Internet readers, Bluetooth readers must now be registered to [Locations](https://stripe.com/docs/api/terminal/locations/object). Registering your Bluetooth readers to a location ensures that the readers install the proper regional configurations and are properly grouped on your account.

To register the reader to a location, create and use a `BluetoothConnectionConfiguration` object with the `locationId` set accordingly, and pass that object in when calling `Terminal.shared.connectBluetoothReader()`.

When discovering readers that have already been registered to a location, those reader objects will have a valid `locationId` property during discovery. If it makes sense for your application, you can pass that `locationId` from the discovered `Reader` object into the `BluetoothConnectionConfiguration` initializer to keep that reader registered to the same location. This is the pattern we recommend when discovering and connecting to simulated Bluetooth readers, which are now automatically registered to a mock location.

When connecting to a reader, you may want to display a list of Locations in your app. To enable this, the SDK provides the `Terminal.shared.listLocations(:completion:)` method that takes the same parameters as the [List all Locations](https://stripe.com/docs/api/terminal/locations/list) API endpoint. You may want to adjust your connection flow to allow users to pick a location before they select a reader, should they want to switch that reader's location manually.

## Other Changes
* [`SCPReaderSoftwareUpdate`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPReaderSoftwareUpdate.html) now has a [`components`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPReaderSoftwareUpdate.html#/c:objc(cs)SCPReaderSoftwareUpdate(py)components) property that can be used to determine the changes that will be applied with this update. [`deviceSoftwareVersion`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPReaderSoftwareUpdate.html#/c:objc(cs)SCPReaderSoftwareUpdate(py)deviceSoftwareVersion) can still be used to identify the specific firmware, config, and keys that will be installed with the update.
* Adds support for setting a [`SCPSimulatedCard`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPSimulatedCard.html) on the [`SCPSimulatorConfiguration`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPSimulatorConfiguration.html) object, allowing simulation of different card brands and decline types. See Simulated Test Cards for more details.
* Added optional delegate method, [`reader:didReportBatteryLevel:status:isCharging`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)reader:didReportBatteryLevel:status:isCharging:), to announce battery updates from Bluetooth readers.
* Adds error codes:
    * Added error [`SCPErrorBluetoothAccessDenied`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorBluetoothAccessDenied) returned when Bluetooth is enabled on the device but access for your application has been denied.
    * [`SCPErrorBluetoothPeerRemovedPairingInformation`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorBluetoothPeerRemovedPairingInformation) and [`SCPErrorBluetoothAlreadyPairedWithAnotherDevice`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorBluetoothAlreadyPairedWithAnotherDevice) to increase clarity when discovery or connection fails unexpectedly.
    * [`SCPErrorFeatureNotAvailable`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorFeatureNotAvailable), which will get returned when the initiated operation is not available for your account.
* Added [`SCPDeviceTypeStripeM2`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPDeviceType.html#/c:@E@SCPDeviceType@SCPDeviceTypeStripeM2) to [`SCPDeviceType`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPDeviceType.html). This reader is in beta testing and not yet generally available.
* Renames `SCPErrorPaymentDeclinedByStripeAPI` to [`SCPErrorDeclinedByStripeAPI`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorDeclinedByStripeAPI), referencing the fact that this error will be returned if Stripe rejects the SetupIntent or Refund as well as the payment.
* Bug fix: If your reader battery was low (around 15 percent or less), we did not invoke [`readerDidReportLowBatteryWarning`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)readerDidReportLowBatteryWarning:) until an action (such as a transaction) was taken. Now [`readerDidReportLowBatteryWarning`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)readerDidReportLowBatteryWarning:) is also announced upon connection to the reader.
* Bug fix: [`requestError`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPProcessPaymentError.html#/c:objc(cs)SCPProcessPaymentError(py)requestError) on the [`SCPProcessingPaymentError`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPProcessPaymentError.html) is now being properly populated in the case server has responded with an error and causes [`processPayment`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)processPayment:completion:) to fail.
* Bug fix: The very first [`discoverReaders`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)discoverReaders:delegate:completion:) call using Bluetooth with iOS 13.4 or later no longer results with a "Generic Bluetooth Error" and should now successfully start discovery.

## New features

* Added support for [Swift Package Manager](https://swift.org/package-manager/).
* Added support for running with iOS Simulator on Macs with M1 processors.
* The SDK's card-present refund functionality now works with the BBPOS WisePad 3 reader.
* Invite only: Stripe Terminal now supports creating [SetupIntents](https://stripe.com/docs/terminal/payments/saving-cards#outside-the-united-states-------) to save card information outside the United States. When saving card information in the United States, please continue to use [readReusableCard](https://stripe.com/docs/terminal/payments/saving-cards#read-reusable-card).

# 1.4.0 2020-09-03

- Added [`accountType`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPReceiptDetails.html#/c:objc(cs)SCPReceiptDetails(py)accountType) to `SCPReceiptDetails`.
- Added [`SCPDeviceTypeWisePosE`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPDeviceType.html#/c:@E@SCPDeviceType@SCPDeviceTypeWisePosE) to `SCPDeviceType`.
- Deprecated the `SCPDiscoveryConfiguration` initializers that require that you specify the device type to discover and replaced them with initializers that only require that you specify the discovery method. More specifically, if you use any of these `SCPDiscoveryConfiguration` initializers, you should replace them with the corresponding versions:
    - `initWithDeviceType:simulated:` → `initWithDiscoveryMethod:simulated:`
    - `initWithDeviceType:discoveryMethod:simulated:` → `initWithDiscoveryMethod:simulated:`
    - `initWithDeviceType:discoveryMethod:locationId:simulated:` → `initWithDiscoveryMethod:locationId:simulated:`
- Added a new interface in the example app to grant easy access to receipts

# 1.3.0 2020-07-28

This update adds Verifone P400 support for the following methods in `StripeTerminal`:

- [`setReaderDisplay`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)setReaderDisplay:cart:completion:) and [`clearReaderDisplay`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)clearReaderDisplay:completion:) allow you to set the Verifone P400’s [cart details](https://stripe.com/docs/terminal/checkout/cart-display) interface
- [`readReusableCard`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)readReusableCard:delegate:completion:) (only available for US merchants)

This update also introduces a cosmetic change to `SCPReader.deviceSoftwareVersion`. The Key Identifier number was previously displayed as the five-character string `30000` . This and future updates will display the identifier as a six-character string: `300001`. The key itself has not changed.

Not every Stripe Terminal reader supports all the functionality in the SDK. If you call a function that is not supported by the currently connected reader you will receive a `SCPErrorFeatureNotAvailableWithConnectedReader` error.

# 1.2.1 2020-06-18

- Sample app improvements:
    - Hide certain actions, like card-present refunds and reader updates, when the currently connected reader does not support them
    - Add interface to register a Verifone P400
- Improve the resiliency of Verifone P400 connections
- Throw an error if `collectRefundPaymentMethod` is called with an invalid charge ID in the RefundParameters object

# 1.2.0 2020-05-28

This update introduces support for Stripe Terminal in Canada using the [Verifone P400](https://stripe.com/docs/terminal/readers/verifone-p400) reader. To get started with Stripe Terminal in Canada, read our [Canada documentation](https://stripe.com/docs/terminal/canada).

Stripe Terminal supports Interac Debit payments and refunds. Interac in-person payments must be refunded while the cardholder is present. The Stripe Terminal iOS SDK includes a new card-present refunds API to support in-person refunds:

- `collectRefundPaymentMethod`
- `processRefund`

To support the card-present refunds API, we also introduce:

- the `SCPRefundParameters` object, which you pass into `collectRefundPaymentMethod`
- the `SCPProcessRefundError` class

### Other changes

- Example app is now compiled with Swift 5.2 by default
- Fixes issue where example app was preventing operation cancellation where it should be possible, and where example app was allowing cancellation where it shouldn't be possible.
- Fixes example app UI bugs
- Fixes bug where the SDK doesn't cancel outstanding cancelables when a reader disconnects
- Updates internal dependencies

# 1.1.1 2020-04-07

This update introduces support for the new `cardholderName` field in `SCPCardPresentDetails.h`, which is currently in beta.

# 1.1.0 2020-03-24

This update introduces support for connecting to and making payments with the [Verifone P400 countertop reader](https://stripe.com/docs/terminal/readers/verifone-p400).

iOS connectivity to the Verifone P400 reader is currently in public beta. Not all capabilities of the iOS SDK are available when connected to the Verifone P400, and some features available in the JavaScript SDK are not yet available in the iOS SDK. Future versions of the Stripe Terminal iOS SDK will add these additional Verifone P400 capabilities. Make sure to watch our [Github Releases page](https://github.com/stripe/stripe-terminal-ios/releases) ([RSS link](https://github.com/stripe/stripe-terminal-ios/releases.atom)) to get notified about these new updates.

The following iOS methods are not available when connected to a Verifone P400:


- [`createPaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)createPaymentIntent:completion:)
- [`cancelPaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)cancelPaymentIntent:completion:)
- [`readReusableCard`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)readReusableCard:delegate:completion:)

The following JavaScript SDK methods, which offer additional Verifone P400 functionality, are not available in the iOS SDK:


- [`setReaderDisplay`](https://stripe.com/docs/terminal/js-api-reference#set-reader-display)
- [`clearReaderDisplay`](https://stripe.com/docs/terminal/js-api-reference#clear-reader-display)

### Migrating your iOS integration to support the Verifone P400

- The `verifoneP400` is a new `SCPDeviceType` enum value. To discover Verifone P400 devices you’ve [registered to your Stripe account](https://stripe.com/docs/terminal/readers/connecting/verifone-p400#register-reader), you’ll need to specify both the `verifoneP400`  device type and the `internet` discovery method in your `DiscoveryConfiguration`.
- We recommend using locations when working with the Verifone P400. [Locations](https://stripe.com/docs/api/terminal/locations) filter the readers registered to your account. When registering a reader, you can associate the reader with a specific location. `DiscoveryConfiguration` has a new `locationId` parameter, which can be used to filter readers by location ID.
- The SDK’s `Reader` object now contains additional properties that match those on the [Reader API object](https://stripe.com/docs/api/terminal/readers/object). Many of these new properties only apply to the Verifone P400 reader:
    - `ipAddress`: The IP address of the reader, used for establishing a connection on the local network.
    - `locationId`: The [Location](https://stripe.com/docs/api/terminal/locations/object#terminal_location_object-id) ID associated with the reader.
    - `status`: The network connectivity status of the reader, i.e. offline or online. Check that the reader’s status is `online` before attempting to connect.
    - `label`: A custom label that can be optionally be associated with the reader.
    - `stripeID`: A [unique identifier](https://stripe.com/docs/api/terminal/readers/object#terminal_reader_object-id) for the reader.
- `discoverReaders` returns all registered readers, including those that are `offline`. We recommend that you display `offline` readers in your app’s UX for discovering readers so your users know which readers are already registered.
- We have added a new `ConnectionConfiguration` class (similar to `DiscoveryConfiguration`), which supports the `failIfInUse` option when connecting to the Verifone P400.
- The `TerminalDelegate.didReportUnexpectedReaderDisconnect` method will be called when the SDK notices it has been disconnected from the Verifone P400 (for example, if the reader loses its connection or power for over a minute). You can test this in your app by turning off the reader. Refer to [handling disconnects](https://stripe.com/docs/terminal/readers/connecting/verifone-p400#handling-disconnects) for more information.
- Since the Verifone P400 has a built-in display, your application doesn’t need to display events from the payment method collection process to users. You can pass `delegate: nil` to `collectPaymentMethod` because the `ReaderDisplayDelegate` methods will not be called.
- We introduced three new errors specific to connections with the Verifone P400:
    - `SCPErrorUnknownReaderIpAddress`: Returned when connecting to a reader that does not have an IP address on the `Reader` object.
    - `SCPErrorInternetConnectTimeOut`: `connectReader` completes with this error when connecting to an internet-enabled reader times out (for example, when connecting to a reader that is `offline`).
    - `SCPErrorConnectFailedReaderIsInUse`: Returned when the chosen reader is currently collecting a payment and `failIfInUse` is set to `true`. See the [Connecting to the Verifone P400](https://stripe.com/docs/terminal/ios-verifone-p400#connecting-verifone) section for more details.

### Other Changes

- Updated internal dependencies

# 1.0.3 2019-11-21

* Fixed an unexpected discovery failure when using the `bluetoothScan` discovery method
* Updated the example app for better iOS 13 support

# 1.0.2 2019-09-26

* Updated CoreLocation usage to make `processPayment` and `readReusableCard` more likely to succeed.
* Removed the need to include `NSMicrophoneUsageDescription` in your app's `Info.plist` file.

# 1.0.1 2019-09-09

* Removed entries in `SCPDeprecations.h` from pre v1.0 beta releases. If you still need to update your app from a beta release, we recommend updating using v1.0.0 *first*, and then updating to the latest.
* Fixed `paymentMethodDetails.cardPresent.brand` to return the correct values for `.amex` and `.dinersClub`. In v1.0.0, these brands were incorrectly being returned as `.unknown`.

# 1.0.0 2019-06-07

* First generally available release.
* Changelog details for previous releases (our betas) can be found in the release notes for each release: [https://github.com/stripe/stripe-terminal-ios/releases]
