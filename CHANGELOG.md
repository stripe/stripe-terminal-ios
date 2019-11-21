# Stripe Terminal iOS SDK changelog

If you are using CocoaPods, update your Podfile:
```
pod 'StripeTerminal', '1.0.1'
```

# 1.0.2 2019-09-26

* Updated CoreLocation usage to make `processPayment` and `readReusableCard` more likely to succeed.
* Removed the need to include `NSMicrophoneUsageDescription` in your app's `Info.plist` file.

# 1.0.1 2019-09-09

* Removed entries in `SCPDeprecations.h` from pre v1.0 beta releases. If you still need to update your app from a beta release, we recommend updating using v1.0.0 *first*, and then updating to the latest.
* Fixed `paymentMethodDetails.cardPresent.brand` to return the correct values for `.amex` and `.dinersClub`. In v1.0.0, these brands were incorrectly being returned as `.unknown`.

# 1.0.0 2019-06-07

* First generally available release.
* Changelog details for previous releases (our betas) can be found in the release notes for each release: [https://github.com/stripe/stripe-terminal-ios/releases]
