//
//  SCPNfcUidCollectedData.h
//  StripeTerminal
//
//  Created by Mindy Lou on 9/23/25.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <StripeTerminal/SCPCollectedData.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Represents non-payment data collected using `collectData` with the NFC interface.
 */
NS_SWIFT_NAME(NfcUidCollectedData)
@interface SCPNfcUidCollectedData : SCPCollectedData

/**
 The NFC UID for the collected data, if it exists.
*/
@property (nonatomic, readonly, copy) NSString *uid;

/**
 You cannot directly instantiate `SCPNfcUidCollectedData`. You should only use
 one that has been returned by our SDK.

 @see SCPTerminal.shared.collectData()
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate `SCPNfcUidCollectedData`. You should only use
 one that has been returned by our SDK.

 @see SCPTerminal.shared.collectData()
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
