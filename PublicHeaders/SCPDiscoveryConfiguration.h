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

 Note that `simulated` is not supported by `verifoneP400`.

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

 Note that not all deviceType and discovery method combinations are valid and
 not all readers support simulated mode. If the specified configuration is
 invalid, `discoverReaders` will fail.

 | DeviceType     | DiscoveryMethod                                      | simulated         |
 | -------------- | -----------------------------------------------------|-------------------|
 | `chipper2X`    | `bluetoothProximity` (recommended), `bluetoothScan`  | `true` or `false` |
 | `verifoneP400` | `internet`                                           | `true` or `false` |

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
 Initializes a discovery configuration with the given device type and
 discovery method and location ID.

 Not all deviceType and discovery method combinations are valid and not all
 readers support locationId or simulated mode. If the specified configuration is
 invalid, `discoverReaders` will fail. Only the following `DiscoveryConfiguration`
 combinations are allowed:

 | DeviceType     | DiscoveryMethod                                      | locationId      | simulated         |
 | -------------- | -----------------------------------------------------|-----------------|-------------------|
 | `chipper2X`    | `bluetoothProximity` (recommended), `bluetoothScan`  | `nil`           | `true` or `false` |
 | `verifoneP400` | `internet`                                           | `nil` or string | `true` or `false` |

 @param deviceType          The device type to discover.
 @param discoveryMethod     The discovery method to use.
 @param locationId          The optional location ID to filter the discovered
 list to only readers at the specific location. Currently updating and creating
 locations is not supported by this SDK and will need to take place on the
 backend.
 @see https://stripe.com/docs/api/terminal/locations
 @param simulated           Whether to use simulated discovery to discover a
 device simulator. The SDK comes with the ability to simulate behavior without
 using physical hardware. This makes it easy to quickly test your integration
 end-to-end, from pairing with a reader to taking payments.
 */
- (instancetype)initWithDeviceType:(SCPDeviceType)deviceType
                   discoveryMethod:(SCPDiscoveryMethod)discoveryMethod
                        locationId:(nullable NSString *)locationId
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
 A location ID that can be used to filter discovery result so only readers
 registered to that location are returned. Currently this is only applicable
 to VerifoneP400 readers.
 */
@property (nonatomic, copy, nullable, readonly) NSString *locationId;

/**
 Use `initWithDeviceType:simulated:` or `initWithDeviceType:discoveryMethod:simulated:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithDeviceType:simulated:` or `initWithDeviceType:discoveryMethod:simulated:`
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
