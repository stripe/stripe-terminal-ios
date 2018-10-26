//
//  SCPDiscoveryMethod.h
//  StripeTerminal
//
//  Created by Evan Sandler on 10/17/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

/**
 The possible methods for discovering a reader.
 */
typedef NS_ENUM(NSUInteger, SCPDiscoveryMethod) {
    /**
     Bluetooth Scan
     */
    SCPDiscoveryMethodBluetoothScan,
    /**
     Bluetooth Proximity
     */
    SCPDiscoveryMethodBluetoothProximity,
} NS_SWIFT_NAME(DiscoveryMethod);

NS_ASSUME_NONNULL_END
