# stripe-pos-ios

During the private alpha program, the iOS Point of Sale SDK will only be available using Carthage or manual installation. For more information on installing the SDK, see the [Setup Guide](https://stripe.com/docs/point-of-sale).

This repository contains:
1. An example app (in the `Example` directory).
2. iOS API reference docs (in the `docs` directory; open `index.html` to view).
3. A `CHANGELOG` file documenting changes from the previous version.

Please send us lots of feedback! You can either:
- [File an issue on Github](https://github.com/stripe/stripe-pos-ios/issues/new) (for minor bug reports, nits, or feature requests)
- Email me directly: bg@stripe.com (please also cc charlessang@stripe.com) (for integration help or blocking bug reports)
- Email your account manager (for more general product questions)

## Documentation overview

### Getting started
- Point of Sale Overview: https://stripe.com/docs/point-of-sale
- Backend Setup Guide: https://stripe.com/docs/point-of-sale/backend
- iOS SDK Setup Guide: https://stripe.com/docs/point-of-sale/ios
- Your First Payment: https://stripe.com/docs/point-of-sale/first-payment

### Completing your integration
- iOS SDK Reference: https://stripe.com/docs/point-of-sale/ios/reference
- Common SDK Reference: https://stripe.com/docs/point-of-sale/sdk-reference
- Chipper 2X User Guide: https://stripe.com/docs/point-of-sale/readers/chipper2x
- Testing Your Integration: https://stripe.com/docs/point-of-sale/testing

## Requirements
The Stripe Point of Sale SDK is compatible with apps supporting iOS 10 and above. The included Example app requires Xcode 9.

## Running the example app
- In `RootViewController.swift`, set your Stripe Account's test secret key. Note that this is for demonstration purposes only. You should NEVER store your account's secret API key in your app. For more information, see https://stripe.com/docs/keys
- The dependencies for the Example app have been pre-downloaded, so you shouldn't need to run `carthage` to build the app.

