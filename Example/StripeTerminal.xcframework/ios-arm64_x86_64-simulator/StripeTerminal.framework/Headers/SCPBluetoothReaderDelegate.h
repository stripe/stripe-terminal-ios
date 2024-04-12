//
//  SCPBluetoothReaderDelegate.h
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
#import <StripeTerminal/SCPDisconnectReason.h>
#import <StripeTerminal/SCPReaderDisplayMessage.h>
#import <StripeTerminal/SCPReaderEvent.h>
#import <StripeTerminal/SCPReaderInputOptions.h>


@class SCPReader;
@class SCPReaderSoftwareUpdate;
@class SCPCancelable;

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle a connected Bluetooth reader's events throughout
 the lifetime of its connection.

 Implementing this delegate is required when connecting to any Bluetooth connected
 reader, such as the Stripe M2, BBPOS Chipper 2X BT, and the BBPOS WisePad 3.

 The provided delegate must be retained by your application until the reader disconnects.
 */
NS_SWIFT_NAME(BluetoothReaderDelegate)
@protocol SCPBluetoothReaderDelegate
    <NSObject>

/**
 The SDK is reporting that an update is available for the reader.
 This update should be installed at the earliest convenience via
 `-[SCPTerminal installUpdate:]`

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

/**
 The SDK is reporting that the reader has started installing a software update.

 There are two scenarios when a reader's software update can be installed. Some
 updates must be installed immediately, and may be being installed automatically
 during `connectReader:`. Other updates can be delayed, and will be installed
 when your integration calls `installAvailableUpdate`.

 Required updates will only start installing during `connectReader:`. Once your app's
 `connectReader:` completion is called, `didStartInstallingUpdate:` will only fire
 from requests to install via `installUpdate:`.

 Note that required updates are critical for the reader to have the
 correct configuration and prevent receiving `SCPErrorUnsupportedReaderVersion`.
 Updates that aren't yet required are reported by `reader:didReportUpdateAvailable:`.

 @see https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt#updating-reader-software

 @param reader      The originating reader.
 @param update      The `SCPReaderSoftwareUpdate` with an `estimatedUpdateTime` that
 can be used to communicate how long the update is expected to take.
 @param cancelable  This cancelable is provided to cancel the
 installation if needed. Canceling a required update will result in a failed
 connect with error `SCPErrorUnsupportedReaderVersion`. Incremental only updates will
 have a nil cancelable because these updates can not be canceled.
 */
- (void)reader:(SCPReader *)reader didStartInstallingUpdate:(SCPReaderSoftwareUpdate *)update cancelable:(nullable SCPCancelable *)cancelable;

/**
 The reader reported progress on a software update.

 @param reader              The originating reader.
 @param progress            An estimate of the progress of the software update
 (in the range [0, 1]).
 */
- (void)reader:(SCPReader *)reader didReportReaderSoftwareUpdateProgress:(float)progress NS_SWIFT_NAME(reader(_:didReportReaderSoftwareUpdateProgress:));

/**
 The reader is reporting that an installation has finished. If the install was
 successful, error will be nil.

 @param reader      The originating reader.
 @param update      The update that was being installed, if any. Calls to `installAvailableUpdate`
                    when no update is available will still report didFinishInstallingUpdate, but with
                    a nil update.
 @param error       If the installed failed, this will describe the error preventing install.
 */
- (void)reader:(SCPReader *)reader didFinishInstallingUpdate:(nullable SCPReaderSoftwareUpdate *)update error:(nullable NSError *)error NS_SWIFT_NAME(reader(_:didFinishInstallingUpdate:error:));

/**
 This method is called when the reader begins waiting for input. Your app
 should prompt the customer to present a payment method using one of the given input
 options. If the reader emits a prompt, the `didRequestReaderDisplayMessage` method
 will be called.

 Use `- [SCPTerminal stringFromReaderInputOptions]` to get a user facing string for the input
 options.

 @param reader            The originating reader.
 @param inputOptions      The armed input options on the reader.
 */
- (void)reader:(SCPReader *)reader didRequestReaderInput:(SCPReaderInputOptions)inputOptions NS_SWIFT_NAME(reader(_:didRequestReaderInput:));

/**
 This method is called to request that a prompt be displayed in your app.
 For example, if the prompt is `SwipeCard`, your app should instruct the
 user to present the card again by swiping it.

 Use `- [SCPTerminal stringFromReaderDisplayMessage]` to get a user facing string for the prompt.

 @see SCPReaderDisplayMessage

 @param reader              The originating reader.
 @param displayMessage      The message to display to the user.
 */
- (void)reader:(SCPReader *)reader didRequestReaderDisplayMessage:(SCPReaderDisplayMessage)displayMessage NS_SWIFT_NAME(reader(_:didRequestReaderDisplayMessage:));

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

/**
  Optional method that is called when the reader has disconnected from the SDK and includes the
  reason for the disconnect.

  @note The `SCPTerminalDelegate`'s `terminal:didReportUnexpectedReaderDisconnect:` method will still be called.

  @param reader      The originating reader.
  @param reason      The reason for the disconnect. @see `SCPDisconnectReason`
 */
- (void)reader:(SCPReader *)reader didDisconnect:(SCPDisconnectReason)reason NS_SWIFT_NAME(reader(_:didDisconnect:));

@end

NS_ASSUME_NONNULL_END
