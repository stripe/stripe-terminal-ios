1.0.0-b4

If you are using CocoaPods, update your Podfile:
```
pod 'StripeTerminal', '1.0.0-b4'
```

### API updates
- When using the `transferDataDestination` parameter to create a `PaymentIntent`, you you must also specify the `onBehalfOf` parameter, and this must match the destination account. This makes it explicit that charges are settled in the country of the specified account, and that the connected account’s address and phone number show up on the customer’s credit card statement. For more information, see https://stripe.com/docs/connect/charges-transfers#on-behalf-of
- The `stripeAccount` property on `SCPPaymentIntentParameters` has been removed. To create a PaymentIntent via the SDK on behalf of a connected account, you should set the `Stripe-Account` header when creating a connection token on your backend. The SDK will inherit this connected account setting from the connection token, and use the same `Stripe-Account` header whenever it creates or confirms a PaymentIntent.

### Pairing improvements
We've made some updates to the Bluetooth Proximity discovery method. If you your app will be used in a busy environment, with multiple iOS devices pairing to multiple available readers at the same time, **we highly recommend using the bluetooth proximity discovery method**.
- After a reader has been discovered using the proximity method, the LEDs located above the reader's power button will start flashing multiple colors. After discovering the reader, your app should prompt the user to tap a button to connect to the reader. You may want to tell your user to confirm that the reader is flashing.
- When discovering a reader using the Bluetooth Proximity method, the `didUpdateDiscoveredReaders` delegate method will be called twice. It will be called for the first time when the reader is initially discovered. The reader's LEDs will begin flashing. After a short delay, `didUpdateDiscoveredReaders` will be called a second time with an updated reader object, populated with additional info about the device, like its battery level.
- `BluetoothProximity` is now the default discovery method when initializing `DiscoveryConfiguration` with a device type.

### Integration tips
- If you are using `readSource` method to defer a payment for later, note that the transaction will *not* receive the beneficial rates and liability shift associated with card present transactions. **Most integrations should not use `readSource`**. If you are simply collecting a payment from a customer, you should create a `PaymentIntent` and use the associated `collectPaymentMethod` and `confirmPaymentIntent` methods.
- Make sure your integration **captures the PaymentIntent**, and does so on your backend. Our example app previously included a client-side `BackendSimulator` class, for demonstration purposes only. You should be sure not to do this in your own app. Secret API keys should be kept confidential and stored only on your own servers. Your account’s secret API key can perform any API request to Stripe without restriction, and you should never hardcode your secret API key into your app. The example app now uses an example backend that you can easily deploy to Heroku: https://github.com/stripe/example-terminal-backend

### Other changes
- The timeout for reading a card with `collectPaymentMethod` has been increased from 1 minute to 5 minutes. If reading a card times out, `collectPaymentMethod` will fail with the error code `SCPErrorCardReadTimedOut`.
- 
