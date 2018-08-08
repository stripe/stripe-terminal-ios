//
//  SCPReaderUpdate.h
//  StripePOS
//
//  Created by Ben Guo on 12/21/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPDiscoveryConfiguration.h"
#import "SCPJSONDecodable.h"

NS_ASSUME_NONNULL_BEGIN

/**
 The estimated amount of time for an update. Note that these times are estimates;
 actual times may vary depending on your network connection.
 */
typedef NS_ENUM(NSUInteger, SCPUpdateTimeEstimate) {
    /**
     The update should take less than 1 minute to complete.
     */
    SCPUpdateTimeEstimateLessThan1Minute,
    /**
     The update should take 1-2 minutes to complete.
     */
    SCPUpdateTimeEstimate1To2Minutes,
    /**
     The update should take 2-5 minutes to complete.
     */
    SCPUpdateTimeEstimate2To5Minutes,
    /**
     The update should take 5-10 minutes to complete.
     */
    SCPUpdateTimeEstimate5To10Minutes,
};

/**
 An object representing a reader update.
 */
@interface SCPReaderUpdate : NSObject

/**
 The estimated amount of time for the update.
 */
@property (nonatomic, readonly) SCPUpdateTimeEstimate estimatedUpdateTime;

/**
 You cannot directly instantiate `SCPReaderUpdate`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPReaderUpdate`. You should only use
 one that has been returned by our SDK.
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
