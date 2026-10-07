//
//  SCPMobileReaderDelegate.h
//  StripeTerminal
//
//  Created by Brian Cooke on 5/26/2020.
//  Copyright © 2020 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBatteryStatus.h>
#import <StripeTerminal/SCPReaderEvent.h>
#import <StripeTerminal/SCPReaderInteractionDelegate.h>

@class SCPReader;
@class SCPReaderSoftwareUpdate;

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle a connected Bluetooth reader's events throughout
 the lifetime of its connection.

 Implementing this delegate is required when connecting to any Bluetooth connected
 reader, such as the Stripe M2, BBPOS Chipper 2X BT, and the BBPOS WisePad 3.

 The provided delegate must be retained by your application until the reader disconnects.
 */
NS_SWIFT_NAME(MobileReaderDelegate)
@protocol SCPMobileReaderDelegate <SCPReaderInteractionDelegate>

/**
 The SDK is reporting a deferred software update that is available for the
 Mobile Reader. This callback is only used for Mobile Reader updates that an
 integration can install later by calling `-[SCPTerminal installUpdate:]`.

 Tap to Pay readers don't report available optional updates. Mandatory Tap to
 Pay configuration installation during connection is reported through the
 installation lifecycle callbacks on `SCPReaderInteractionDelegate`.

 Check the `SCPReaderSoftwareUpdate.requiredAt` field to see when this update
 will be a required update. Required updates are installed immediately upon connection.

 This delegate method is most likely to be called right after `connectReader:` but
 applications that stay connected to the reader for long periods of time should expect
 this method to be called any time the reader is not busy performing a transaction.

 @see https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt#updating-reader-software

 @param reader      The originating reader.
 @param update      An `SCPReaderSoftwareUpdate` object representing the update to be installed.
 */
- (void)reader:(SCPReader *)reader didReportAvailableUpdate:(SCPReaderSoftwareUpdate *)update;

@optional

/**
 The SDK reported an event from the reader (e.g. a card was inserted).

 @param reader      The originating reader.
 @param event       The reader event.
 @param info        Additional info associated with the event, or nil.
 */
- (void)reader:(SCPReader *)reader didReportReaderEvent:(SCPReaderEvent)event info:(nullable NSDictionary *)info NS_SWIFT_NAME(reader(_:didReportReaderEvent:info:));

/**
 The SDK reported the reader's battery level or charging state has changed.

 @see SCPBatteryStatus

 @param reader       The originating reader.
 @param batteryLevel The new battery level of the reader, a float from 0.0 to 1.0
 @param status       The classification of the battery level. @see `SCPBatteryStatus`
 @param isCharging   YES if the reader is plugged in and charging.
 */
- (void)reader:(SCPReader *)reader didReportBatteryLevel:(float)batteryLevel status:(SCPBatteryStatus)status isCharging:(BOOL)isCharging NS_SWIFT_NAME(reader(_:didReportBatteryLevel:status:isCharging:));

/**
 This method is called when the SDK's currently connected reader has a low battery.

 @param reader      The originating reader.
 */
- (void)readerDidReportLowBatteryWarning:(SCPReader *)reader NS_SWIFT_NAME(readerDidReportLowBatteryWarning(_:));

@end

NS_ASSUME_NONNULL_END
