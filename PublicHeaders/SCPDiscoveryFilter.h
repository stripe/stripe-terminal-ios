//
//  SCPDiscoveryFilter.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2025-10-31.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The `SCPDiscoveryFilter` contains information used to single out a reader during the discovery process.
 When a filter is provided, only the reader matching the filter will be returned during discovery,
 and discovery will complete once the reader is found.
 */
NS_SWIFT_NAME(DiscoveryFilter)
@interface SCPDiscoveryFilter : NSObject

/**
 Creates a filter to discover a reader by its serial number.

 @param serialNumber The serial number of the reader to discover. Must not be empty.
 @return A discovery filter configured to match the specified serial number, or nil if serialNumber is empty.
 */
+ (nullable instancetype)filterBySerialNumber:(NSString *)serialNumber NS_SWIFT_NAME(bySerialNumber(_:));

/**
 Creates a filter to discover a reader by its reader ID (tmr_*).

 @param readerId The ID of the reader to discover. Must start with "tmr_".
 @return A discovery filter configured to match the specified reader ID, or nil if readerId is invalid.
 */
+ (nullable instancetype)filterByReaderId:(NSString *)readerId NS_SWIFT_NAME(byReaderId(_:));

/**
 Creates a filter that allows all readers to be discovered (no filtering).

 @return A discovery filter that does not restrict discovery.
 */
+ (instancetype)none;

/// Use the factory methods to create instances.
- (instancetype)init NS_UNAVAILABLE;

/// Use the factory methods to create instances.
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
