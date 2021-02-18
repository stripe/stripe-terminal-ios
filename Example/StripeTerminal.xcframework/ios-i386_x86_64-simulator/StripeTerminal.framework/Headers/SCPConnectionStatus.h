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
     The SDK is connected to a reader.
     */
    SCPConnectionStatusConnected,
    /**
     The SDK is currently connecting to a reader.
     */
    SCPConnectionStatusConnecting,
} NS_SWIFT_NAME(ConnectionStatus);

NS_ASSUME_NONNULL_END
