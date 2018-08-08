//
//  SCPDiscoveryConfiguration.h
//  StripePOS
//
//  Created by Ben Guo on 7/17/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The possible device types for a reader.
 */
typedef NS_ENUM(NSUInteger, SCPDeviceType) {
    /**
     BBPOS Chipper 2X BT
     */
    SCPDeviceTypeChipper2X,
};

/**
 The possible discovery methods.
 */
typedef NS_ENUM(NSUInteger, SCPDiscoveryMethod) {
    /**
     Bluetooth discovery
     */
    SCPDiscoveryMethodBluetooth,
};

/**
 SCPDiscoveryConfiguration represents all the options you can set when
 discovering readers.
 */
@interface SCPDiscoveryConfiguration : NSObject

/**
 The timeout for discovery, in seconds. If the value is 0, discovery will not
 timeout. The default is 0 (no timeout).
 */
@property (nonatomic, assign, readwrite) NSUInteger timeout;

/**
 The reader's device type. Default is Chipper2X.
 */
@property (nonatomic, assign, readwrite) SCPDeviceType deviceType;

/**
 The discovery method. Currently, Bluetooth (the default) is the only option.
 */
@property (nonatomic, assign, readwrite) SCPDiscoveryMethod discoveryMethod;

/**
 Returns an unlocalized string for the given device type.
 */
+ (NSString *)stringFromDeviceType:(SCPDeviceType)deviceType;

@end

NS_ASSUME_NONNULL_END
