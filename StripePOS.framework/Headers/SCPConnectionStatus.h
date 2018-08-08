//
//  SCPConnectionStatus.h
//  StripePOS
//
//  Created by Ben Guo on 8/25/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

/**
 The possible connection statuses for an SCPTerminal.
 */
typedef NS_ENUM(NSUInteger, SCPConnectionStatus) {
    /**
     SCPTerminal is not connected to a reader.
     */
    SCPConnectionStatusNotConnected,
    /**
     SCPTerminal is connected to a reader.
     */
    SCPConnectionStatusConnected,
    /**
     SCPTerminal is busy processing a command.
     */
    SCPConnectionStatusBusy,
};

NS_ASSUME_NONNULL_END
