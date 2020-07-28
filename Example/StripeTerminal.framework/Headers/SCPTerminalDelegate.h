//
//  SCPTerminalDelegate.h
//  StripeTerminal
//
//  Created by Ben Guo on 11/1/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"
#import "SCPReaderEvent.h"
#import "SCPTerminal.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle updates from the Stripe Terminal iOS SDK.
 */
NS_SWIFT_NAME(TerminalDelegate)
@protocol SCPTerminalDelegate <NSObject>

/**
 The reader disconnected unexpectedly (that is, without your app explicitly
 calling `disconnectReader`).

 In your implementation of this method, you should notify your user that
 the reader disconnected. You may also want to call `discoverReaders` to begin
 scanning for readers. Your app can attempt to automatically reconnect to the
 disconnected reader, or display UI for your user to re-connect to a reader.

 You can trigger this call in your app by powering off the connected reader.

 @see https://stripe.com/docs/terminal/readers/connecting

 @param terminal    The originating terminal.
 @param reader      The previously connected reader.
 */
- (void)terminal:(SCPTerminal *)terminal didReportUnexpectedReaderDisconnect:(SCPReader *)reader NS_SWIFT_NAME(terminal(_:didReportUnexpectedReaderDisconnect:));

@optional
/**
 The SDK reported an event from the reader (e.g. a card was inserted).
 
 @note The Verifone P400 has a built-in display which handles displaying card and
 payment events to the customer. The SDK will not call this method while
 connected to the Verifone P400.

 @param terminal    The originating terminal.
 @param event       The reader event.
 @param info        Additional info associated with the event, or nil.
 */
- (void)terminal:(SCPTerminal *)terminal didReportReaderEvent:(SCPReaderEvent)event info:(nullable NSDictionary *)info NS_SWIFT_NAME(terminal(_:didReportReaderEvent:info:));

/**
 This method is called when the SDK's currently connected reader has a low battery.
 
 @note The Verifone P400 is powered by an outlet, and does not use battery power.
 The SDK will not call this method while connected to the Verifone P400.

 @param terminal    The originating terminal.
 */
- (void)terminalDidReportLowBatteryWarning:(SCPTerminal *)terminal NS_SWIFT_NAME(terminalDidReportLowBatteryWarning(_:));

/**
 The currently connected reader's `connectionStatus` changed.

 You should *not* use this method to detect when a reader unexpectedly
 disconnects from your app, as it cannot be used to accurately distinguish
 between expected and unexpected disconnect events. To detect unexpect
 disconnects (e.g. to automatically notify your user), you should instead use
 the `-[SCPTerminalDelegate terminal:didReportUnexpectedReaderDisconnect:]` method.

 @param terminal              The originating terminal.
 @param status                The SDK's new connection status.
 */
- (void)terminal:(SCPTerminal *)terminal didChangeConnectionStatus:(SCPConnectionStatus)status NS_SWIFT_NAME(terminal(_:didChangeConnectionStatus:));

/**
 The currently connected reader's `paymentStatus` changed.

 @param terminal            The originating terminal.
 @param status              The SDK's new payment status.
 */
- (void)terminal:(SCPTerminal *)terminal didChangePaymentStatus:(SCPPaymentStatus)status NS_SWIFT_NAME(terminal(_:didChangePaymentStatus:));

@end

NS_ASSUME_NONNULL_END
