//
//  SCPDiscoveryConfiguration.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/17/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPDeviceType.h"
#import "SCPDiscoveryMethod.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Configuration for discovering readers.

 @see https://stripe.com/docs/terminal/readers/connecting
 */
NS_SWIFT_NAME(DiscoveryConfiguration)
@interface SCPDiscoveryConfiguration : NSObject

/**
 Initializes a discovery configuration with the given device type, selecting
 the default discovery method for the device type.

 @param deviceType          The device type to discover.
 @param simulated           Whether to use simulated discovery to discover a
 device simulator. The SDK comes with the ability to simulate behavior without
 using physical hardware. This makes it easy to quickly test your integration
 end-to-end, from pairing with a reader to taking payments.
 */
- (instancetype)initWithDeviceType:(SCPDeviceType)deviceType
                         simulated:(BOOL)simulated;

/**
 Initializes a discovery configuration with the given device type and discovery method.

 Note that not all deviceType and discovery method combinations are valid. If
 the specified configuration is invalid, `discoverReaders` will fail.

 | DeviceType | valid DiscoveryMethods                               |
 | ---------- | -----------------------------------------------------|
 | chipper2X  | bluetoothProximity (recommended), bluetoothScan      |

 @param deviceType          The device type to discover.
 @param discoveryMethod     The discovery method to use.
 @param simulated           Whether to use simulated discovery to discover a
 device simulator. The SDK comes with the ability to simulate behavior without
 using physical hardware. This makes it easy to quickly test your integration
 end-to-end, from pairing with a reader to taking payments.
 */
- (instancetype)initWithDeviceType:(SCPDeviceType)deviceType
                   discoveryMethod:(SCPDiscoveryMethod)discoveryMethod
                         simulated:(BOOL)simulated;

/**
 The timeout (in seconds) after which `discoverReaders:` should fail. If the
 value is `0` (the default), discoverReaders will never timeout.

 Note that setting a timeout is not currently supported when using
 `SCPDiscoveryMethodBluetoothProximity`, or any simulated discovery. If you set
 a timeout when using these configurations, the timeout will be ignored.
 */
@property (nonatomic, assign, readwrite) NSUInteger timeout;

/**
 The reader device type to discover.
 */
@property (nonatomic, readonly) SCPDeviceType deviceType;

/**
 The method by which to discover readers.
 */
@property (nonatomic, readonly) SCPDiscoveryMethod discoveryMethod;

/**
 Whether to use simulated discovery to discover a device simulator.

 The Terminal SDK comes with the ability to simulate behavior without using
 physical hardware. This makes it easy to quickly test your integration
 end-to-end, from pairing with a reader to taking payments.
 */
@property (nonatomic, readonly) BOOL simulated;

/**
 Use `initWithDeviceType:simulated:` or `initWithDeviceType:discoveryMethod:simulated:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithDeviceType:simulated:` or `initWithDeviceType:discoveryMethod:simulated:`
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
