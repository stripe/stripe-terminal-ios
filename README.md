# Stripe Terminal iOS <img src="https://img.shields.io/badge/Beta 1-brightgreen.svg">

[Request a Beta invite](https://stripe.com/terminal#request-invite) to get started with Stripe Terminal.

## Requirements
The Stripe Terminal iOS SDK is compatible with apps supporting iOS 10 and above.

## Try the example app
This repository includes an example iOS app, which you can use to familiarize yourself with the SDK and reader before starting your own integration. To get started:

1. Navigate to the `Example` folder, and open `Example.xcodeproj`.
2. In `RootViewController.swift`, set your Stripe Account's test secret API key. A backend simulator has been included as part of the example app for demonstration purposes only. Note that you should _never_ store your Stripe account's secret API key in your own app. For more information, see https://stripe.com/docs/keys
3. Build and run the app. The Stripe Terminal SDK includes a simple Reader Simulator, so you can get started without any physical hardware.

Note: the example app comes with the Stripe Terminal SDK pre-installed, but uses a few other dependencies. We've included pre-built dependencies using Swift 4.2. You may need to run `./setup.sh` to re-build the app's dependencies for your environment.

## Installation
We recommend that you install the SDK using Cocoapods. If you prefer to install the library manually, please use the latest version from our [releases](https://github.com/stripe/stripe-terminal-ios/releases) page.

### Cocoapods

1. If you haven't already, install the latest version of [CocoaPods](https://guides.cocoapods.org/using/getting-started.html).

2. Add this line to your Podfile:
```
pod 'Stripe'
```

3. Run the following command:
```
pod install
```

From now on, don't forget to use the `*.xcworkspace` file to open your project in Xcode, instead of the `.xcodeproj` file.

In the future, to update to the latest version of the SDK, just run:
```
pod update Stripe
```

### Manual
1. Navigate to our [releases](https://github.com/stripe/stripe-terminal-ios/releases) page, download StripeTerminal.framework.zip, and unzip it.

2. Drag `StripeTerminal.framework` to the Embedded Binaries section of your Xcode project’s General settings. Make sure to select "Copy items if needed".

3. Navigate to the Build Phases section of your Xcode project settings, and create a new Run Script Build Phase. Paste the following snippet into the text field:
```
bash "${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/StripeTerminal.framework/integrate_framework.sh
```

When new versions of the SDK are released, repeat steps one and two to update your installation

### Configure your app

Location services must be enabled in order to use the iOS SDK. Add the `NSLocationWhenInUseUsageDescription` key to your app’s Info.plist file. Xcode displays this key as “Privacy - Location When In Use Usage Description”. Write an appropriate description for your app (e.g., "Location access is required in order to accept payments.").

> Note: Stripe needs to know where payments occur to reduce risks associated with those charges and to minimize disputes. If the SDK can’t determine the iOS device’s location, payments are disabled until location access is restored.

For your app to run in the background and remain connected to the reader, add this key-value pair to your `Info.plist` file:
- Key: `UIBackgroundModes` (Required background modes)
- Value: `bluetoooth-central` (Uses Bluetooth LE accessories)

For your app to pass validation when submitting to the App Store, add the following key-value pairs as well:
- Privacy - Bluetooth Peripheral Usage Description
  - Key: `NSBluetoothPeripheralUsageDescription`
  - Value: “Bluetooth access is required in order to connect to supported bluetooth card readers.”
- Privacy - Microphone Usage Description
  - Key: `NSMicrophoneUsageDescription`
  - Value: “Bluetooth access is required in order to connect to supported bluetooth card readers.”



## Documentation
- [API Reference](https://stripe.github.io/stripe-terminal-ios/docs/index.html)


