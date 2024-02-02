//
//  SCPDisconnectReason.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2023-11-15.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Possible reasons for Bluetooth reader disconnects.
 */
typedef NS_ENUM(NSUInteger, SCPDisconnectReason) {
    /**
     Unexpected disconnect.
     */
    SCPDisconnectReasonUnknown,

    /**
     Terminal.disconnectReader was called.
     */
    SCPDisconnectReasonDisconnectRequested,

    /**
     Terminal.rebootReader was called.
     */
    SCPDisconnectReasonRebootRequested,

    /**
     Reader disconnected after performing its required security reboot. This will
     happen if the reader has been running for 24 hours. To control this you can
     call Terminal.rebootReader which will reset the 24 hour timer.
     */
    SCPDisconnectReasonSecurityReboot,

    /**
     Reader disconnected because its battery was critically low and needs to be charged before it can be used.
     */
    SCPDisconnectReasonCriticallyLowBattery,

    /**
     Reader was powered off.
     */
    SCPDisconnectReasonPoweredOff,

    /**
     Bluetooth was disabled on the device.
     */
    SCPDisconnectReasonBluetoothDisabled,

} NS_SWIFT_NAME(DisconnectReason);

NS_ASSUME_NONNULL_END
