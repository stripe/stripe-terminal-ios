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
 */
NS_SWIFT_NAME(DiscoveryConfiguration)
@interface SCPDiscoveryConfiguration : NSObject

/**
 Initializes a discovery configuration with the given device type.
 The the discovery method is the default for that device type.

 @param deviceType      The device type to discover.
 */
- (instancetype)initWithDeviceType:(SCPDeviceType)deviceType;

/**
 Initializes a discovery configuration with the given device type and discovery method.

 Note that this initializer returns an optional value because not all deviceType
 and method combinations are valid. For the Chipper 2X, we recommend using the
 bluetoothProximity discovery method, which lets you discover a single reader by
 holding it next to the iOS device.
 
 @param deviceType      The device type to discover.
 @param method          The discovery method to use.
 */
- (nullable instancetype)initWithDeviceType:(SCPDeviceType)deviceType method:(SCPDiscoveryMethod)method;

/**
 The timeout (in seconds) after which discoverReaders should fail. If the
 value is 0 (the default), discoverReaders will never timeout.

 Note that setting a timeout is not currently supported when using:
 - The BluetoothProximity DiscoveryMethod
 - The ReaderSimulator DeviceType
 */
@property (nonatomic, assign, readwrite) NSUInteger timeout;

/**
 The reader device type to discover.
 */
@property (nonatomic, readonly) SCPDeviceType deviceType;

/**
 The method by which to discover readers.
 */
@property (nonatomic, readonly) SCPDiscoveryMethod method;

/**
 Use `initWithDeviceType:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithDeviceType:`
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
