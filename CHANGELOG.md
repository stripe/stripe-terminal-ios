1.0.0

If you are using CocoaPods, update your Podfile:
```
pod 'StripeTerminal', '1.0.0'
```

## Changes from 1.0.0-rc2

* Adds `Reader.simulated` property, to tell whether a reader is simulated or not.

* The `Terminal.connectedReader` property will now be `nil` when the SDK calls your
`TerminalDelegate.terminal(_:didReportUnexpectedReaderDisconnect:)` method. In previous
releases, it contained the previously connected `Reader` object. The previously connected
reader is still available, as a parameter of this method.

- When a `SCPErrorSessionExpired` has been thrown (see `SCPErrors.h` for more details on when
this is thrown) we now call `TerminalDelegate.didReportUnexpectedReaderDisconnect` after a
successful auto-disconnect. Note there is a small chance the disconnect fails and this 
callback will not be called. You can check `Terminal.connectionStatus` in your completion block
that received the `SCPErrorSessionExpired` to see if your reader is still connected.
