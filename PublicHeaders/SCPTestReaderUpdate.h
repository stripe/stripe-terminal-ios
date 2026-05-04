//
//  SCPTestReaderUpdate.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2026-04-07.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPReaderSoftwareUpdate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The kind of simulated update to present during connection.
 */
typedef NS_ENUM(NSUInteger, SCPTestReaderUpdateType) {
    /// An optional update is available and will be announced during connect.
    SCPTestReaderUpdateTypeAvailable = 0,

    /// A required update will be performed during connect.
    SCPTestReaderUpdateTypeRequired,

    /// A required update exists. When connecting offline, connection will fail
    /// because the reader's version is not allowed. When connecting online,
    /// the reader will update and connect normally.
    SCPTestReaderUpdateTypeRequiredOffline,

    /// A required update exists but the reader's battery is too low for the
    /// update to begin. The connection will fail.
    SCPTestReaderUpdateTypeLowBattery,

    /// A required update exists but the reader's battery is too low for the
    /// update to begin. The update will fail but connection succeeds because
    /// the reader is on a recent software version.
    SCPTestReaderUpdateTypeLowBatterySucceedConnect,
} NS_SWIFT_NAME(TestReaderUpdateType);

/**
 Describes a simulated software update to apply during a test-mode connection.

 Create instances with the provided factory methods rather than `init`.
 */
NS_SWIFT_NAME(TestReaderUpdate)
@interface SCPTestReaderUpdate : NSObject <NSCopying>

/// The kind of simulated update.
@property (nonatomic, readonly) SCPTestReaderUpdateType updateType;

/// The component(s) the simulated update contains.
/// Only applicable for `available`, `required`, and `requiredOffline` types.
@property (nonatomic, readonly) SCPUpdateComponent components;

/// A simulated optional update containing the given component(s).
+ (instancetype)availableWithComponents:(SCPUpdateComponent)components
    NS_SWIFT_NAME(available(_:));

/// A simulated required update containing the given component(s).
+ (instancetype)requiredWithComponents:(SCPUpdateComponent)components
    NS_SWIFT_NAME(required(_:));

/// A simulated required-for-offline update containing the given component(s).
+ (instancetype)requiredOfflineWithComponents:(SCPUpdateComponent)components
    NS_SWIFT_NAME(requiredOffline(_:));

/// Simulates a required update that fails because the reader's battery is too
/// low. The connection will also fail.
+ (instancetype)lowBattery;

/// Simulates a required update that fails because the reader's battery is too
/// low, but the connection succeeds because the reader is on a recent version.
+ (instancetype)lowBatterySucceedConnect;

/// Randomly selects and returns a concrete update scenario to exercise various states,
/// or nil to simulate no update being available.
+ (nullable instancetype)random;

/// Unavailable. Use the factory methods on `SCPTestReaderUpdate`.
- (instancetype)init NS_UNAVAILABLE;
/// Unavailable. Use the factory methods on `SCPTestReaderUpdate`.
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
