//
//  SCPUpdateReaderSoftwareDelegate.h
//  StripeTerminal
//
//  Created by Ben Guo on 6/13/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"
#import "SCPTerminal.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle updates when checking for and installing
 reader software updates.
 
 You must implement the ability to update your reader's software in your app.
 Though we expect required software updates to be very rare, by using Stripe
 Terminal, you are obligated to include this functionality.
 */
NS_SWIFT_NAME(ReaderSoftwareUpdateDelegate)
@protocol SCPReaderSoftwareUpdateDelegate <NSObject>

/**
 A software update is available to be installed on the connected reader
 hardware. You should notify your app's user that an update is available, and
 ask if they want to proceed with the update.

 If an update is initiated, the reader will become unresponsive until the
 update is complete. In some cases, you will need to restart the reader at the
 end of the update.

 You should use the `didReportReaderSoftwareUpdateProgress` delegate
 method to signal the progress of the update to your user. After the update
 completes, the `didCompleteReaderSoftwareUpdate` delegate method will be called
 to indicate whether the update was successfully completed.

 @param terminal        The originating terminal.

 @param update          An object containing information about the available
 software update.

 @param installUpdate   Call this block with a boolean value indicating whether
 you want to proceed with the update. Calling `installUpdate(true)` begins
 installing the udpate.
 */
- (void)terminal:(SCPTerminal *)terminal
readerSoftwareUpdateAvailable:(SCPReaderSoftwareUpdate *)update
   installUpdate:(SCPInstallUpdateBlock)installUpdate NS_SWIFT_NAME(terminal(_:readerSoftwareUpdateAvailable:installUpdate:));

/**
 The terminal reported progress on a reader software update.

 @param terminal            The originating terminal.
 @param progress            An estimate of the progress of the software update
 (in the range [0, 1]).
 */
- (void)terminal:(SCPTerminal *)terminal
didReportReaderSoftwareUpdateProgress:(float)progress NS_SWIFT_NAME(terminal(_:didReportReaderSoftwareUpdateProgress:));

/**
 Updating the reader software completed. If `error` is nil, the software update
 was installed successfully.

 @param terminal    The originating terminal.
 @param error       An error describing why the software update failed, or nil
 if the update was installed successfully.
 */
- (void)terminal:(SCPTerminal *)terminal
didCompleteReaderSoftwareUpdate:(nullable NSError *)error NS_SWIFT_NAME(terminal(_:didCompleteReaderSoftwareUpdate:));

@end

/// Deprecated: UpdateReaderSoftwareDelegate has been renamed to ReaderSoftwareUpdateDelegate
NS_SWIFT_NAME(UpdateReaderSoftwareDelegate)
__attribute__((deprecated("UpdateReaderSoftwareDelegate has been renamed to ReaderSoftwareUpdateDelegate", "SCPReaderSoftwareUpdateDelegate")))
@protocol SCPUpdateReaderSoftwareDelegate <SCPReaderSoftwareUpdateDelegate>
@end

NS_ASSUME_NONNULL_END
