//
//  SCPReaderBuzzerVolume.h
//  StripeTerminal
//
//  Created by Ben Wu on 7/28/26.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPBuzzerVolume.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The result of a buzzer volume retrieval, as returned by
 `SCPReaderSettings.buzzerVolume` after `[SCPTerminal retrieveReaderSettings:]`.

 When the connected reader supports buzzer volume control, `volume` is non-nil
 and `error` is `nil`. When the reader does not support buzzer volume control,
 `error` is non-nil and `volume` is `nil`.
 */
NS_SWIFT_NAME(ReaderBuzzerVolume)
@interface SCPReaderBuzzerVolume : NSObject

/**
 The reader's current buzzer volume state. Non-nil when the reader supports
 buzzer volume control.
 */
@property (nonatomic, nullable, readonly) SCPBuzzerVolume *volume;

/**
 Non-nil when the reader does not support buzzer volume control.
 */
@property (nonatomic, nullable, readonly) NSError *error;

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
