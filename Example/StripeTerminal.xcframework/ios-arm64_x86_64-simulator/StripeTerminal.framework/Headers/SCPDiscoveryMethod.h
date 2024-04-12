//
//  SCPDiscoveryMethod.h
//  StripeTerminal
//
//  Created by Evan Sandler on 10/17/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The possible methods for discovering a reader. This is provided for convenience
 when working with `SCPDiscoveryConfiguration` objects.

 @see `SCPDiscoveryConfiguration`

 @see https://stripe.com/docs/terminal/readers/connecting
 */
typedef NS_ENUM(NSUInteger, SCPDiscoveryMethod) {
    /// @see `SCPBluetoothScanDiscoveryConfiguration`
    SCPDiscoveryMethodBluetoothScan,

    /// @see `SCPBluetoothProximityDiscoveryConfiguration`
    SCPDiscoveryMethodBluetoothProximity,

    /// @see `SCPInternetDiscoveryConfiguration`
    SCPDiscoveryMethodInternet,

    /// @see `SCPLocalMobileDiscoveryConfiguration`
    SCPDiscoveryMethodLocalMobile,

#ifdef SCP_USB_ENABLED
    /// @see `SCPUsbDiscoveryConfiguration`
    SCPDiscoveryMethodUsb
#endif
} NS_SWIFT_NAME(DiscoveryMethod);

NS_ASSUME_NONNULL_END
