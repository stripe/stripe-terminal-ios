1.0.0-b5

If you are using CocoaPods, update your Podfile:
```
pod 'StripeTerminal', '1.0.0-b5'
```

## Reader software update: audio feedback
We've released an (optional) reader update that enables beeps when a card is inserted and when the transaction completes.
- After this update, the reader will emit a single beep when a card is inserted, and two beeps when the transaction is complete. Currently, the reader only emits these beeps for contactless transactions.
- The reader will also issue two beeps, recurring at a 5 second interval, if the inserted card is left in the reader after the transaction has completed.

Note: you will need to update your readers in order to enable this feature. You can update your readers by implementing the SDK's `updateReaderSoftware` [workflow](https://stripe.com/docs/terminal/ios/workflows#reader-updates), or by using the provided example app, which includes the ability to update readers. You can download the Example app directly on [TestFlight](https://testflight.apple.com/join/NYXuDNuT), or build it from source.

You'll need to perform a series of 2 updates in order to enable this functionality on your reader.

- The current `deviceSoftwareVersion` should look something like this:
  - `1.00.03.32-SZZZ_Generic_v35-30000`
- The first update will update the firmware on your reader to `1.00.03.34`.
  - This firmware adds the ability to beep during contact card presentation.
  - The version for this update will look something like this:
    - `1.00.03.34-SZZZ_Generic_v35-30000`
- The second update will update the configuration of your reader to `SZZZ_Generic_v37`
  - This configuration enables beeps on card insert, transaction complete, and card left in reader.
  - The version for this update will look something like this:
    - `1.00.03.34-SZZZ_Generic_v37-30000`

## Other updates
- `retrievePaymentIntent` has been renamed in Swift to make it clearer that you must pass a `clientSecret` as the first argument.
- When `discoverReaders` is canceled, the completion block will now be called with `nil`. Previously, canceling `discoverReaders` would result in the completion block producing an error with code `SCPErrorCanceled`. This was surprising to several users, so we've changed the behavior of this method. Note that canceling `collectPaymentMethod` still produces an error with code `SCPErrorCanceled`.
- We've fixed [an issue](https://github.com/stripe/stripe-terminal-ios/issues/16) where connecting to a reader immediately after discovery would fail when using the `BluetoothDiscovery` method.
- The `didRequestReaderInputPrompt` delegate method has been modified in Swift to be consistent with other delegate methods.
```
-    func terminal(terminal: Terminal, didRequestReaderInputPrompt inputPrompt: ReaderInputPrompt) {
+    func terminal(_ terminal: Terminal, didRequestReaderInputPrompt inputPrompt: ReaderInputPrompt) {
```

