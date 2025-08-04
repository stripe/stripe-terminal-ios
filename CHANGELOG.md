# Stripe Terminal iOS SDK changelog

This document details changes made to the SDK by version. The current status
of each release can be found in the [Support Lifecycle](SUPPORT.md).

If you are using CocoaPods, update your Podfile:
```
pod 'StripeTerminal', '~> 4.0'
```
# 4.6.0 2025-08-04
* Built with Xcode 16.0 Swift version 6.0.

### New
* Improved error handling when device is tampered. Connecting to a tampered reader will now fail with the `SCPErrorReaderTampered` error code.
* Preview: Added `ConfirmConfiguration.surcharge` and `SurchargeConfiguration` to configure surcharging on `confirmPaymentIntent`.
  * If you are interested in joining the preview, please contact [Stripe support](https://support.stripe.com/).
* Preview: Added a `print` method to enable printing images on the Verifone V660p reader.
  * If you are interested in joining the preview, please contact [Stripe support](https://support.stripe.com/).

### Updates
* Preview: The `ConfirmConfiguration.amountSurcharge` field has been renamed to `ConfirmConfiguration.surcharge.amount`.
  * If you are interested in joining this preview, please contact [Stripe support](https://support.stripe.com/).

# 4.5.0 2025-06-10
* Built with Xcode 16.0 Swift version 6.0.

### New
* New: Added `cardholderVerificationMethod` to [`SCPReceiptDetails`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPReceiptDetails.html).
  * See [`cardholder_verification_method`](https://docs.stripe.com/api/charges/object#charge_object-payment_method_details-card_present-receipt-cardholder_verification_method) for the list of supported verification methods.

### Updates
* iOS Location permission is no longer enforced when discovering readers, and will instead only be enforced when confirming payment intents.

### Fixes
* Fixed issue with issuing Interac refunds when `onBehalfOf` parameter is provided.
* Fixed issue where [`SCPCardPresentParameters`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPCardPresentParameters.html) fields were dropped.
* Fixed issue where calling [`discoverReaders`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)discoverReaders:delegate:completion:) while a mobile reader is connected would cause the SDK to enter an unexpected state preventing subsequent [`collectPaymentMethod`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)collectPaymentMethod:completion:) requests from responding.

# 4.4.0 2025-05-14
* Built with Xcode 16.0 Swift version 6.0.
### New
* Added simulated Internet reader support for collecting inputs. See the updated [`SCPSimulatorConfiguration`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPSimulatorConfiguration.html) for usage.
* Added `TapToPayInternalNetworkError` error code for network errors surfaced in Tap to Pay on iPhone and changed related errors from `InternalNetworkError` to `TapToPayInternalNetworkError`.
* Added new mobile reader disconnect reasons: `bluetoothSignalLost`, `usbDisconnected`, and `idlePowerDown` to [`SCPDisconnectReason`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPDisconnectReason.html).

### Fixes
* Fixed an issue where calling `collectPaymentMethod` when no reader was connected to the SDK falsely returned `SCPErrorFeatureNotAvailableWithConnectedReader`. This error is now correctly reported as `SCPErrorNotConnectedToReader`.
* Fixed an issue where the auto-reconnect feature would attempt to reconnect after a reader disconnected due to critically low battery and then disconnect again. Auto-reconnect is no longer attempted in this scenario.
* Fixed an issue where connection attempt to a reader incorrectly returned [`SCPErrorNotConnectedToInternet`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorNotConnectedToInternet) if fetching the connection token failed.  The correct error [`SCPErrorConnectionTokenProviderCompletedWithError`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorConnectionTokenProviderCompletedWithError) is now reported instead.
* Fixed an issue where the WisePad 3 reader would remain on the processing screen for 30 seconds when a collectPaymentMethod request with [`updatePaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPCollectConfiguration.html#/c:objc(cs)SCPCollectConfiguration(py)updatePaymentIntent) applied fails. The reader now exits the processing screen immediately.

# 4.3.0 2025-03-26
* Built with Xcode 16.0 Swift version 6.0.
* New: Added field `requestPartialAuthorization` to [`SCPCardPresentParameters`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPCardPresentParameters.html).
  * If you are interested in joining this preview, please email [stripe-terminal-betas@stripe.com](mailto:stripe-terminal-betas@stripe.com).
* New: Added field [`cardDetails`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPCardDetails.html) to [`SCPPaymentMethodDetails`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPPaymentMethodDetails.html).
  * _Note for internet reader integrations, this feature requires [reader software version](https://stripe.com/docs/terminal/readers/bbpos-wisepos-e#reader-software-version) `2.31` or later to be installed on your internet reader._
* Update: If the [`fetchConnectionToken`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPConnectionTokenProvider.html#/c:objc(pl)SCPConnectionTokenProvider(im)fetchConnectionToken:) completion block is called with an empty string for the token the SDK will fail the command with `SCPErrorConnectionTokenProviderCompletedWithNothing`.
* Fix: Resolved an issue where the SDK could be left in an unexpected state if `discoverReaders` was called while an existing `discoverReaders` was already in progress.
* Preview: [CollectInputs](https://stripe.com/docs/terminal/features/collect-inputs) now requires a unique `id` for each `SelectionButton`.
  * If you are interested in joining this preview, please email [stripe-terminal-betas@stripe.com](mailto:stripe-terminal-betas@stripe.com).
* Fix: Auto reconnect now reports [`SCPErrorBluetoothConnectTimedOut`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorBluetoothConnectTimedOut) if it times out reconnecting to a reader instead of [`SCPErrorCanceled`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorCanceled).
* Fix: Auto reconnect will continue trying to reconnect while the app is in the background. When the app becomes active the reconnect timer will give another 60 seconds for reconnect to succeed before timing out.
* Fix: Resolved an issue where the `allowRedisplay` parameter was not correctly applied when using `updatePaymentIntent` with [`collectPaymentMethod`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)collectPaymentMethod:collectConfig:completion:)

# 4.2.0 2025-02-14
* Built with Xcode 16.0 Swift version 6.0.
* New: Added `collectionReason` to [`SCPSetupIntentConfiguration`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPSetupIntentConfiguration.html).
  * This field can only be changed for Tap To Pay readers. The default value is saveCard.
* Added a new `Terminal.stringFromError` method to convert an `SCPError` to a non-localized string of the enum values name.
* Update: updatePaymentIntent is now supported when offline mode is enabled. 
* Update: Validation of location services has been added to Tap to Pay and mobile readers during [`collectPaymentMethod`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)collectPaymentMethod:completion:), [`collectSetupIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)collectSetupIntentPaymentMethod:allowRedisplay:completion:), and [`collectRefund`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)collectRefundPaymentMethod:completion:). This validation was already being enforced by [`confirmPaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)confirmPaymentIntent:completion:), [`confirmSetupIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)confirmSetupIntent:completion:), and [`confirmRefund`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)confirmRefund:), and is now extended to return the error earlier in the payment process.
* Update: Added support for operating offline with simulated Bluetooth and Internet readers.
* Fix: Resolved a rare deadlock crash during the Bluetooth scan discovery process.
* Fix: Prevented a minor memory leak each time the SDK connects to a reader.

