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

    /**
     The mobile reader automatically powers down after 10 hours of inactivity when not charging,
     to conserve battery life
     */
    SCPDisconnectReasonIdlePowerDown,

    /**
     The mobile reader has been disconnected due to the USB cable being physically disconnected. This may also occur
     when the USB driver is disabled in the app settings.
     */
    SCPDisconnectReasonUsbDisconnected,

    /**
     The mobile reader’s Bluetooth signal has been lost, either because it is out of range, or due to wireless
     interference.
     */
    SCPDisconnectReasonBluetoothSignalLost,
} NS_SWIFT_NAME(DisconnectReason);

NS_ASSUME_NONNULL_END
