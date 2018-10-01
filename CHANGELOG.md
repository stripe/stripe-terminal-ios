# CHANGELOG

### Card insert and removal events
- You can now use the new `ReaderEvent` enum to detect card insert and removal events, using the optional `didEmitReaderEvent` method on `TerminalDelegate`.
- Note: if you have received readers directly from Stripe via the Alpha program, you will need to update your reader to the latest firmware configuration in order to see card insert and removal events. You can do this by implementing the SDK's `updateReaderSoftware` workflow, or by using the provided example app, which includes the ability to update readers. You can download the Example app directly by joining the [TestFlight beta](https://stripe-terminal-app.herokuapp.com).

### UpdateReaderSoftware
`UpdateReader` has been renamed `UpdateReaderSoftware` to distinguish between updating the Reader object in the Stripe API, and updating the software on the physical reader. Other related changes:

- The `updateReader` method has been renamed `updateReaderSoftware`, and returns a `Cancelable`.
- The `UpdateReaderDelegate` protocol has been renamed `UpdateReaderSoftwareDelegate`. Methods within this protocol have also been renamed.
- The `ReaderUpdate` object has been renamed `ReaderSoftwareUpdate`
- `InstallUpdateCompletionBlock` has been renamed `InstallUpdateBlock`, as it is not a completion block.
- A `deviceSoftwareVersion` property has been added to the `ReaderSoftwareUpdate` object, which you can use to determine the target update version.
- The `updateReaderSoftware` method call now requires an `UpdateReaderSoftwareParameters` object. Typically, you will not need to modify the default parameters object, as nearly all readers are registered in the production environment. However, if you received readers as part of the alpha program, you may need to set `environment` to `test` in order to update some of your readers. If this is the case, please contact your account manager to arrange exchanging this reader for a production reader.

### Other changes
- The polymorphic `Terminal.string(from:)` methods in Swift have been renamed to individual `stringFrom{Type}` methods.
- The `didDisconnectUnexpectedlyFrom` method has been renamed to `didDisconnectUnexpectedlyFromReader` in Swift, for consistency.
- The `AttachingSource` value in the `PaymentStatus` enumeration has been renamed to `CollectingPaymentMethod`.
- The `ReaderInputPrompt` enumeration has a new `TryAnotherCard` value, used to indicate that the presented card is invalid. This value is used to indicate that the user should try another card. This indicates the user should try a different card. In contrast, the `TryAnotherReadMethod` prompt means the user should either: 1. try another read method on the same card (e.g. swipe if the card was inserted), or 2. try a different card.
