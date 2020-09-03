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
 Configuration options for discovering readers.

 Objects of this type get passed into the `Terminal.shared.discoverReaders()`
 method to control which devices get discovered, and how.

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
                         simulated:(BOOL)simulated DEPRECATED_MSG_ATTRIBUTE("All `initWithDeviceType` constructors of SCPDiscoveryConfiguration are deprecated; please use the corresponding `initWithDiscoveryMethod` constructor instead.");

/**
 Initializes a discovery configuration with the given device type and discovery method.

 Note that not all deviceType and discovery method combinations are valid.
 If the specified configuration is invalid, `discoverReaders` will fail.

 * The BBPOS Chipper 2X supports the Bluetooth Proximity and Bluetooth Scan discovery methods.
 * The BBPOS WisePad 3 only supports the Bluetooth Scan discovery method.
 * The Verifone P400 and BBPOS WisePOS E only support the Internet discovery method.

 @param deviceType          The device type to discover.
 @param discoveryMethod     The discovery method to use.
 @param simulated           Whether to use simulated discovery to discover a
 device simulator. The SDK comes with the ability to simulate behavior without
 using physical hardware. This makes it easy to quickly test your integration
 end-to-end, from pairing with a reader to taking payments.
 */
- (instancetype)initWithDeviceType:(SCPDeviceType)deviceType
                   discoveryMethod:(SCPDiscoveryMethod)discoveryMethod
                         simulated:(BOOL)simulated DEPRECATED_MSG_ATTRIBUTE("All `initWithDeviceType` constructors of SCPDiscoveryConfiguration are deprecated; please use the corresponding `initWithDiscoveryMethod` constructor instead.");

/**
 Initializes a discovery configuration with the given discovery method. All discoverable readers
 for that method will be discovered.

 @param discoveryMethod     The discovery method to use.
 @param simulated           Whether to use simulated discovery to discover a
 device simulator. The SDK comes with the ability to simulate behavior without
 using physical hardware. This makes it easy to quickly test your integration
 end-to-end, from pairing with a reader to taking payments.
*/
- (instancetype)initWithDiscoveryMethod:(SCPDiscoveryMethod)discoveryMethod
                              simulated:(BOOL)simulated;

/**
Initializes a discovery configuration with the given discovery method. All discoverable readers
for that method will be discovered.

@param discoveryMethod    The discovery method to use.
@param locationId         The optional location ID to filter the discovered
list to only readers at the specific location. Currently updating and creating
locations is not supported by this SDK and will need to take place on the
backend. Only available for the Internet discovery method.
@param simulated           Whether to use simulated discovery to discover a
device simulator. The SDK comes with the ability to simulate behavior without
using physical hardware. This makes it easy to quickly test your integration
end-to-end, from pairing with a reader to taking payments.
*/
- (instancetype)initWithDiscoveryMethod:(SCPDiscoveryMethod)discoveryMethod
                             locationId:(nullable NSString *)locationId
                              simulated:(BOOL)simulated;

/**
 Initializes a discovery configuration with the given device type and
 discovery method and location ID.

 Not all deviceType and discovery method combinations are valid and not all
 readers support locationId. If the specified configuration is invalid,
 `discoverReaders` will fail. Only the following `DiscoveryConfiguration`
 combinations are allowed:

 * The BBPOS Chipper 2X supports the Bluetooth Proximity and Bluetooth Scan discovery methods.
 * The BBPOS WisePad 3 only supports the Bluetooth Scan discovery method.
 * The Verifone P400 and BBPOS WisePOS E only support the Internet discovery method.

 @param deviceType          The device type to discover.
 @param discoveryMethod     The discovery method to use.
 @param locationId          The optional location ID to filter the discovered
 list to only readers at the specific location. Currently updating and creating
 locations is not supported by this SDK and will need to take place on the
 backend. Only available for the Internet discovery method.
 @see https://stripe.com/docs/api/terminal/locations
 @param simulated           Whether to use simulated discovery to discover a
 device simulator. The SDK comes with the ability to simulate behavior without
 using physical hardware. This makes it easy to quickly test your integration
 end-to-end, from pairing with a reader to taking payments.
 */
- (instancetype)initWithDeviceType:(SCPDeviceType)deviceType
                   discoveryMethod:(SCPDiscoveryMethod)discoveryMethod
                        locationId:(nullable NSString *)locationId
                         simulated:(BOOL)simulated DEPRECATED_MSG_ATTRIBUTE("All `initWithDeviceType` constructors of SCPDiscoveryConfiguration are deprecated; please use the corresponding `initWithDiscoveryMethod` constructor instead.");

/**
 The timeout (in seconds) after which `discoverReaders:` should fail. If the
 value is `0` (the default), discoverReaders will never timeout.

 Note that setting a timeout is not currently supported when using
 `SCPDiscoveryMethodBluetoothProximity`, or any simulated discovery. If you set
 a timeout when using these configurations, the timeout will be ignored.
 */
@property (nonatomic, assign, readwrite) NSUInteger timeout;

/**
 The reader device type to discover. Deprecated.
 */
@property (nonatomic, readonly) SCPDeviceType deviceType DEPRECATED_MSG_ATTRIBUTE("The `deviceType` property of SCPDiscoveryConfiguration is deprecated; please do not rely on the behavior of this property in your app.");

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
