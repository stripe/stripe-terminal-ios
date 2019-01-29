1.0.0-b6

If you are using CocoaPods, update your Podfile:
```
pod 'StripeTerminal', '1.0.0-b6'
```

## Singleton initializer

`SCPTerminal` is now a singleton, and you will need to update your integration.

Before:
```
let terminal = Terminal(configuration: terminalConfig,
                        tokenProvider: apiClient,
                        delegate: self)
```

After:
```
// required
Terminal.setTokenProvider(apiClient)
// optional – set a listener to incorporate SDK logs into your own logs
Terminal.setLogListener({ ... })
// optional – set a delegate to receive status updates from the SDK
Terminal.shared.delegate = self
```

If you rely on destroying and recreating `SCPTerminal` instances to clear state (for example, to switch between different Stripe accounts in your app), you should instead use the `clearCachedCredentials` method.

`SCPTerminalConfiguration` has also been removed, and the `logLevel` property that was previously on `SCPTerminalConfiguration` is now a property on `SCPTerminal`.

## Loglines

The `terminal:didEmitLogline` method on `SCPTerminalDelegate` has been removed, and replaced with a static `setLogListener` method on `Terminal` class.

Previously, this delegate method was always called on the main thread. Now, the block you provide may be called from any thread.

You can use this optional method to listen for logs from the Stripe Terminal SDK and incorporate them into your own remote logs. Note that these loglines are subject to change, and provided for informational and debugging purposes only. You should not depend on them for behavior in your app.

To print internal logs from the SDK to the console, you can set logLevel to `.verbose` on the Terminal instance.

## createKeyedSource

The `createKeyedSource` method has been removed. If you were previously using this functionality, you will need to update your integration to use the [Stripe iOS SDK](https://github.com/stripe/stripe-ios) to handle this flow.

## updateReaderSoftware -> checkForReaderSoftwareUpdate

The `updateReaderSoftware` method has been renamed `checkForReaderSoftwareUpdate`, to make it clearer that this method only checks for any available reader software update. If an update is available, your delegate's `readerSoftwareUpdateAvailable` method will be called.
- The `UpdateReaderSoftwareParameters` class has been removed. When you call `checkForReaderSoftwareUpdate`, you'll need to pass a `ReaderSoftwareUpdateDelegate` and a `completion` block.
- `SCPUpdateReaderSoftwareDelegate` has been renamed `SCPReaderSoftwareUpdateDelegate`, for consistency with the `SCPReaderSoftwareUpdate` class.

## Discovery & Connecting to Readers

This update adds some additional checks to the discovery & connect process. You will
receive errors for some common integration mistakes:

- You must be actively discovering readers in order to connect to one. Calling
`SCPTerminal connectReader:` after canceling the `discoverReaders` cancelable will now
fail with `SCPErrorMustBeDiscoveringToConnect`
- Calling `SCPTerminal connectReader:` with a Reader from a different discovery process
will fail with `SCPErrorCannotConnectToUndiscoveredReader`.

We found & fixed a bug affecting reader discovery after a failed connect. The `Terminal`
is still discovering readers, but in previous beta releases it wasn't delivering updates
to the `DiscoveryDelegate`.

## Reader Session reuse, and clearConnectionToken -> clearCachedCredentials

`SCPTerminal` now caches & re-uses the reader session when reconnecting to the same
reader. This speeds up reconnection and makes it less likely to fail in spotty network
conditions.

Because of this, the public `clearConnectionToken` method that's necessary when changing
between testmode/livemode or between different accounts has been renamed for clarity.
