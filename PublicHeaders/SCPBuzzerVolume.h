//
//  SCPBuzzerVolume.h
//  StripeTerminal
//
//  Created by Ben Wu on 7/28/26.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The buzzer (beep) volume state of a reader that supports buzzer volume control.

 Obtain this via `SCPReaderBuzzerVolume.volume` after calling
 `[SCPTerminal retrieveReaderSettings:]`.
 */
NS_SWIFT_NAME(BuzzerVolume)
@interface SCPBuzzerVolume : NSObject

/**
 The reader's current buzzer volume, in the range `1...maxVolume`.
 */
@property (nonatomic, readonly) NSInteger currentVolume;

/**
 The maximum buzzer volume the reader supports. A valid volume is in the
 range `1...maxVolume`.
 */
@property (nonatomic, readonly) NSInteger maxVolume;

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
