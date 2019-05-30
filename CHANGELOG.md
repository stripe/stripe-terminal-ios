1.0.0-rc2

If you are using CocoaPods, update your Podfile:
```
pod 'StripeTerminal', '1.0.0-rc2'
```

## Other changes

- Adds `SCPCardPresentDetails.generatedCard`, which provides a reusable `card` PaymentMethod
from a processed PaymentIntent. See https://stripe.com/docs/terminal/payments/saving-cards#saving-payment-intent-card
for more details.

- The `ReadReusableCardParameters` object passed to `Terminal.readReusableCard()` now includes a
`customer` property which, if included, will attach the newly created `PaymentMethod` to the
specified customer.

- `Terminal.readReusableCard()` no longer prompts for `ReaderInputOptionTapCard`

- Fixes a race condition caused by quickly canceling `Terminal.collectPaymentMethod()` or
`Terminal.readReusableCard()`, which would lead to subsequent commands failing with
`SCPErrorBusy`.

- Removes `SCPErrorCancelFailedReaderBusy`. Starting with this release, the SDK now takes
as long as it needs to ensure the command is canceled or completes (whichever happens
first), instead of sometimes reporting that it was unable to cancel for certain hardware
states and then continuing the command.

- We will now attempt to automatically disconnect the card reader if a server request 
results in an `SCPErrorSessionExpired` error. The reader must be reconnected to start 
a new session. If our attempt at disconnecting the reader fails you may need to disconnect it
yourself.

- The `Terminal.checkForUpdate` completion block will now be passed nil and no error
rather than being passed `SCPErrorNoAvailableReaderSoftwareUpdate` when there is no update present.

- `Terminal.collectPaymentMethod` and `Terminal.readReusableCard` will now fail with
`SCPErrorCardLeftInReader` when the reader still contains the credit card from a previous
transaction. The same card can be used for more than one transaction, but it must be
removed and re-inserted for each one. Previously, instead of failing immediately, the
`collectPaymentMethod`/`readReusableCard` request would fail silently and users needed to
cancel the request in order to proceed.
