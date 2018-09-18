//
//  SCPDiscoveryConfiguration.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/17/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPDeviceType.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Configuration for discovering readers.
 */
NS_SWIFT_NAME(DiscoveryConfiguration)
@interface SCPDiscoveryConfiguration : NSObject

/**
 The timeout for discovery, in seconds. If the value is 0, discovery will not
 timeout. Default is 0 (no timeout).
 */
@property (nonatomic, assign, readwrite) NSUInteger timeout;

/**
 The reader's device type. Default is Chipper2X.
 */
@property (nonatomic, assign, readwrite) SCPDeviceType deviceType;

@end

NS_ASSUME_NONNULL_END
