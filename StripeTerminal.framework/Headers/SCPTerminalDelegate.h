//
//  SCPTerminalDelegate.h
//  StripeTerminal
//
//  Created by Ben Guo on 11/1/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"
#import "SCPTerminal.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle updates from a Terminal.
 */
NS_SWIFT_NAME(TerminalDelegate)
@protocol SCPTerminalDelegate <NSObject>

@optional
/**
 The reader's battery is low.

 @param terminal    The originating terminal.
 */
- (void)terminalDidReportLowBatteryWarning:(SCPTerminal *)terminal;

/**
 The terminal disconnected unexpectedly from the reader.

 In your implementation of this method, you may want to notify your user that
 the reader disconnected. You may also call `discover` to begin scanning for
 readers, and attempt to automatically reconnect to the disconnected reader.
 Be sure to either set a timeout or make it possible to cancel calls to
 `discover`.

 @param terminal    The originating terminal.
 @param reader      The previously connected reader.
 */
- (void)terminal:(SCPTerminal *)terminal didDisconnectUnexpectedlyFromReader:(SCPReader *)reader;

/**
 The terminal's connection status changed.

 Note: You should *not* use this method to detect when a reader unexpectedly
 disconnects from your app, as it cannot be used to accurately distinguish
 between expected and unexpected disconnect events.

 To detect unexpect disconnects (e.g. to automatically notify your user),
 you should instead use the `didDisconnectUnexpectedlyFromReader` method.

 @param terminal              The originating terminal.
 @param status                The terminal's new connection status.
 */
- (void)terminal:(SCPTerminal *)terminal didChangeConnectionStatus:(SCPConnectionStatus)status NS_SWIFT_NAME(terminal(_:didChangeConnectionStatus:));

/**
 The terminal's payment status changed.

 @param terminal            The originating terminal.
 @param status              The terminal's new payment status.
 */
- (void)terminal:(SCPTerminal *)terminal didChangePaymentStatus:(SCPPaymentStatus)status NS_SWIFT_NAME(terminal(_:didChangePaymentStatus:));

/**
 The terminal emitted a logline. You may use this optional callback to
 incorporate loglines from the Stripe Terminal SDK into your own telemetry
 tooling.

 @param terminal    The originating terminal.
 @param logline     The logline.
 */
- (void)terminal:(SCPTerminal *)terminal didEmitLogline:(NSString *)logline;

@end

NS_ASSUME_NONNULL_END
