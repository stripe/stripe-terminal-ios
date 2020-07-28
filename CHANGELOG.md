# Stripe Terminal iOS SDK changelog

If you are using CocoaPods, update your Podfile:
```
pod 'StripeTerminal', '1.3.0'
```
# 1.3.0 2020-07-28

This update adds Verifone P400 support for the following methods in `StripeTerminal`:

- [`setReaderDisplay`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)setReaderDisplay:cart:completion:) and [`clearReaderDisplay`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)clearReaderDisplay:completion:) allow you to set the Verifone P400’s [cart details](https://stripe.com/docs/terminal/checkout/cart-display) interface
- [`readReusableCard`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)readReusableCard:delegate:completion:) (only available for US merchants)

This update also introduces a cosmetic change to `SCPReader.deviceSoftwareVersion`. The Key Identifier number was previously displayed as the five-character string `30000` . This and future updates will display the identifier as a six-character string: `300001`. The key itself has not changed.

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
