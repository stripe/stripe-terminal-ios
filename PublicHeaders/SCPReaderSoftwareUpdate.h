//
//  SCPReaderSoftwareUpdate.h
//  StripeTerminal
//
//  Created by Ben Guo on 12/21/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPDiscoveryConfiguration.h"
#import "SCPJSONDecodable.h"

NS_ASSUME_NONNULL_BEGIN

/**
 The estimated amount of time for an update. Note that these times are estimates;
 actual times may vary depending on your network connection.

 @see https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt#software-updates-and-releases
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
     The update should take 5-15 minutes to complete.
     */
    SCPUpdateTimeEstimate5To15Minutes,
} NS_SWIFT_NAME(UpdateTimeEstimate);

/**
 An object representing a reader update.

 @see https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt#software-updates-and-releases
 */
NS_SWIFT_NAME(ReaderSoftwareUpdate)
@interface SCPReaderSoftwareUpdate : NSObject

/**
 The estimated amount of time for the update.
 */
@property (nonatomic, readonly) SCPUpdateTimeEstimate estimatedUpdateTime;

/**
 The target version for the update.
 */
@property (nonatomic, readonly) NSString *deviceSoftwareVersion;

/**
 Returns an unlocalized string for the given update time estimate.
 */
+ (NSString *)stringFromUpdateTimeEstimate:(SCPUpdateTimeEstimate)estimate;

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
