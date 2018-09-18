# CHANGELOG

- The framework has been renamed "StripeTerminal". You will need to remove `StripePOS.framework` from your app, and add the new `StripeTerminal` framework.
- Endpoints have also been (backwards-compatibly) renamed. Please update your backend to use `v1/terminal/activation_token`. Your existing integration will continue working, but we will be migrating all users off the legacy `/point_of_sale/activation_token` and `pos_activation_token` endpoints.
- The `SCP` prefix has been removed from all types in Swift. Xcode should provide helpful errors to help migrate your Swift files.
- `ActivationTokenProvider` has been renamed `ConnectionTokenProvider`, and `getToken` has been renamed `fetchConnectionToken`, for clarity.
- `connect` has been renamed `connectReader`, and `disconnect` has been renamed `disconnectReader`, for clarity.

## Reader Input
We've replaced all references to reading a "card" with more general names centered around "Reader Input".

- The `attachSource:readCardDelegate:completion` method has been renamed `collectPaymentMethod:delegate:completion:`.
- `ReadCardDelegate` has been renamed `ReaderInputDelegate`.
- The `didBeginWaitingForCard` delegate method has been renamed `didBeginWaitingForReaderInput`.
- The `CardPresentationType` enum has been replaced with an option set, `ReaderInputOptions`.
- The `ReadCardPrompt` enum has been renamed `ReaderInputPrompt`.
- The `didRequestReadCardPrompt` delegate method has been renamed `didRequestReaderInputPrompt`.
- The `readSource:readCardDelegate:completion` method has been renamed `readSource:delegate:completion:`.
- Additional prompts have been added to `ReaderInputPrompt`, to make it clearer how to proceed in various card presentation scenarios. For example, the SDK will now surface a "Try Another Read Method" prompt if the presented card could not be read.

## Detecting unexpected disconnects
`TerminalDelegate` has a new optional `didDisconnectUnexpectedlyFromReader` delegate method, which you can use to handle unexpected disconnects (e.g. if the reader runs out of battery, or is powered off).

If you were previously using the `didChangeConnectionStatus` method to detect unexpected disconnects, please start using this new delegate method. ConnectionStatus changes cannot be used to reliably determine when a reader disconnects unexpectedly.

## Switching accounts
We've added a new `clearConnectionToken` method. You should use this to switch accounts in your app, e.g. to switch between using test and live Stripe API keys on your backend. Please note that you should only initialize a Terminal once in your app. Behavior is undefined if you create multiple Terminal instances.

In order to switch accounts in your app:

- if a reader is connected, call `disconnect`
- call `clearConnectionToken`
- call `discover` and `connect` to connect to a reader. The `connect` call will request a new activation token from your provider.

An overview of the lifecycle of a connection token:

- When a Terminal is initialized, the SDK attempts to proactively request
a connection token from your backend server.
- Under the hood, when `connect` is called, the SDK uses the connection token
along with reader information to create a reader session.
- Subsequent calls to `connect` require a new connection token. If you
disconnect from a reader, and then call `connect` again, the SDK will request
a connection token from your backend server.
- When your app becomes active, the SDK will attempt to proactively request
a connection token from your backend server as needed.

## Other changes
- `PaymentParameters` has been renamed `PaymentIntentParameters`
- The `createKeyedSourceWithSTPPaymentCardTextField` method has been renamed to be less verbose.
- The `connect` method will now error if location access is disabled – surfacing this error earlier is a better user (and developer) experience.
- The `didChange(_,status:)` methods have been renamed to `didChange(_,connectionStatus:)` and `didChange(_,paymentStatus:)` in Swift.
