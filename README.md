# Stripe Terminal iOS SDK

Stripe Terminal enables you to build your own in-person checkout to accept payments in the physical world. Built on Stripe's payments network, Terminal helps you unify your online and offline payment channels. With the Stripe Terminal iOS SDK, you can connect to [pre-certified card readers](https://stripe.com/docs/terminal/designing-integration) from your iOS app and drive a customized in-store checkout flow. The Stripe Terminal iOS SDK is a proprietary, closed-source library maintained by Stripe, and the proprietary source code is Stripe's confidential information and is not made publicly available.

Get started with our [integration guides](https://stripe.com/docs/terminal/sdk/ios) and [sample integration](https://stripe.com/docs/terminal/integration-builder), or browse the [SDK reference documentation](https://stripe.dev/stripe-terminal-ios/docs/index.html).

> Upgrading from an older version of the SDK? See our [migration guide](https://stripe.com/docs/terminal/sdk-migration-guide) for guidance.

## Requirements
The Stripe Terminal iOS SDK is compatible with apps supporting iOS 14 and above.

## Try the example app
The iOS SDK includes an open-source example app, which you can use to familiarize yourself with the SDK and reader before starting your own integration.

To build the example app from source, you'll need to:

1. Navigate to the `Example` folder, and open `Example.xcworkspace` (make sure to open the **`.xcworkspace`** and not the `.xcodeproj`).
2. Navigate to our [example backend](https://github.com/stripe/example-terminal-backend) and click the button to deploy it on Heroku.
3. In `AppDelegate.swift`, set the URL of the Heroku app you just deployed.
3. Build and run the app. The SDK comes with a simple reader simulator, so you can get started without any physical hardware.

## Installation
We support CocoaPods and Swift Package Manager. If you prefer to install the library manually, please use the latest version from our [releases](https://github.com/stripe/stripe-terminal-ios/releases) page.

### Swift Package Manager

In Xcode, select **File > Swift Packages > Add Package Dependency** and enter https://github.com/stripe/stripe-terminal-ios

### CocoaPods

1. If you haven't already, install the latest version of [CocoaPods](https://guides.cocoapods.org/using/getting-started.html).

2. Add this line to your Podfile:
```
pod 'StripeTerminal', '~> 4.0'
```

3. Run the following command:
```
pod install
```

From now on, don't forget to use the `*.xcworkspace` file to open your project in Xcode, instead of the `.xcodeproj` file.

In the future, to update to the latest compatible version of the SDK, just run:
```
pod update StripeTerminal
```

### Manual
1. Navigate to our [releases](https://github.com/stripe/stripe-terminal-ios/releases) page, download StripeTerminal.xcframework.zip, and unzip it.

2. Drag `StripeTerminal.xcframework` to the Frameworks, Libraries, and Embedded Content section of your Xcode project’s General settings. Make sure to select "Copy items if needed".

When new versions of the SDK are released, repeat the above steps to update your installation.

### Configure your app

Location services must be enabled in order to use the iOS SDK. Add the following key-value pair to your app's `Info.plist` file:

- Privacy - Location When In Use Usage Description
  - Key: `NSLocationWhenInUseUsageDescription`
  - Value: "Location access is required in order to accept payments."

> Note: Stripe needs to know where payments occur to reduce risks associated with those charges and to minimize disputes. If the SDK can’t determine the iOS device’s location, payments are disabled until location access is restored.

For your app to run in the background and remain connected to the reader, add this key-value pair to your `Info.plist` file:

- Required background modes
  - Key: `UIBackgroundModes`
  - Value: `bluetooth-central` (Uses Bluetooth LE accessories)
  - Note the value is actually an array that you will need to add `bluetooth-central` to.

For your app to pass validation when submitting to the App Store, add the following key-value pairs as well:

- Privacy - Bluetooth Always Usage Description
  - Key: `NSBluetoothAlwaysUsageDescription`
  - Value: "This app uses Bluetooth to connect to supported card readers."

## Previous API References

We maintain an archive of the API reference for the previous major version.

- [3.9.0](https://stripe.dev/stripe-terminal-ios/3.9.0/index.html)
- [2.23.0](https://stripe.dev/stripe-terminal-ios/2.23.0/index.html)

