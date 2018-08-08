//
//  SCPReader.h
//  StripePOS
//
//  Created by Ben Guo on 8/1/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPDiscoveryConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Information about a reader.
 */
@interface SCPReader : NSObject

/**
 The reader's battery level (in the range [0, 1]). If the reader does not
 have a battery or the battery level is unknown, the value of this property
 will be 1.
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
 You cannot directly instantiate `SCPReader`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPReader`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
