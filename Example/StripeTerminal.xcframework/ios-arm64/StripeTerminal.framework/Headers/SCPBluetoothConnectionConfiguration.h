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

#import <StripeTerminal/SCPReconnectionDelegate.h>

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
 When set to true, the Terminal SDK  will attempt a Bluetooth auto-reconnection on any unexpected disconnect.
 You must also set an `autoReconnectionDelegate` for your application to respond accordingly to reconnection attempts.
 Enabling `autoReconnectOnUnexpectedDisconnect` without providing an `autoReconnectionDelegate` will error with `SCPErrorReaderConnectionConfigurationInvalid`.

 When set to false, we will immediately surface any disconnection through TerminalDelegate.

 Defaults to false.
 */
@property (nonatomic, assign, readonly) BOOL autoReconnectOnUnexpectedDisconnect;

/**
 Contains callback methods for Bluetooth auto-reconnection.
 */
@property (nonatomic, weak, readonly, nullable) id<SCPReconnectionDelegate> autoReconnectionDelegate;

/**
 Initialize your connect options with a location ID.
 */
- (instancetype)initWithLocationId:(NSString *)locationId;

/**
 Initialize your connect options with a location ID and an expected behavior for unexpected disconnects.
 */
- (instancetype)initWithLocationId:(NSString *)locationId autoReconnectOnUnexpectedDisconnect:(BOOL)autoReconnectOnUnexpectedDisconnect autoReconnectionDelegate:(nullable id<SCPReconnectionDelegate>)autoReconnectionDelegate;

@end

NS_ASSUME_NONNULL_END
