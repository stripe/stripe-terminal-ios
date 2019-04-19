1.0.0-rc1

If you are using CocoaPods, update your Podfile:
```
pod 'StripeTerminal', '1.0.0-rc1'
```

## DiscoveryConfiguration

The initializers for DiscoveryConfiguration have changed. Rather than specifying a `readerSimulator` device type, you can now specify that the configuration is `simulated`. This allows for the SDK to simulate all device type and discovery method combinations. The `readerSimulator` device type has been removed.

Previously, the `init(deviceType:method:)` was nullable, and would return nil if an invalid device type and discovery method combination was provided. That method has been replaced with `init(deviceType:discoveryMethod:simulator:)`, which is no longer nullable. If an invalid device type and discovery method combination is provided, the subsequent call to `discoverReaders` will fail with `SCPErrorInvalidDiscoveryConfiguration`.

## PaymentMethods

This release uses [PaymentMethods](https://stripe.com/docs/api/payment_methods) instead of [Sources](https://stripe.com/docs/api/sources). They're similar concepts, but it means we've shuffled things around. In b6 (and earlier), a `Source` would be added to your `PaymentIntent` during `Terminal.confirmPaymentIntent()`, or a standalone `card_present` `Source` could be created via `Terminal.readSource()`.

### Terminal.processPayment()

The `Terminal.confirmPaymentIntent()` method has been replaced by `Terminal.processPayment()`. In this flow, the `CardPresentSource` class has been replaced by `CardPresentDetails`:

- The returned `PaymentIntent` no longer has a `CardPresentSource` property. Instead, find the `CardPresentDetails` object on the `Charge`(s) in `PaymentIntent.charges`.
- Each `Charge` has a `PaymentMethodDetails` object, with transaction-specific details about the payment method used. For the StripeTerminal SDK `collectPaymentMethod` & `processPayment` flow, these `PaymentMethodDetails` will be of `type == .cardPresent`, and their `cardPresent` property has the `CardPresentDetails`.
- The `CardPresentSource.stripeId`, `CardPresentSource.metadata`, and `CardPresentSource.name` properties are not available on `CardPresentDetails`.
- `CardPresentSource.receiptData` is now `CardPresentDetails.receipt`, and the class name has changed from `ReceiptData` to `ReceiptDetails`.

There are a couple other misc related changes:

- The `PaymentIntentStatusRequiresSource` status has been renamed `PaymentIntentStatusRequiresPaymentMethod`.
- The `ReceiptDetails.mid` and `ReceiptDetails.tid` properties have been removed.

### Terminal.readReusableCard()

The `Terminal.readSource()` method has been replaced by `Terminal.readReusableCard()`. A successful `readReusableCard` call returns a `PaymentMethod` instead of a `CardPresentSource`.

The returned payment method is of `type == .card`, instead of `cardPresent`. It's no longer necessary to convert the payment method first, these `PaymentMethod`s are immediately usable for online charges, and can be reused.

Properties from the `CardPresentSource` are now found either on the top-level `PaymentMethod` (ex: `stripeId`), or inside the `PaymentMethod`'s `card: CardDetails` property (ex: `brand` or `fingerprint`).


## Unexpected reader disconnects

The `terminal:didDisconnectUnexpectedlyFromReader:` method has been renamed `terminal:didReportUnexpectedReaderDisconnect:`, and is now required. Your app should handle this method, and notify your user that the reader has disconnected. You may also want to start the `discoverReaders` process when your app handles this method. Your app can automatically attempt to discover and connect to the previously connected reader, or display UI for your user to re-connect to a reader.

## Reader Update API

The `terminal:checkForReaderSoftwareUpdate` has been renamed and split into two calls: `terminal:checkForUpdate` and `terminal:installUpdate`. Instead of calling `terminal:checkForReaderSoftwareUpdate` and receiving the update via `readerSoftwareUpdateDelegate:readerSoftwareUpdateAvailable`, `terminal:checkForUpdate` accepts a completion which is passed the update if one is available. Once you have an update you will have to call `terminal:installUpdate`. We are deprecating `readerSoftwareUpdateDelegate:didCompleteReaderSoftwareUpdate`.  Instead you will pass a completion to `terminal:installUpdate` which will be passed nil upon successful completion and an error otherwise.

## Other changes

- The SDK will now request location permissions from the user when your app connects to a reader for the first time. (Feedback from https://github.com/stripe/stripe-terminal-ios/issues/26)
- We've fixed issues where `connectReader` took a long time under certain conditions.
- Bugfix: In some situations, the `completion:` blocks for `collectPaymentMethod` and `readSource` could execute more than once: reporting a failure followed by a success [#28](https://github.com/stripe/stripe-terminal-ios/issues/28).
- Added a `hasTokenProvider` getter, in case you want to check whether you've set a token provider before accessing the `shared` Terminal singleton. (Feedback from https://github.com/stripe/stripe-terminal-ios/issues/26)
