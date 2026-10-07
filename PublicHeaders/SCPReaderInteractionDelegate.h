//
//  SCPReaderInteractionDelegate.h
//  StripeTerminal
//
//  Created by Stripe on 8/17/2026.
//  Copyright © 2026 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPReaderDelegate.h>
#import <StripeTerminal/SCPReaderDisplayMessage.h>
#import <StripeTerminal/SCPReaderInputOptions.h>

@class SCPCancelable;
@class SCPReader;
@class SCPReaderSoftwareUpdate;

NS_ASSUME_NONNULL_BEGIN

/**
 A base delegate for interactions shared by mobile and Tap to Pay readers.

 Don't implement this protocol directly. Instead, implement `SCPMobileReaderDelegate`
 or `SCPTapToPayReaderDelegate` for the reader types your integration supports.
 */
NS_SWIFT_NAME(ReaderInteractionDelegate)
@protocol SCPReaderInteractionDelegate <SCPReaderDelegate>

/**
 The reader has started installing a software update.

 The installation lifecycle callbacks cover both Mobile Reader software
 updates and mandatory Tap to Pay configuration installation during
 `-[SCPTerminal connectReader:completion:]`.

 @param reader The originating reader.
 @param update The `SCPReaderSoftwareUpdate` with a `durationEstimate` that can be
 used to communicate how long the update is expected to take.
 @param cancelable A cancelable that can be used to cancel the installation when
 cancellation is supported.
 */
- (void)reader:(SCPReader *)reader
    didStartInstallingUpdate:(SCPReaderSoftwareUpdate *)update
                  cancelable:(nullable SCPCancelable *)cancelable
    NS_SWIFT_NAME(reader(_:didStartInstallingUpdate:cancelable:));

/**
 The reader reported progress on a software update.

 @param reader The originating reader.
 @param progress An estimate of the progress of the software update in the range
 `[0.0, 1.0]`.
 */
- (void)reader:(SCPReader *)reader
    didReportReaderSoftwareUpdateProgress:(float)progress
    NS_SWIFT_NAME(reader(_:didReportReaderSoftwareUpdateProgress:));

/**
 The reader has finished installing an update.

 @param reader The originating reader.
 @param update The update that was being installed, if any.
 @param error The error that prevented installation, or `nil` if the installation
 succeeded.
 */
- (void)reader:(SCPReader *)reader
    didFinishInstallingUpdate:(nullable SCPReaderSoftwareUpdate *)update
                        error:(nullable NSError *)error
    NS_SWIFT_NAME(reader(_:didFinishInstallingUpdate:error:));

/**
 This method is called when the reader begins waiting for input. Your app should
 prompt the customer to present one of the given payment methods.

 @param reader The originating reader.
 @param inputOptions The armed input options on the reader.
 */
- (void)reader:(SCPReader *)reader
    didRequestReaderInput:(SCPReaderInputOptions)inputOptions
    NS_SWIFT_NAME(reader(_:didRequestReaderInput:));

/**
 This method is called when the reader requests that a prompt be displayed in
 your app.

 @param reader The originating reader.
 @param displayMessage The message to display to the user.
 */
- (void)reader:(SCPReader *)reader
    didRequestReaderDisplayMessage:(SCPReaderDisplayMessage)displayMessage
    NS_SWIFT_NAME(reader(_:didRequestReaderDisplayMessage:));

@end

NS_ASSUME_NONNULL_END
