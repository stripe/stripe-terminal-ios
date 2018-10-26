# CHANGELOG

Note that if you are using CocoaPods, the format of this version has changed. In your Podfile:
```
pod 'StripeTerminal', '1.0.0-b3'
```

### Tap to discover
- We've added a new discovery method, "Bluetooth Proximity", which you can use to discover a reader by holding it next to the iOS device. We think this will greatly improve the reader discovery experience – please try it out! If you have any feedback on the feature, please [file an issue](https://github.com/stripe-ios/stripe-terminal-ios/issues/new).
- The initializer for `DiscoveryConfiguration` now requires specifying a `deviceType`.

### Other changes
- The `batteryLevel` property on `Reader` is now an optional `NSNumber` (boxing a float from [0.0, 1.0], as before). (h/t @jasonzurita)
- `ReadSourceParameters` now has an optional `metadata` property, which you can use to attach key-value pairs to the source. (h/t @jasonzurita)
- We've fixed a bug where `collectPaymentMethod` could not be canceled if a card from a previous payment was left in the reader. (h/t @sgruby-reformation)
- `ConfirmError` now has an optional `declineCode` property. If the payment was declined, this property contains the `decline_code` from the Stripe API. (h/t @sgruby-reformation)
- `terminal.cancel` has been renamed to `terminal.cancelPaymentIntent` in Swift, for clarity
- `didReport:info:` has been renamed to `didReportReaderEvent:info:` in Swift, for clarity
- Several error codes have been renamed:
  - `ReaderError` has been renamed `UnknownReaderError`
  - `SDKError` has been renamed `UnexpectedSdkError`
  - `NetworkError` has been renamed `UnknownNetworkError`
