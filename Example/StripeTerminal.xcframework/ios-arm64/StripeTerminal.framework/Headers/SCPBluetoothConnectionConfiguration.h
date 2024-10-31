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

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPConnectionConfiguration.h>
#import <StripeTerminal/SCPMobileReaderDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This class lets you define Bluetooth reader connection options.

 An object of this class should get passed into `Terminal.shared.connectReader()`.
 */

NS_SWIFT_NAME(BluetoothConnectionConfiguration)
@interface SCPBluetoothConnectionConfiguration : SCPConnectionConfiguration

/**
 The MobileReaderDelegate to use for this connection to the reader.
 */
@property (nonatomic, weak, readonly) id<SCPMobileReaderDelegate> delegate;

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
 Implement the `reader:didStartReconnect:` and related callbacks  for your application to respond accordingly to
 reconnection attempts.

 When set to false, the SDK will immediately surface any disconnection through ReaderDelegate.

 Defaults to true.
 */
@property (nonatomic, assign, readonly) BOOL autoReconnectOnUnexpectedDisconnect;

/**
 Use `SCPBluetoothConnectionConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPBluetoothConnectionConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The `CollectConfigurationBuilder` is used to create a `CollectConfiguration` object.
 */
NS_SWIFT_NAME(BluetoothConnectionConfigurationBuilder)
@interface SCPBluetoothConnectionConfigurationBuilder : SCPBuilder <SCPBluetoothConnectionConfiguration *>

/// Create a `BluetoothConnectionConfiguration` with the provided delegate and locationId.
- (instancetype)initWithDelegate:(id<SCPMobileReaderDelegate>)delegate locationId:(NSString *)locationId NS_DESIGNATED_INITIALIZER;

/// Set the locationId property for the `BluetoothConnectionConfiguration` object that will be built.
- (SCPBluetoothConnectionConfigurationBuilder *)setLocationId:(NSString *)locationId;

/// Set the autoReconnectOnUnexpectedDisconnect property for the `BluetoothConnectionConfiguration` object that will be built.
- (SCPBluetoothConnectionConfigurationBuilder *)setAutoReconnectOnUnexpectedDisconnect:(BOOL)autoReconnectOnUnexpectedDisconnect;

/**
 Use `initWithLocationId:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithLocationId:`
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
