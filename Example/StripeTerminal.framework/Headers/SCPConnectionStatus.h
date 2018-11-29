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
 The possible connection statuses for a terminal.
 */
typedef NS_ENUM(NSUInteger, SCPConnectionStatus) {
    /**
     Terminal is not connected to a reader.
     */
    SCPConnectionStatusNotConnected,
    /**
     Terminal is connected to a reader.
     */
    SCPConnectionStatusConnected,
    /**
     Terminal is busy processing a command.
     */
    SCPConnectionStatusBusy,
} NS_SWIFT_NAME(ConnectionStatus);

NS_ASSUME_NONNULL_END
