//
//  SCPBuzzerVolumeParameters.h
//  StripeTerminal
//
//  Created by Ben Wu on 7/28/26.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPReaderSettingsParameters.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The buzzer (beep) volume level to apply to a reader via
 `[SCPTerminal setReaderSettings:completion:]` with `SCPBuzzerVolumeParameters`.
 */
typedef NS_ENUM(NSUInteger, SCPBuzzerVolumeLevel) {
    /** The lowest audible volume. Resolves to 1. */
    SCPBuzzerVolumeLevelLow,
    /** The loudest volume the reader supports. Resolves to `SCPBuzzerVolume.maxVolume`. */
    SCPBuzzerVolumeLevelHigh,
    /** A specific volume in the range `1...SCPBuzzerVolume.maxVolume`, set via `initWithVolume:`. */
    SCPBuzzerVolumeLevelCustom,
} NS_SWIFT_NAME(BuzzerVolumeLevel);

/**
 Parameters for setting the buzzer (beep) volume on a reader via
 `[SCPTerminal setReaderSettings:completion:]`.

 Use `initWithLevel:` for `Low` or `High`, or `initWithVolume:` for a
 specific custom volume in the range `1...maxVolume`.

 Passing these parameters to a reader that does not support buzzer volume
 control returns `SCPErrorFeatureNotAvailableWithConnectedReader`.
 */
NS_SWIFT_NAME(BuzzerVolumeParameters)
@interface SCPBuzzerVolumeParameters : NSObject <SCPReaderSettingsParameters>

/**
 The volume level to apply.
 */
@property (nonatomic, readonly) SCPBuzzerVolumeLevel level;

/**
 The custom volume to set. Only meaningful when `level` is
 `SCPBuzzerVolumeLevelCustom` — must be in the range `1...maxVolume`,
 where `maxVolume` comes from `SCPBuzzerVolume.maxVolume`. When
 `level` is `Low` or `High`, this value is undefined and must not be used.
 */
@property (nonatomic, readonly) NSInteger volume;

/**
 Create parameters for `Low` or `High` volume.

 @param level `SCPBuzzerVolumeLevelLow` or `SCPBuzzerVolumeLevelHigh`.
 Passing `SCPBuzzerVolumeLevelCustom` is a programmer error; use
 `initWithVolume:` instead.
 */
- (instancetype)initWithLevel:(SCPBuzzerVolumeLevel)level NS_SWIFT_NAME(init(level:));

/**
 Create parameters for a specific custom volume.

 Sets `level` to `SCPBuzzerVolumeLevelCustom` automatically. The volume
 must be in the range `1...maxVolume` (from `SCPBuzzerVolume.maxVolume`);
 passing a value outside that range causes `setReaderSettings:completion:` to
 return `SCPErrorInvalidRequiredParameter`.

 @param volume The target volume. Must be `>= 1` and `<= maxVolume`.
 */
- (instancetype)initWithVolume:(NSInteger)volume NS_SWIFT_NAME(init(volume:));

/**
 Use `initWithLevel:` or `initWithVolume:` instead.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithLevel:` or `initWithVolume:` instead.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
