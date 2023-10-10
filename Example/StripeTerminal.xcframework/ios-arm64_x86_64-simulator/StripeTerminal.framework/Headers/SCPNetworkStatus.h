//
//  SCPNetworkStatus.h
//  StripeTerminal
//
//  Created by Bill Finn on 2022-04-28.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The possible network connection statuses for the SDK.
 */
typedef NS_ENUM(NSUInteger, SCPNetworkStatus) {
    /**
     The SDK has not determined if it can communicate with stripe.com.
     */
    SCPNetworkStatusUnknown,
    /**
     The SDK is not able to communicate with stripe.com.
     */
    SCPNetworkStatusOffline,
    /**
     The SDK is able to communicate with stripe.com.
     */
    SCPNetworkStatusOnline,
} NS_SWIFT_NAME(NetworkStatus);

NS_ASSUME_NONNULL_END
