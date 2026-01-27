//
//  SCPTapToPayReaderDelegate.h
//  StripeTerminal
//
//  Created by Martin Mroz on 2/16/22.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <StripeTerminal/SCPBlocks.h>
#import <StripeTerminal/SCPReaderDelegate.h>
#import <StripeTerminal/SCPReaderDisplayMessage.h>
#import <StripeTerminal/SCPReaderInputOptions.h>

@class SCPReader;
@class SCPReaderSoftwareUpdate;
@class SCPCancelable;
@class SCPPaymentIntent;
@class SCPPaymentOption;
@class SCPQrCodeDisplayData;

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle a connected tap to pay reader's events throughout
 the lifetime of its connection.

 Implementing this delegate is required when connecting to any Tap To Pay reader.

 The provided delegate must be retained by your application until the reader disconnects.
 */
NS_SWIFT_NAME(TapToPayReaderDelegate)
@protocol SCPTapToPayReaderDelegate <SCPReaderDelegate>

/**
 The reader has started installing a software update.

 @param reader The originating reader.
 @param update The `SCPReaderSoftwareUpdate` with an `durationEstimate` that
   can be used to communicate how long the update is expected to take.
 @param cancelable  This cancelable is provided to cancel the
   installation if needed. Canceling a required update will result in a failed
   connect with error `SCPErrorUnsupportedReaderVersion`. Some updates will
   have a nil cancelable because these updates can not be canceled.
 */
- (void)tapToPayReader:(SCPReader *)reader
    didStartInstallingUpdate:(SCPReaderSoftwareUpdate *)update
                  cancelable:(nullable SCPCancelable *)cancelable
    NS_SWIFT_NAME(tapToPayReader(_:didStartInstallingUpdate:cancelable:));

/**
 The reader reported progress on a software update.

 @param reader The originating reader.
 @param progress An estimate of the progress of the software update
   (in the range [0.0, 1.0]).
 */
- (void)tapToPayReader:(SCPReader *)reader
    didReportReaderSoftwareUpdateProgress:(float)progress
    NS_SWIFT_NAME(tapToPayReader(_:didReportReaderSoftwareUpdateProgress:));

/**
 The reader has finished installing an update.

 @param reader The originating reader.
 @param update The update that was being installed, if any.
 @param error If the installed failed, this will describe the error
    preventing install. If it succeeded, the error will be `nil`.
 */
- (void)tapToPayReader:(SCPReader *)reader
    didFinishInstallingUpdate:(nullable SCPReaderSoftwareUpdate *)update
                        error:(nullable NSError *)error
    NS_SWIFT_NAME(tapToPayReader(_:didFinishInstallingUpdate:error:));

/**
 This method is called when the reader begins waiting for input.
 Use `- [SCPTerminal stringFromReaderInputOptions:]` to get a  user facing string
 for the input options.

 @param reader The originating reader.
 @param inputOptions The armed input options on the reader.
 */
- (void)tapToPayReader:(SCPReader *)reader
    didRequestReaderInput:(SCPReaderInputOptions)inputOptions
    NS_SWIFT_NAME(tapToPayReader(_:didRequestReaderInput:));

/**
 This method is called to request that a prompt be displayed in your app.
 Use `- [SCPTerminal stringFromReaderDisplayMessage:]` to get a user
 facing string for the prompt.

 @see SCPReaderDisplayMessage
 @param reader The originating reader.
 @param displayMessage The message to display to the user.
 */
- (void)tapToPayReader:(SCPReader *)reader
    didRequestReaderDisplayMessage:(SCPReaderDisplayMessage)displayMessage
    NS_SWIFT_NAME(tapToPayReader(_:didRequestReaderDisplayMessage:));

@optional

/**
 The reader is reporting that, as part of preparing to accept payments,
 the terms of service has been accepted.

 @param reader The originating reader.
 */
- (void)tapToPayReaderDidAcceptTermsOfService:(SCPReader *)reader
    NS_SWIFT_NAME(tapToPayReaderDidAcceptTermsOfService(_:));

/**
 This method is called when payment method selection is required during payment collection.
 Payment collection will block until the completion block is invoked with either the selected
 payment option or a failure.

 @param reader                      The originating reader.
 @param paymentIntent               The PaymentIntent being processed.
 @param availablePaymentOptions     Array of available payment options for the customer to choose from.
 @param completion                  The completion block to invoke with the selected payment option or failure.
 */
- (void)tapToPayReader:(SCPReader *)reader
    didRequestPaymentMethodSelection:(SCPPaymentIntent *)paymentIntent
             availablePaymentOptions:(NSArray<SCPPaymentOption *> *)availablePaymentOptions
                          completion:(SCPPaymentMethodSelectionCompletionBlock)completion
    NS_SWIFT_NAME(tapToPayReader(_:didRequestPaymentMethodSelection:availablePaymentOptions:completion:));

/**
 This method is called when a QR code should be displayed to the user during payment processing.
 Your app should display the QR code to the customer and call the completion block once the QR code
 is successfully shown. Payment confirmation will block until the completion block is invoked.

 @param reader              The originating reader.
 @param paymentIntent       The PaymentIntent being processed.
 @param qrData              The QrCodeDisplayData containing the QR code image URLs and expiration information.
 @param completion          The completion block to invoke when the QR code is successfully displayed or fails.
 */
- (void)tapToPayReader:(SCPReader *)reader
    didRequestQrCodeDisplay:(SCPPaymentIntent *)paymentIntent
                     qrData:(SCPQrCodeDisplayData *)qrData
                 completion:(SCPQrCodeDisplayCompletionBlock)completion
    NS_SWIFT_NAME(tapToPayReader(_:didRequestQrCodeDisplay:qrData:completion:));

@end

NS_ASSUME_NONNULL_END
