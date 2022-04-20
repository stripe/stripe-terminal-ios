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

#import <StripeTerminal/SCPDiscoveryConfiguration.h>
#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The estimated amount of time for an update. Note that these times are estimates;
 actual times may vary depending on your network and Bluetooth connection.

 @see https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt#reader-software-releases
 @see https://stripe.com/docs/terminal/readers/bbpos-wisepad3#reader-software-releases
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
 A bitmask identifying what exact updates are contained within this update.

 Note that the time estimates documented here are for each individual piece. Updates
 will often contain multiple components together. Check the `estimatedUpdateTime` to
 see how long the entire update process is expected to take for all components.

 @see https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt#reader-software-releases
 @see https://stripe.com/docs/terminal/readers/bbpos-wisepad3#reader-software-releases
 */
typedef NS_OPTIONS(NSUInteger, SCPUpdateComponent) {
    /**
     If set, the update contains incremental changes to the reader. If this is
     the only component being updated, the `deviceSoftwareVersion` will *not*
     differ from the existing installed version. Incremental updates should take
     less than 1 minute.
     */
    SCPUpdateComponentIncremental = 1 << 0,
    /**
     If set, this update contains updated firmware for this reader. Firmware updates
     can take 5 to 15 minutes.
     */
    SCPUpdateComponentFirmware = 1 << 1,
    /**
     If set, this update contains a new configuration for this reader. These may
     contain regional changes or other card network updates. Configuration updates
     are expected to take 1 to 2 minutes.
     */
    SCPUpdateComponentConfig = 1 << 2,
    /**
     If set, this update contains updated encryption keys for the reader.
     Updating keys should take less than 1 minute.
     */
    SCPUpdateComponentKeys = 1 << 3,
} NS_SWIFT_NAME(UpdateComponent);

/**
 An object representing a reader update.

 @see https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt#reader-software-releases
 @see https://stripe.com/docs/terminal/readers/bbpos-wisepad3#reader-software-releases
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
 The components that will be installed in this update.
 */
@property (nonatomic, readonly) SCPUpdateComponent components;

/**
 The date at which this update will be required to be installed. If this date
 is in the past, the SDK will automatically update the reader upon connection.
 The reader will not be able to transact until the update is complete.

 @see https://stripe.com/docs/terminal/readers/bbpos-wisepad3#updating-reader-software
 */
@property (nonatomic, readonly) NSDate *requiredAt;

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
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
