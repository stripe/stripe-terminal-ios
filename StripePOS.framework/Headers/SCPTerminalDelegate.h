//
//  SCPTerminalDelegate.h
//  StripePOS
//
//  Created by Ben Guo on 11/1/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"
#import "SCPTerminal.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle updates from an SCPTerminal instance.
 You must pass a SCPTerminalDelegate when initializing SCPTerminal.
 */
@protocol SCPTerminalDelegate <NSObject>

@optional
/**
 The reader's battery is low.

 @param terminal    The originating terminal.
 */
- (void)terminalDidReportLowBatteryWarning:(SCPTerminal *)terminal;

/**
 The terminal's connection status changed.

 @param terminal    The originating terminal.
 @param status      The terminal's new connection status.
 */
- (void)terminal:(SCPTerminal *)terminal didChangeConnectionStatus:(SCPConnectionStatus)status;

/**
 The terminal's payment status changed.

 @param terminal    The originating terminal.
 @param status      The terminal's new payment status.
 */
- (void)terminal:(SCPTerminal *)terminal didChangePaymentStatus:(SCPPaymentStatus)status;

/**
 The terminal emitted a logline. You may use this optional callback to incorporate loglines
 from the Stripe POS SDK into your own telemetry tooling.

 @param terminal    The originating terminal.
 @param logline     The logline.
 */
- (void)terminal:(SCPTerminal *)terminal didEmitLogline:(NSString *)logline;

@end

NS_ASSUME_NONNULL_END
