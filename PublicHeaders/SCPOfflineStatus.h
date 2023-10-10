//
//  SCPOfflineStatus.h
//  StripeTerminal
//
//  Created by Bill Finn on 2023-08-18.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPOfflineStatusDetails.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Provides offline status details for the connected reader and the SDK.
 */
NS_SWIFT_NAME(OfflineStatus)
@interface SCPOfflineStatus : NSObject

/**
 Returns the offline status details for the connected smart reader (if any). If
 no smart reader is connected, this value will be null.
 */
@property (nonatomic, nullable, readonly, strong) SCPOfflineStatusDetails *reader;

/**
 Returns the offline status details for the POS device, useful for the case of mobile readers where the POS acts as the agent for storing and forwarding payment requests.
 */
@property (nonatomic, readonly, strong) SCPOfflineStatusDetails *sdk;

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