# 4.1.0 2024-11-18
* Built with Xcode 16.0 Swift version 6.0.
* Update: Added field `dynamicCurrencyConversion` to [`SCPCardPresentDetails`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPCardPresentDetails.html).
  * If you are interested in joining this preview, please email [stripe-terminal-betas@stripe.com](mailto:stripe-terminal-betas@stripe.com).
* New: Affirm support for smart readers is now available in private preview.
  * If you are interested in joining this preview, please email [stripe-terminal-betas@stripe.com](mailto:stripe-terminal-betas@stripe.com).
* New: Added an `returnUrl` parameter to [`SCPConfirmConfiguration`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPConfirmConfiguration.html) to specify desired return_url to redirect to upon completion of a Redirect Payment Method.

# 4.0.0 2024-10-31
4.0.0 includes breaking changes in both symbols and behavior. See the [migration guide](https://stripe.com/docs/terminal/references/sdk-migration-guide) for more details.

* Built with Xcode 16.0, Swift version 6.0.
* Update: Minimum deployment target updated from iOS 13.0 to iOS 14.0.

### New Features
* [Mail order / telephone order (MOTO)](https://docs.stripe.com/terminal/features/mail-telephone-orders/overview) payment support for smart readers.
  - Contact Stripe support to enable this feature on your account.

* Global [card saving after payment](https://docs.stripe.com/terminal/features/saving-cards/save-after-payment) support by updating customer consent capture. The following breaking changes are required:
  - A valid `allowRedisplay` value is now required to be set in `collectConfiguration` when using `setupFutureUsage` for `SCPTerminal`'s `collectPaymentMethod`.
  - Removed the `customerConsentCollected` parameter from `SCPTerminal`'s `collectSetupIntentPaymentMethod` and replaced it with `allowRedisplay`.

## ⚠️ Breaking changes required

### Reader discovery
* New: Added a new enum value `discovering` to [`SCPConnectionStatus`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPConnectionStatus.html) to represent when discovery is running.
* Update: Subsequent calls to `SCPTerminal`'s `discoverReaders:delegate:completion:` cancel all previously queued discovery operations. Only one discovery operation can run at any given time; all other discovery attempts will fail with `SCPErrorCanceledDueToIntegrationError`.
* Update: Internet and Tap to Pay discovery will now call the [`discoverReaders`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)discoverReaders:delegate:completion:) completion block when the operation completes since these are not long running discovery operations.

### Reader connection
* Update: There is now a single [`connectReader`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)connectReader:delegate:connectionConfig:completion:) call used for all connection methods. This replaces the previous methods: `connectBluetoothReader`, `connectInternetReader`, and `connectLocalMobileReader`.
  - For mobile readers and Tap to Pay readers, the `ReaderDelegate` has been removed from the `connectReader` method as a parameter, and moved into the `connectionConfig`, replacing `autoReconnectionDelegate`.  - For smart readers, the `InternetConnectionConfiguration` now also expects an `InternetReaderDelegate` to be passed in, which will alert your integration of reader disconnects.

* Update: [Auto reconnect on unexpected disconnect](https://docs.stripe.com/terminal/payments/connect-reader?terminal-sdk-platform=ios&reader-type=tap-to-pay#2.-automatically-attempt-reconnection) is now enabled by default for mobile and Tap to Pay readers.
  * The `SCPReconnectionDelegate` has been removed and the methods have been moved to the common [`ReaderDelegate`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPReaderDelegate.html).
* Update: The method for handling reader disconnects has changed.
  * Removed `terminal:didReportUnexpectedReaderDisconnect:` from the `SCPTerminalDelegate`. Use [`reader:didDisconnect:`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPReaderDelegate.html#/c:objc(pl)SCPReaderDelegate(im)reader:didDisconnect:) to be informed of reader disconnects.
  * When auto-reconnect on unexpected disconnect is enabled, both [`-readerDidFailReconnect:`](https://stripe.dev/stripe-terminal-ios/docs/4.0.0/Protocols/SCPReaderDelegate.html#/c:objc(pl)SCPReaderDelegate(im)readerDidFailReconnect:) and [`reader:didDisconnect:`](https://stripe.dev/stripe-terminal-ios/docs/4.0.0/Protocols/SCPReaderDelegate.html#/c:objc(pl)SCPReaderDelegate(im)reader:didDisconnect:) methods will be called if the SDK fails to reconnect to the reader and it becomes disconnected.

### Payment acceptance
* New: Added a new enum value `SCPCardPresentCaptureMethodManual` to [`SCPCardPresentCaptureMethod`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPCardPresentCaptureMethod.html) for simplifying manual card capture without affecting automatic non-card payment capture.
    * If you are interested in joining this private preview, please email [stripe-terminal-betas@stripe.com](mailto:stripe-terminal-betas@stripe.com).
* Update: `SCPTerminal`'s `confirmPaymentIntent:completion`, `confirmSetupIntent:completion`, and `confirmRefund:completion` operations now return `SCPCancelable`'s that allow you to cancel the operation in certain scenarios.
* Update: Calls to `SCPTerminal`'s `cancelPaymentIntent:completion` or `cancelSetupIntent:completion` will now cancel ongoing operations related to the specified intent.
* Update: [`SCPOfflineDelegate`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPOfflineDelegate.html) now conforms to `NSObject`.
* Update: `SCPPaymentIntentParameters` and `SCPSetupIntentParameters` now keep payment method types as values of the `SCPPaymentMethodType` enum rather than strings.
* Update: [`SCPSetupIntent.stripeId`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPSetupIntent.html#/c:objc(cs)SCPSetupIntent(py)stripeId) is now `nullable` to be consistent with `SCPPaymentintent.stripeId`. The `SCPSetupIntent.stripeId` will continue to be present.

### Renaming
* Update: [`BluetoothReaderDelegate`](https://stripe.dev/stripe-terminal-ios/3.9.0/Protocols/SCPBluetoothReaderDelegate.html) has been renamed to [`MobileReaderDelegate`](https://stripe.dev/stripe-terminal-ios/Protocols/SCPMobileReaderDelegate.html).
* Update: In `SCPReaderSoftwareUpdate`, renamed `estimatedUpdateTime` to `durationEstimate`.
* Update: Renamed `SCPUpdateTimeEstimate` to `SCPUpdateDurationEstimate`.
* Update: Renamed "local mobile" and "apple built in" to "Tap To Pay" in all SDK types, function names, and error codes to align with Stripe branding for this functionality.

## Non-breaking changes
* Update: The [`SCPInternetDiscoveryConfiguration`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPInternetDiscoveryConfiguration.html) now supports an optional `timeout` value, specifying the timeout in seconds for the discover readers request. If the online discovery attempt fails, the operation will automatically fall back to offline discovery if [offline mode](https://docs.stripe.com/terminal/features/operate-offline/overview?reader-type=internet) is enabled.
* Update: Improved accuracy of smart reader errors that are reported as `SCPError`.  Errors that were previously reported as a `SCPErrorGenericReaderError` are now mapped to a more specific `SCPError` type.


# 3.9.1 2024-09-05
* Built with Xcode 15.2, Swift version 5.9.
* Fix [#325](https://github.com/stripe/stripe-terminal-ios/issues/325): Corrects the status of `Terminal.shared.paymentStatus` and `Terminal.shared.connectionStatus` after [automatically reconnecting](https://docs.stripe.com/terminal/payments/connect-reader?terminal-sdk-platform=ios&reader-type=bluetooth#handle-disconnects) to mobile readers during unexpected disconnects.

# 3.9.0 2024-09-03
* Built with Xcode 15.2, Swift version 5.9.
* Beta: WeChat Pay support for smart readers is now available in private beta.
  * If you are interested in joining this beta, please email [stripe-terminal-betas@stripe.com](mailto:stripe-terminal-betas@stripe.com).
* New: Adds support for [Interac refunds](https://docs.stripe.com/terminal/payments/regional?integration-country=CA#refund-an-interac-payment) on the Tap to Pay simulated reader.
* Update: For mobile readers with [`auto reconnection`](https://docs.stripe.com/terminal/payments/connect-reader?terminal-sdk-platform=ios&reader-type=bluetooth#handle-disconnects) enabled, the SDK now installs required updates upon reconnection after a [reboot](https://docs.stripe.com/terminal/payments/connect-reader?terminal-sdk-platform=ios&reader-type=bluetooth#reboot-the-connected-reader). Your application will continue to receive notifications about updates via the [`BluetoothReaderDelegate`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html) and should handle updating its UI to inform the user of the update accordingly.
* Update: Improved handling of [`SCPErrorReaderMissingEncryptionKeys`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorReaderMissingEncryptionKeys) error for mobile readers with auto-reconnection enabled. Previously, the SDK would disconnect from the reader without auto-reconnecting when this error occurred. Now, if auto-reconnection is enabled, the SDK will automatically reconnect and recover from this error.
* Fix [#595](https://github.com/stripe/stripe-terminal-react-native/issues/595): Addresses the issue where backgrounding the app while the Tap to Pay PIN collection screen is displayed causes the SDK to become unresponsive until the app is relaunched.
* Fix: Resolves a race condition that occurs when a card is inserted simultaneously as [`collectPaymentMethod`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)collectPaymentMethod:completion:) is being canceled. Previously, this resulted in a [`SCPErrorReaderBusy`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorReaderBusy) error. Now, the collection will complete by returning a [`SCPErrorCanceled`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorCanceled) error instead.

# 3.8.3 2024-08-12
* Fix the root cause of the deadlocks, further reducing the risk of SDK crashes.

# 3.8.2 2024-08-08
* Fix another path that could result in a logger deadlock, further reducing the risk of SDK crashes.

# 3.8.1 2024-08-06
* Fix a deadlock in the logger that can cause the SDK to crash

# 3.8.0 2024-07-31
* Built with Xcode 15.2, Swift version 5.9.
* Fix an issue running on iOS 18 where the SDK fails [`collectPaymentMethod`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)collectPaymentMethod:completion:) with [`SCPErrorUnexpectedSdkError`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorUnexpectedSdkError) when collecting amounts greater than 99999.
* Fix an issue where the SDK can report a reader as connected if it had disconnected while installing a required update.
* Fix a rare race condition where [`confirmPaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)confirmPaymentIntent:completion:) could incorrectly fail with [`SCPErrorReaderBusy`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorReaderBusy).
* Fix `supportsReadersOfType` returning `true` for `SCPDeviceTypeAppleBuiltIn` on iOS versions below 16.7 (minimum supported version).

# 3.7.0 2024-06-24
* Built with Xcode 15.2, Swift version 5.9.
* Beta: Surcharging is now available in private beta.
  * added a `surchargeNotice` parameter to [`SCPCollectConfiguration`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPCollectConfiguration.html) to display a surcharge notice on the payment collection screen.
  * added a `SCPSurcharge` field to the [`SCPCardPresentParameters`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPCardPresentParameters.html) object.
  * added a [`SCPConfirmConfiguration`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPConfirmConfiguration.html) class to allow per-transaction overrides for [`confirmPaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)confirmPaymentIntent:completion:).
  * added an `amountSurcharge` parameter to [`SCPConfirmConfiguration`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPConfirmConfiguration.html) to surcharge when confirming a payment.
  * If you are interested in joining this beta, please email stripe-terminal-betas@stripe.com.
* Beta: Added a `collectData` method to collect eligible magstripe data, such as gift cards.
  * If you are interested in joining this beta, please email stripe-terminal-betas@stripe.com.
* Update: Added [`SCPSimulateReaderUpdateLowBatterySucceedConnect`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPSimulateReaderUpdate.html#/c:@E@SCPSimulateReaderUpdate@SCPSimulateReaderUpdateLowBatterySucceedConnect) to simulate an error scenario where a required update fails on a mobile reader due to low battery, but the SDK still successfully connects to the reader.
  * see [Simulated reader updates](https://docs.stripe.com/terminal/references/testing?terminal-sdk-platform=ios#simulated-reader-updates) for details.
* Update: if a mobile reader receives the [`SCPErrorReaderMissingEncryptionKeys`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPError.html#/c:@E@SCPError@SCPErrorReaderMissingEncryptionKeys) error during payment collection, the SDK will disconnect from the reader. Note that auto reconnection will not work in this scenario. The error will automatically recover once the reader is reconnected.
* Fix: Fixed a crash that occurred when canceling [`collectPaymentMethod`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)collectPaymentMethod:completion:) after [`confirmPaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)confirmPaymentIntent:completion:) had already been called on the `PaymentIntent`.

# 3.6.0 2024-05-13
* Built with Xcode 15.2, Swift version 5.9.
* Update: Using [`SCPOfflineBehaviorRequireOnline`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPOfflineBehavior.html#/c:@E@SCPOfflineBehavior@SCPOfflineBehaviorRequireOnline) will attempt online network calls regardless of the current network status. This may cause requests while the network is offline to take longer as requests will always be attempted online first.
* Update: Tapping or inserting an unsupported card will now report `SCPReaderDisplayMessageTryAnotherCard` instead of `SCPReaderDisplayMessageTryAnotherReadMethod`.
* Update: [`paymentStatus`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(py)paymentStatus) now stays `ready` while API-only commands are in-progress. This includes `createPaymentIntent`, `createSetupIntent`, `cancelPaymentIntent`, and `cancelSetupIntent`.
* Update: [`paymentStatus`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(py)paymentStatus) now updates to `waitingForInput` while [`collectInputs`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)collectInputs:completion:) is running.
* Update: If a reader receives the `SCPErrorReaderMissingEncryptionKeys` error when collecting a payment the SDK now also reboots the reader in addition to the existing behavior of disconnecting from the reader. Reconnecting to the reader should re-install the keys and allow the reader to collect payments again.

# 3.5.0 2024-04-12
* Built with Xcode 15.2, Swift version 5.9.
* Beta: [`CollectInputs`](https://stripe.com/docs/terminal/features/collect-inputs?terminal-sdk-platform=ios) can now display optional `toggles` in each input type.
  * If you are interested in joining this beta, please email stripe-terminal-betas@stripe.com.
* New: Support for connecting to mPOS readers over USB-C on iPads with M-series chips.
  * This feature is in private beta. Please [contact us](mailto:stripe-terminal-betas@stripe.com) if you are interested in joining this beta.
* New: Added an xcprivacy file to the framework listing our data use and [required reason API](https://developer.apple.com/documentation/bundleresources/privacy_manifest_files/describing_use_of_required_reason_api?language=objc) usage.
* Update: Added [`SetupIntentParameters.paymentMethodTypes`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPSetupIntentParameters.html#/c:objc(cs)SCPSetupIntentParameters(py)paymentMethodTypes).
  - _Note for internet reader integrations, this feature requires [reader software version](https://stripe.com/docs/terminal/readers/bbpos-wisepos-e#reader-software-version) `2.22` or later to be installed on your internet reader._
* Update: [`supportsReadersOfType`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)supportsReadersOfType:discoveryMethod:simulated:error:) now returns NO with error `SCPErrorInvalidDiscoveryConfiguration` if the device type and discovery method are incompatible.
* Update: When a Bluetooth reader has an error installing a required update the SDK will allow connecting to the reader if the reader is running a recent version. The error installing the update will still be communicated in the [`reader:didFinishInstallingUpdate:error:`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)reader:didFinishInstallingUpdate:error:) callback. The update will be available to be retried using [`installAvailableUpdate`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)installAvailableUpdate). If the update isn't installed with `installAvailableUpdate` the installation will be retried the next time connecting to the reader.
* Fixes [#291](https://github.com/stripe/stripe-terminal-ios/issues/291): Fixes a bug where the cancelable returned by [`collectPaymentMethod`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)collectPaymentMethod:completion:) was not responsive in certain conditions when a card was left in the reader or inserted before calling `collectPaymentMethod`.
* Fixes a bug where `rebootReader` would return `SCPErrorUnexpectedSdkError` if called after the reader received a firmware update.

# 3.4.0 2024-03-04
* Built with Xcode 15.2, Swift version 5.9.
* New: For Tap to Pay on iPhone, added `autoReconnectOnUnexpectedDisconnect` and `autoReconnectionDelegate` to the [`SCPLocalMobileConnectionConfiguration`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPLocalMobileConnectionConfiguration.html). When `autoReconnectOnUnexpectedDisconnect` is enabled, the SDK will attempt to restore connection upon any unexpected disconnect to your local mobile reader. See [Stripe documentation](https://stripe.com/docs/terminal/payments/connect-reader?terminal-sdk-platform=ios&reader-type=tap-to-pay#handle-disconnects) for details.
* Update: Formatting on certain fields exposed in `SCPOfflineCardPresentDetails` is now consistent with `SCPCardPresentDetails`
  * `expYear` is a four-digit number
  * `receiptDetails.accountType` is no longer a number, and is one of `default`, `savings`, `checking`, or `credit`
* Update: The SDK now requires that a `NSBluetoothAlwaysUsageDescription` key be present in your app's Info.plist instead of a `NSBluetoothPeripheralUsageDescription` key.
* Update: Allow `SCPCollectConfiguration.updatePaymentIntent` to be true for offline enabled readers when `SCPCreateConfiguration` has `offlineBehavior` set to `SCPOfflineBehaviorRequireOnline`.
* Update: Added new `SCPErrorReaderMissingEncryptionKeys`. Returned in a rare condition where the reader is missing the required keys to encrypt payment method data. The reader will disconnect if this error is hit. Reconnecting to the reader should re-install the keys.
* Update: More descriptive error messages in `SCPErrorKeyMessage` for operations that fail due to network-related errors.
* Fixes a bug where `SCPPaymentIntent.stripeId` was not `nil` in the response to `confirmPaymentIntent` when operating offline with a smart reader.
* Fixes a rare bug where Bluetooth readers could get into a state where they would no longer accept payments and needed to be replaced.

# 3.3.1 2024-02-07
* Built with Xcode 15.2, Swift version 5.9.
* Fixes [#282](https://github.com/stripe/stripe-terminal-ios/issues/282): Fixes a crash when connecting to Stripe Reader M2 or BBPOS Chipper 2X devices that are running older configs.
* Fixes a race condition that could result in a crash when an internet reader unexpectedly disconnects.

# 3.3.0 2024-02-02
* Built with Xcode 15.2, Swift version 5.9.
* New: [`rebootReader`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)rebootReader:) method to reboot Bluetooth readers.
* New: An optional [`reader:didDisconnect:`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate(im)reader:didDisconnect:) method was added to [`SCPBluetoothReaderDelegate`](https://stripe.dev/stripe-terminal-ios/docs/Protocols/SCPBluetoothReaderDelegate.html#/c:objc(pl)SCPBluetoothReaderDelegate) which provides a new [`SCPDisconnectReason`](https://stripe.dev/stripe-terminal-ios/docs/Enums/SCPDisconnectReason.html) to communicate known reasons why a Bluetooth reader disconnected.
* New: Support refunding payments with the `SCPPaymentIntent.stripeId`.
  * _Note for internet reader integrations, this feature requires [reader software version](https://stripe.com/docs/terminal/readers/bbpos-wisepos-e#reader-software-version) `2.19` or later to be installed on your internet reader._
* New: Added support for retrieving and updating reader settings on WisePOS E and Stripe S700 by calling `retrieveReaderSettings` and `setReaderSettings` on `SCPTerminal`.
  * Beta: Accessibility settings are provided at this time, allowing text-to-speech via speakers to be turned on and off as needed.
  * Please [contact us](mailto:stripe-terminal-betas@stripe.com) if you are interested in joining this beta.
* Beta: Added a [`collectInputs`](https://stripe.com/docs/terminal/features/collect-inputs) method to display forms and collect information from customers.
  * If you are interested in joining this beta, please email stripe-terminal-betas@stripe.com.
* Fixes a bug where collected offline payments using a reader that wasn't connected to online first would fail to be forwarded.
* Fixes [#272](https://github.com/stripe/stripe-terminal-ios/issues/272): Removed old note about `discoverReaders` not returning an error when canceled. In 3.x SDKs canceling `discoverReaders` reports `SCPErrorCanceled`.
* Fixes [#251](https://github.com/stripe/stripe-terminal-ios/issues/251): Allow acceptance of Discover cards stored in Apple Pay.
* Fixes [#279](https://github.com/stripe/stripe-terminal-ios/issues/279): Canceling collectPaymentMethod no longer hangs if card was removed early and the reader went back to the tipping input screen.

# 3.2.1 2023-12-18
* Built with Xcode 14.3, Swift version 5.8.
* Fixes [#276](https://github.com/stripe/stripe-terminal-ios/issues/276): Fixes a regression introduced in 3.2.0 where reconnecting to a Bluetooth reader can timeout after disabling and re-enabling Bluetooth on the iOS device.

# 3.2.0 2023-11-17
* Built with Xcode 14.3, Swift version 5.8.
* Update: `retrievePaymentIntent` and `retrieveSetupIntent` no longer require a connected reader.
* Update: Adds `SCPCharge.authorizationCode` to the sdk's [`SCPCharge`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPCharge.html) model when it is available.
  * _Note for internet reader integrations, this feature requires [reader software version](https://stripe.com/docs/terminal/readers/bbpos-wisepos-e#reader-software-version) `2.18` or later to be installed on your internet reader._
* Update: Added `network` and `wallet` to `SCPCardPresentDetails`.
* Update: Added `paymentMethodId` to `SCPPaymentIntent`.
* Update: The amount of time a reader can be used offline before needing to be activated online has been reduced to 30 days.
* Update: `SCPReaderNetworkStatus` has a new case (`SCPReaderStatusUnknown`) that represents the network status of an internet reader that was discovered while the SDK is operating in offline mode.
* Fix: `SCPSetupIntent.status` is now `SCPSetupIntentStatusRequiresConfirmation` after the payment has been collected.
* Fixes a rare crash when connecting to a Bluetooth reader with a critically low battery.
* Fixes a rare crash when installing a Bluetooth reader update.
* Fixes a bug where cancelPaymentIntent, createSetupIntent, and cancelSetupIntent were not being queued and could error with an unexpected SDK error if called while another command was in progress.
* Fixes merchant choice routing not updating upon switching reader regions.
* Fixes [#262](https://github.com/stripe/stripe-terminal-ios/issues/262): Initial Bluetooth reader battery level is reported immediately after connecting to the reader.
* Fixes error messaging to not return an unexpected SDK error in some situations when connected to a smart reader.
* Fixes an issue where integrations could hit `SCPErrorSessionExpired` when the SDK comes back online while using offline mode.

# 3.1.0 2023-10-10
* Built with Xcode 14.3, Swift version 5.8.
* New: Public beta support for offline payments.
    * See [Collect payments while offline](https://stripe.com/docs/terminal/features/operate-offline/collect-payments) for details.
* Beta: Allow customer-initiated cancellation for PaymentIntent, SetupIntent, and Refund payment method collection with internet readers. See `setEnableCustomerCancellation:` on `SCPCollectConfigurationBuilder`, `SCPSetupIntentConfigurationBuilder`, and `SCPRefundConfigurationBuilder`.
    * _Note: This feature requires [reader software version](https://stripe.com/docs/terminal/readers/bbpos-wisepos-e#reader-software-version) `2.17` or later to be installed on your internet reader._
    * Please [contact us](mailto:stripe-terminal-betas@stripe.com) if you want to support customer-initiated cancellation.
* Update: When connecting to internet readers, the SDK no longer relies on DNS. This resolves an [error](https://support.stripe.com/questions/the-stripe-terminal-sdk-is-encountering-dns-errors-when-connecting-to-an-internet-reader) experienced by users of some DNS providers.
* Fixes an issue where tipping and offline configs may not be fetched when connecting to an mPOS reader. Tipping and offline mode users should upgrade their SDK.
* Fixes an issue where the SDK wouldn't announce an unexpected disconnect if an internet reader receives an invalid session error. This can happen after the reader reboots while the SDK is in the background.
* Fixes an issue where the SDK would error with `SCPErrorFeatureNotAvailableWithConnectedReader` instead of `SCPErrorNotConnectedToReader` when calling certain commands without being connected to a reader.
* Fixes a bug where the SDK could deadlock if attempting to connect to the same reader twice.
* Fixes a crash running `Terminal.shared.supportsReaders` on M1 Mac.
* Improved `confirmPaymentIntent` performance when location is not available.

# 3.0.0 2023-09-08
3.0.0 includes breaking changes in both symbols and behavior. See the [migration guide](https://stripe.com/docs/terminal/references/sdk-migration-guide) for more details.

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

# 2.23.3 2024-08-14
* Built with Xcode 15.2, Swift version 5.9.
* Minimum deployment target changed from iOS 11.0 to iOS 12.0 as required by Xcode 15.
* Fix an issue running on iOS 18 where the SDK fails [`collectPaymentMethod`](https://stripe.dev/stripe-terminal-ios/2.23.0/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)collectPaymentMethod:completion:) with [`SCPErrorUnexpectedSdkError`](https://stripe.dev/stripe-terminal-ios/2.23.0/Enums/SCPError.html#/c:@E@SCPError@SCPErrorUnexpectedSdkError) when collecting [amounts](https://stripe.dev/stripe-terminal-ios/2.23.0/Classes/SCPPaymentIntent.html#/c:objc(cs)SCPPaymentIntent(py)amount) greater than 99999.
* Fix an issue where the [`SCPCardPresentDetails`](https://stripe.dev/stripe-terminal-ios/2.23.0/Classes/SCPCardPresentDetails.html) object would be null for a [`SCPPaymentIntent`](https://stripe.dev/stripe-terminal-ios/2.23.0/Classes/SCPPaymentIntent.html).

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
