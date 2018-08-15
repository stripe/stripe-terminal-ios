# CHANGELOG

- The SDK will now throw an exception if `discover` is called and your app's Info.plist is missing the `NSBluetoothPeripheralUsageDescription` key. This key is required for your app to pass validation when submitting to the App Store.
- Fixes an issue where calling `discover` immediately after a reader became disconnected would fail.
- Miscellaneous internal improvements
