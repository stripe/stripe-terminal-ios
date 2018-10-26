//
//  SCPDiscoveryConfiguration.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/17/18.
//  Copyright © 2018 Stripe. All rights reserved.
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
 
 @param deviceType      The device type to discover.
 @param method          The discovery method to use.
 */
- (nullable instancetype)initWithDeviceType:(SCPDeviceType)deviceType method:(SCPDiscoveryMethod)method;

/**
 The timeout (in seconds) after which discoverReeaders should fail. If the
 value is 0 (the default), discoverReaders will never timeout.
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
