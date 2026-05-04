//
//  SCPSimulatedOfflineModeConfiguration.h
//  StripeTerminal
//
//  Created by Stripe.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPSimulatedOfflineMode.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Configuration for simulating offline mode for testing offline payment flows
 without physically disconnecting from the network.

 Set this via
 `SCPTerminal.shared.setSimulatedOfflineModeConfiguration`. The SDK
 and the connected smart reader can be configured independently, allowing you
 to test scenarios where only one side loses connectivity.

 @note For testing only. Setting a non-default configuration while connected
 to a livemode reader raises an error.
 */
NS_SWIFT_NAME(SimulatedOfflineModeConfiguration)
@interface SCPSimulatedOfflineModeConfiguration : NSObject <NSCopying>

/**
 The simulated network state for the SDK.

 Default: `SCPSimulatedOfflineModeDisabled`
 */
@property (nonatomic, assign, readonly) SCPSimulatedOfflineMode sdkOfflineMode;

/**
 The simulated network state for the connected smart reader. This setting only
 applies to smart readers which have independent network connectivity. For
 Bluetooth and USB readers, this setting is ignored since all network calls flow
 through the SDK.

 Default: `SCPSimulatedOfflineModeDisabled`
 */
@property (nonatomic, assign, readonly) SCPSimulatedOfflineMode readerOfflineMode;

/**
 Use `SCPSimulatedOfflineModeConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPSimulatedOfflineModeConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

/**
 The default configuration: both SDK and reader offline modes are
 `SCPSimulatedOfflineModeDisabled`.
 */
@property (nonatomic, class, readonly) SCPSimulatedOfflineModeConfiguration *defaultConfiguration;

/**
 Convenience preset that puts both the SDK and a connected smart reader into
 immediate offline mode (`SCPSimulatedOfflineModeOfflineImmediate`).
 */
@property (nonatomic, class, readonly) SCPSimulatedOfflineModeConfiguration *fullOfflineConfiguration;

@end

/**
 A builder class for `SCPSimulatedOfflineModeConfiguration`.
 */
NS_SWIFT_NAME(SimulatedOfflineModeConfigurationBuilder)
@interface SCPSimulatedOfflineModeConfigurationBuilder : SCPBuilder <SCPSimulatedOfflineModeConfiguration *>

/// Set the `sdkOfflineMode` for the configuration that will be built.
- (instancetype)setSdkOfflineMode:(SCPSimulatedOfflineMode)sdkOfflineMode;

/// Set the `readerOfflineMode` for the configuration that will be built.
- (instancetype)setReaderOfflineMode:(SCPSimulatedOfflineMode)readerOfflineMode;

@end

NS_ASSUME_NONNULL_END
