//
//  SCPReader.h
//  StripeTerminal
//
//  Created by Ben Guo on 8/1/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBatteryStatus.h>
#import <StripeTerminal/SCPDeviceType.h>
#import <StripeTerminal/SCPJSONDecodable.h>
#import <StripeTerminal/SCPLocation.h>
#import <StripeTerminal/SCPLocationStatus.h>
#import <StripeTerminal/SCPReaderNetworkStatus.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPReaderSoftwareUpdate;

/**
 Information about a card reader that has been discovered by or connected to
 the SDK.

 Some of the properties are only applicable to a certain device type.
 These properties are labeled with the reader or reader type to which they apply.

 @see https://stripe.com/docs/terminal/readers
 */
NS_SWIFT_NAME(Reader)
@interface SCPReader : NSObject <SCPJSONDecodable>

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
+ (instancetype)new NS_UNAVAILABLE;

/**
 The reader's device type.
 */
@property (nonatomic, readonly) SCPDeviceType deviceType;

/**
 True if this is a simulated reader.

 `SCPDiscoveryConfiguration` objects with `simulated` set to `true` produce simulated
 readers.
 */
@property (nonatomic, readonly) BOOL simulated;

/**
 The Stripe unique identifier for the reader.
 */
@property (nonatomic, nullable, readonly) NSString *stripeId;

/**
 The ID of the reader's [Location](https://stripe.com/docs/api/terminal/locations/object).

 Internet readers remain registered to the location specified when registering
 the reader to your account. For internet readers, this field represents that location.
 If you need to change your internet reader's location, re-register the reader and
 specify the new location id in the `location` param.
 See https://stripe.com/docs/api/terminal/readers/create

 Bluetooth and Apple Built-In readers are designed to be more mobile and must be
 registered to a location upon each connection. This field represents the last
 location that the reader was registered to. If the reader has not been used before,
 this field will be nil. If you associate the reader to a different location while calling
 `connectBluetoothReader`, this field will update to that new location's ID.

 @see https://stripe.com/docs/api/terminal/locations
 */
@property (atomic, nullable, readonly) NSString *locationId;

/**
 Used to tell whether the `location` field has been set.
 */
@property (atomic, readonly) SCPLocationStatus locationStatus;

/**
 The details of the location this reader is registered to, if any.

 During discovery, `location` will be nil for Bluetooth readers that have never
 been connected to.

 You must assign a reader to a location from the SDK when attempting to connect to it.

 @see https://stripe.com/docs/api/terminal/locations
 @see https://stripe.com/docs/terminal/fleet/locations
 @see `SCPConnectionConfiguration`
 */
@property (atomic, nullable, readonly) SCPLocation *location;

/**
 The reader's serial number.
 */
@property (nonatomic, readonly) NSString *serialNumber;

/**
 The reader's current device software version, or `nil` if this information is
 unavailable.
 */
@property (atomic, nullable, readonly) NSString *deviceSoftwareVersion;

#pragma mark Bluetooth Reader Properties

/**
 The available update for this reader, or nil if no update is available.
 This update will also have been announced via
 `- [BluetoothReaderDelegate reader:didReportAvailableUpdate:]`

 Install this update with `- [Terminal installAvailableUpdate]`

 calls to `installAvailableUpdate` when `availableUpdate` is nil will result
 in `- [BluetoothReaderDelegate reader:didFinishInstallingUpdate:error:]` called
 immediately with a nil update and nil error.

 (Bluetooth readers only.)
 */
@property (atomic, nullable, readonly) SCPReaderSoftwareUpdate *availableUpdate;

/**
 The reader's battery level, represented as a boxed float in the range `[0, 1]`.
 If the reader does not have a battery, or the battery level is unknown, this
 value is `nil`.

 (Bluetooth readers only.)
 */
@property (atomic, nullable, readonly) NSNumber *batteryLevel;

/**
 The reader's battery status. Usable as a general classification for the current
 battery state.

 (Bluetooth readers only.)

 @see SCPBatteryStatus
 */
@property (atomic, readonly) SCPBatteryStatus batteryStatus;

/**
 The reader's charging state, represented as a BOOL
 If the reader does not have a battery, or the battery level is unknown, this
 value is `nil`.

 (Bluetooth readers only.)
 */
@property (atomic, nullable, readonly) NSNumber *isCharging;

#pragma mark Internet Reader Properties

/**
 The IP address of the reader.

 (Internet readers only.)
 */
@property (nonatomic, nullable, readonly) NSString *ipAddress;

/**
 The networking status of the reader: usually `online` or `offline`. Note that
 non-Internet readers `status` will always be `offline`.

 Internet readers will return a status of `unknown` if this reader was discovered while operating in offline mode.
 (Internet readers only).
 */
@property (nonatomic, readonly) SCPReaderNetworkStatus status;

/**
 A custom label that may be given to a reader for easier identification.

 (Internet readers only.)
 */
@property (nonatomic, nullable, readonly) NSString *label;

@end

NS_ASSUME_NONNULL_END
