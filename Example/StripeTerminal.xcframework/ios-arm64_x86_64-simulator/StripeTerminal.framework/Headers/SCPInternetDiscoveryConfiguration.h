//
//  SCPInternetDiscoveryConfiguration.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2023-08-09.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPDiscoveryConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The Internet discovery method searches for internet-connected readers,
 such as the Stripe S700 or the BBPOS WisePOS E.

 When discovering a reader with this method `didUpdateDiscoveredReaders`
 will only be called once with a list of readers from `/v1/terminal/readers`.
 Note that this will include readers that are both online and offline.

 Because the discovery process continues if connecting to a discovered
 reader fails, the SDK will refresh the list of `SCPReader`s and call
 `didUpdateDiscoveredReaders` with the results. For more details about failed
 connect calls, see `-[SCPTerminal connectReader:connectionConfig:cancelable:completion:]`

 Create instances of this class using a `SCPInternetDiscoveryConfigurationBuilder`.

 @see https://stripe.com/docs/api/terminal/readers/list
 */
NS_SWIFT_NAME(InternetDiscoveryConfiguration)
@interface SCPInternetDiscoveryConfiguration : NSObject <SCPDiscoveryConfiguration>

/**
 A location ID that can be used to filter discovery result so only readers
 registered to that location are returned. Filtering discovery by a location is
 only applicable to Internet readers; this parameter must be nil when discovering
 Bluetooth readers.
 */
@property (nonatomic, copy, nullable, readonly) NSString *locationId;

@end

/**
 Builder class for SCPInternetDiscoveryConfiguration

 Example usage:

 `[[[SCPInternetDiscoveryConfigurationBuilder new] setLocationId:@"tml_123"] build]`

 `try InternetDiscoveryConfigurationBuilder().setLocationId("tml_123").build()`
 */
NS_SWIFT_NAME(InternetDiscoveryConfigurationBuilder)
@interface SCPInternetDiscoveryConfigurationBuilder : SCPBuilder <SCPInternetDiscoveryConfiguration *>

/// Set the simulated property for the discovery configuration that will be built
- (SCPInternetDiscoveryConfigurationBuilder *)setSimulated:(BOOL)simulated;

/// Set the locationId property for the discovery configuration that will be built
- (SCPInternetDiscoveryConfigurationBuilder *)setLocationId:(nullable NSString *)locationId;

@end

NS_ASSUME_NONNULL_END
