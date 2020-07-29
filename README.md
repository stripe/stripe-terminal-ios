# Stripe Terminal iOS SDK

For information on migrating from beta versions of the iOS SDK, see the [Stripe Terminal Beta Migration Guide](https://stripe.com/docs/terminal/beta-migration-guide).

## Requirements
The Stripe Terminal iOS SDK is compatible with apps supporting iOS 9 and above.

## Try the example app
The iOS SDK includes an open-source example app, which you can use to familiarize yourself with the SDK and reader before starting your own integration.

To build the example app from source, you'll need to:

1. Navigate to the `Example` folder, and open `Example.xcodeproj`.
2. Navigate to our [example backend](https://github.com/stripe/example-terminal-backend) and click the button to deploy it on Heroku.
3. In `AppDelegate.swift`, set the URL of the Heroku app you just deployed.
4. Build and run the app. The SDK comes with a simple reader simulator, so you can get started without any physical hardware.

Note: the example app comes with the Stripe Terminal SDK pre-installed, but uses a few other dependencies. We've included pre-built dependencies using Swift 4.2. You may need to run `./setup.sh` to re-build the app's dependencies for your environment.

For a more fully-featured example, see our Stripe Sample with Terminal on iOS: the [Rocket Rides Pilot App](https://github.com/stripe-samples/sample-terminal-ios-app).

## Installation
We recommend that you install the SDK using CocoaPods. If you prefer to install the library manually, please use the latest version from our [releases](https://github.com/stripe/stripe-terminal-ios/releases) page.

### CocoaPods

1. If you haven't already, install the latest version of [CocoaPods](https://guides.cocoapods.org/using/getting-started.html).

2. Add this line to your Podfile:
```
pod 'StripeTerminal', '~> 1.0'
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
1. Navigate to our [releases](https://github.com/stripe/stripe-terminal-ios/releases) page, download StripeTerminal.framework.zip, and unzip it.

2. Drag `StripeTerminal.framework` to the Embedded Binaries section of your Xcode project’s General settings. Make sure to select "Copy items if needed".

3. Navigate to the Build Phases section of your Xcode project settings, and create a new Run Script Build Phase. Paste the following snippet into the text field:
```
bash "${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/StripeTerminal.framework/integrate-framework.sh"
```

When new versions of the SDK are released, repeat steps one and two to update your installation.

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

- Privacy - Bluetooth Peripheral Usage Description
  - Key: `NSBluetoothPeripheralUsageDescription`
  - Value: “Bluetooth access is required in order to connect to supported bluetooth card readers.”
- Privacy - Bluetooth Always Usage Description
  - Key: `NSBluetoothAlwaysUsageDescription`
  - Value: "This app uses Bluetooth to connect to supported card readers."

## Documentation
- [Getting Started](https://stripe.com/docs/terminal/ios)
- [API Reference](https://stripe.github.io/stripe-terminal-ios/docs/index.html)

## Verifone P400 support in the iOS SDK

iOS connectivity to the Verifone P400 reader is currently in public beta. Not all capabilities of the iOS SDK are available when connected to the Verifone P400, and some features available in the JavaScript SDK are not available in the iOS SDK. As the beta progresses, we aim to add these capabilities to the iOS SDK.

Notably, the following iOS methods are not available when connected to the Verifone P400:

- [`createPaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)createPaymentIntent:completion:)
- [`cancelPaymentIntent`](https://stripe.dev/stripe-terminal-ios/docs/Classes/SCPTerminal.html#/c:objc(cs)SCPTerminal(im)cancelPaymentIntent:completion:)

