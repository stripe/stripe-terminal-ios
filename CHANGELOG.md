1.0.1

If you are using CocoaPods, update your Podfile:
```
pod 'StripeTerminal', '1.0.1'
```

## Changes

* Removed entries in `SCPDeprecations.h` from pre v1.0 beta releases. If you still need to update your app from a beta release, we recommend updating using v1.0.0 *first*, and then updating to the latest.
* Fixed `paymentMethodDetails.cardPresent.brand` to return the correct values for `.amex` and `.dinersClub`. In v1.0.0, these brands were incorrectly being returned as `.unknown`.
