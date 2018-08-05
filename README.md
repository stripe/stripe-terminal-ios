# stripe-pos-ios

During the private alpha program, the iOS Point of Sale SDK will only be available for download as a zipped release package. You can find the latest alpha release of SDK on the [Releases page](https://github.com/stripe/stripe-pos-ios/releases). (After the alpha phase has ended, we'll make the SDK available via the usual channels, Cocoapods and Carthage.)

The zipped release package contains:
- The iOS framework
- An example app (open Example/Example.xcodeproj)
- API reference docs (open docs/index.html)
- A changelog, which you can use to get started updating your integration from a previous version.

Documentation:
- Using the Chipper 2X: https://stripe.com/docs/point-of-sale/readers/chipper2x
- iOS Integration Guide: https://stripe.com/docs/point-of-sale/ios
- Testing Your Integration: https://stripe.com/docs/point-of-sale/testing
- Backend Reference: https://stripe.com/docs/point-of-sale/backend

Please send us lots of feedback! You can either:
- [File an issue on Github](https://github.com/stripe/stripe-pos-ios/issues/new) (for minor bug reports, nits, or feature requests)
- Email me directly: bg@stripe.com (please also cc charlessang@stripe.com) (for integration help or blocking bug reports)
- Email your account manager (for more general product questions)

# Requirements
The Stripe Point of Sale SDK is compatible with apps supporting iOS 10 and above.

# Getting Started

## Running the example app
- The dependencies for the Example app are included in the release, so you shouldn't need to run `carthage` to build the app.
- In `RootViewController.swift`, set your Stripe Account's test secret key. Note that this is for demonstration purposes only – you should NEVER store your account's secret API key in your app. For more information, see https://stripe.com/docs/keys

## Adding the SDK to your app
- Add `StripePOS.framework` to your project.
- Location services must be enabled on at all times when using your Point of Sale app. Stripe needs to know where charges take place to reduce the risks associated with those charges and minimize disputes. Add the `NSLocationWhenInUseUsageDescription` key to your app's `Info.plist` file. (Xcode displays this key as "Privacy - Location When In Use Usage Description"). Pick an appropriate description for your app, e.g. "Location access is required in order to accept payments."
- In order for your app to remain connected to the reader when it enters the background, add the `UIBackgroundModes` ("Required background modes") key to your app's `Info.plist` file.
  - **Chipper 2X**: Add the value `bluetoooth-central` ("Uses Bluetooth LE accessories").
  - **WisePad 2**: Add the value `external-accessory` ("External Accessory Communication")
- **WisePad 2**: Add the `UISupportedExternalAccessoryProtocols` ("Supported External Accessory Protocols") key to your app's `Info.plist` file. Add the value `com.bbpos.bt.wisepad`.

# Next steps
- Follow the guide at https://stripe.com/docs/point-of-sale to start integrating the Stripe Point of Sale SDK in your app.
- To view API reference documentation for the SDK, open `docs/index.html`.
