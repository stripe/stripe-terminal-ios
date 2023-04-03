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

#import <StripeTerminal/SCPReaderDisplayMessage.h>
#import <StripeTerminal/SCPReaderInputOptions.h>


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
@protocol SCPLocalMobileReaderDelegate
    <NSObject>

/**
 The reader has started installing a software update.

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
 @param progress An estimate of the progress of the software update
   (in the range [0.0, 1.0]).
 */
- (void)localMobileReader:(SCPReader *)reader
    didReportReaderSoftwareUpdateProgress:(float)progress
    NS_SWIFT_NAME(localMobileReader(_:didReportReaderSoftwareUpdateProgress:));

/**
 The reader has finished installing an update.

 @param reader The originating reader.
 @param update The update that was being installed, if any.
 @param error If the installed failed, this will describe the error
    preventing install. If it succeeded, the error will be `nil`.
 */
- (void)localMobileReader:(SCPReader *)reader
    didFinishInstallingUpdate:(nullable SCPReaderSoftwareUpdate *)update
                        error:(nullable NSError *)error
    NS_SWIFT_NAME(localMobileReader(_:didFinishInstallingUpdate:error:));

/**
 This method is called when the reader begins waiting for input.
 Use `- [SCPTerminal stringFromReaderInputOptions:]` to get a  user facing string
 for the input options.

 @param reader The originating reader.
 @param inputOptions The armed input options on the reader.
 */
- (void)localMobileReader:(SCPReader *)reader
    didRequestReaderInput:(SCPReaderInputOptions)inputOptions
    NS_SWIFT_NAME(localMobileReader(_:didRequestReaderInput:));

/**
 This method is called to request that a prompt be displayed in your app.
 Use `- [SCPTerminal stringFromReaderDisplayMessage:]` to get a user
 facing string for the prompt.

 @see SCPReaderDisplayMessage
 @param reader The originating reader.
 @param displayMessage The message to display to the user.
 */
- (void)localMobileReader:(SCPReader *)reader
    didRequestReaderDisplayMessage:(SCPReaderDisplayMessage)displayMessage
    NS_SWIFT_NAME(localMobileReader(_:didRequestReaderDisplayMessage:));

@optional

/**
 The reader is reporting that, as part of preparing to accept payments,
 the terms of service has been accepted.

 @param reader The originating reader.
 */
- (void)localMobileReaderDidAcceptTermsOfService:(SCPReader *)reader
    NS_SWIFT_NAME(localMobileReaderDidAcceptTermsOfService(_:));

@end

NS_ASSUME_NONNULL_END
