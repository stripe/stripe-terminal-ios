//
//  SCPBluetoothConnectionConfiguration.h
//  StripeTerminal
//
//  Created by Catriona Scott on 8/6/19.
//  Copyright © 2019 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPConnectionConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This class lets you define Bluetooth reader connection options.

 An object of this class should get passed into `Terminal.shared.connectBluetoothReader()`.
 */

NS_SWIFT_NAME(BluetoothConnectionConfiguration)
@interface SCPBluetoothConnectionConfiguration : SCPConnectionConfiguration

/**
 The ID of the [Location](https://stripe.com/docs/api/terminal/locations) which the reader should be registered to during connection.

 If the provided ID matches the location the reader is already registered to, the
 location will not be changed.

 When connecting to a simulated reader, pass in the reader's pre-existing mock location.
 You can find the mock location ID on the reader object returned to the DiscoveryDelegate,
 on the `locationId` property.

 @see https://stripe.com/docs/terminal/readers/fleet-management#bbpos-wisepad3-discovery
 */
@property (nonatomic, readonly) NSString *locationId;

/**
 Initialize your connect options with a location ID.
 */
- (instancetype)initWithLocationId:(NSString *)locationId;

@end

NS_ASSUME_NONNULL_END
