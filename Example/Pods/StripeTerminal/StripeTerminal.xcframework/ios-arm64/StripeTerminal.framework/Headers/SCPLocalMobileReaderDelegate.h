//
//  SCPLocalMobileReaderDelegate.h
//  StripeTerminal
//
//  Created by Martin Mroz on 2/16/22.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

@class SCPReader;
@class SCPReaderSoftwareUpdate;
@class SCPCancelable;

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle a connected local mobile reader's events throughout
 the lifetime of its connection.

 Implementing this delegate is required when connecting to any Local Mobile reader.

 The provided delegate must be retained by your application until the reader disconnects.
 */
NS_SWIFT_NAME(LocalMobileReaderDelegate)
@protocol SCPLocalMobileReaderDelegate <NSObject>

/**
 The SDK is reporting that the reader has started installing a software update.

 There are two scenarios when a reader's software update can be installed. Some
 updates must be installed immediately, and may be being installed automatically
 during `connectReader:`.

 Required updates will only start installing during `connectReader:`. Once your app's
 `connectReader:` completion is called, `didStartInstallingUpdate:` will only fire
 from requests to install via `installUpdate:`.

 Note that required updates are critical for the reader to have the
 correct configuration and prevent receiving `SCPErrorUnsupportedReaderVersion`.

 @param reader The originating reader.
 @param update The `SCPReaderSoftwareUpdate` with an `estimatedUpdateTime` that
   can be used to communicate how long the update is expected to take.
 @param cancelable  This cancelable is provided to cancel the
   installation if needed. Canceling a required update will result in a failed
   connect with error `SCPErrorUnsupportedReaderVersion`. Some updates will
   have a nil cancelable because these updates can not be canceled.
 */
- (void)localMobileReader:(SCPReader *)reader
 didStartInstallingUpdate:(SCPReaderSoftwareUpdate *)update
               cancelable:(nullable SCPCancelable *)cancelable
    NS_SWIFT_NAME(localMobileReader(_:didStartInstallingUpdate:cancelable:));

/**
 The reader reported progress on a software update.

 @param reader The originating reader.
 @param progress An estimate of the progress of the software update (in the range [0.0, 1.0]).
 */
- (void)localMobileReader:(SCPReader *)reader
didReportReaderSoftwareUpdateProgress:(float)progress
    NS_SWIFT_NAME(localMobileReader(_:didReportReaderSoftwareUpdateProgress:));

/**
 The reader is reporting that an installation has finished. If the install was
 successful, error will be nil.

 @param reader The originating reader.
 @param update The update that was being installed, if any.
 @param error If the installed failed, this will describe the error preventing install.
 */
- (void)localMobileReader:(SCPReader *)reader
didFinishInstallingUpdate:(nullable SCPReaderSoftwareUpdate *)update
                    error:(nullable NSError *)error
    NS_SWIFT_NAME(localMobileReader(_:didFinishInstallingUpdate:error:));

@end

NS_ASSUME_NONNULL_END
