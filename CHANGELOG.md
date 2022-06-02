# Stripe Terminal iOS SDK changelog

If you are using CocoaPods, update your Podfile:
```
pod 'StripeTerminal', '~> 2.0'
```

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
