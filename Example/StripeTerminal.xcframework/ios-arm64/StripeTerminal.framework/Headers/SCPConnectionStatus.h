//
//  SCPConnectionStatus.h
//  StripeTerminal
//
//  Created by Ben Guo on 8/25/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The possible reader connection statuses for the SDK.

 @see https://stripe.com/docs/terminal/readers/connecting
 */
typedef NS_ENUM(NSUInteger, SCPConnectionStatus) {
    /**
     The SDK is not connected to a reader.
     */
    SCPConnectionStatusNotConnected,
    /**
     The SDK is discovering readers.
     */
    SCPConnectionStatusDiscovering,
    /**
     The SDK is currently connecting to a reader.
     */
    SCPConnectionStatusConnecting,
    /**
     The SDK is connected to a reader.
     */
    SCPConnectionStatusConnected,
} NS_SWIFT_NAME(ConnectionStatus);

NS_ASSUME_NONNULL_END
