//
//  SCPReader.h
//  StripeTerminal
//
//  Created by Ben Guo on 8/1/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPDeviceType.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Information about a reader.
 */
NS_SWIFT_NAME(Reader)
@interface SCPReader : NSObject

/**
 The reader's battery level (in the range [0, 1]). If the reader does not
 have a battery or the battery level is unknown, the value of this property
 will be 1 or 0.
 */
@property (nonatomic, readonly) float batteryLevel;

/**
 The reader's device type.
 */
@property (nonatomic, readonly) SCPDeviceType deviceType;

/**
 The reader's serial number.
 */
@property (nonatomic, readonly) NSString *serialNumber;

/**
 The reader's current device software version, or nil if this information is
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
