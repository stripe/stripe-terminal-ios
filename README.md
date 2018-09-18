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

## Install the SDK
https://stripe.com/docs/terminal/ios#install


