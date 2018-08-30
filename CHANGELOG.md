# CHANGELOG

## Important changes
- The `getToken` method has been renamed to `getActivationToken`, and the `posDeviceId` parameter has been removed.
- **Migrating**:
  - In your app, rename `getToken` to `getActivationToken`, and remove the `posDeviceId` parameter.
  - On your backend, call `v1/point_of_sale/activation_token` to create an activation token. (Note that the endpoint has been renamed). You do not need to pass any parameters to this method.

- The `cancel` method on `SCPCancelable` now uses a nullable `NSError` in its completion block instead of a `BOOL`, to improve usability.
- **Migrating**: when canceling a command, check if `error` is non-nil instead of checking if `success` is false.

- The `discover` method has been renamed to `discoverReaders`
- **Migrating**: replace `discover` with `discoverReaders`

- The `terminal:didUpdateDiscoveryResults:` delegate method has been renamed to `terminal:didUpdateDiscoveredReaders:`
- **Migrating**: replace `didUpdateDiscoveryResults` with `didUpdateDiscoveredReaders`

- We've noticed that App Store validation now detects usage of microphone access APIs in our internal reader hardware library. In your Info.plist, please add this key-value pair:
  - Key: `NSMicrophoneUsageDescription` (Privacy - Microphone Usage Description)
  - Value: "Microphone access is required in order to connect to supported audio input card readers."

## Other changes
- `SCPActivationTokenProvider` no longer requires conformance to `NSObjectProtocol` in your Swift app.
- `SCPTerminalDelegate` has a new optional `didEmitLogline:` method, which you can use to incorporate loglines from the Stripe POS SDK into your own telemetry tooling.
- `SCPAddress` was unused, and has been removed.
- `SCPTerminal` has a new `retrievePaymentIntent` method, which you can use to retrieve a PaymentIntent created on your backend. If the information required to create a PaymentIntent isn't readily available in your app, you can create the PaymentIntent on your backend, and pass the ID of the PaymentIntent to your app.
