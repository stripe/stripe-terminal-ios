//
//  SCPReader.h
//  StripeTerminal
//
//  Created by Ben Guo on 8/1/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPDeviceType.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Information about a reader that has been discovered or connected to the SDK.
 */
NS_SWIFT_NAME(Reader)
@interface SCPReader : NSObject

/**
 The reader's battery level, represented as a boxed float in the range `[0, 1]`.
 If the reader does not have a battery, or the battery level is unknown, this
 value is `nil`.
 */
@property (nonatomic, nullable, readonly) NSNumber *batteryLevel;

/**
 The reader's device type.
 */
@property (nonatomic, readonly) SCPDeviceType deviceType;

/**
 True if this is a simulated reader.

 `SCPDiscoveryConfiguration` objects with `simulated = true` produce simulated
 Readers.
 */
@property (nonatomic, readonly) BOOL simulated;

/**
 The reader's serial number.
 */
@property (nonatomic, readonly) NSString *serialNumber;

/**
 The reader's current device software version, or `nil` if this information is
 unavailable.
 */
@property (nonatomic, nullable, readonly) NSString *deviceSoftwareVersion;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
