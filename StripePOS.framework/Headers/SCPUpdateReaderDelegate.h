//
//  SCPUpdateReaderDelegate.h
//  StripePOS
//
//  Created by Ben Guo on 6/13/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"
#import "SCPTerminal.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle events when updating a reader. You must
 pass a `SCPUpdateReaderDelegate` when calling `updateReader`.
 */
@protocol SCPUpdateReaderDelegate <NSObject>

/**
 An update is available to be installed on the connected reader. You should
 notify your app's user that an update is available, and ask if they want to
 proceed with the update.

 During an update, the reader becomes unusable. You may use the
 `terminal:didReportReaderUpdateProgress:` delegate method to follow the
 progress of the update. After the update completes, the
 `terminal:didCompleteReaderUpdate:` method is called.

 @param terminal        The originating terminal.

 @param readerUpdate    An object containing information about the update.

 @param installUpdate   Call this block with a boolean value indicating whether
 you want to proceed with the update. Calling `installUpdate(true)` starts the
 update process.
 */
- (void)terminal:(SCPTerminal *)terminal
readerUpdateAvailable:(SCPReaderUpdate *)readerUpdate
   installUpdate:(SCPBoolCompletionBlock)installUpdate;

/**
 The terminal reported progress on a reader update.

 @param terminal            The originating terminal.
 @param updateProgress      An estimate of the progress of the update (in the range [0, 1]).
 */
- (void)terminal:(SCPTerminal *)terminal
didReportReaderUpdateProgress:(float)updateProgress;

/**
 Updating the reader completed. If `error` is nil, the update was installed
 successfully.

 @param terminal    The originating terminal.
 @param error       An error describing why the update failed, or nil if the
 update was installed successfully.
 */
- (void)terminal:(SCPTerminal *)terminal
didCompleteReaderUpdate:(nullable NSError *)error;

@end

NS_ASSUME_NONNULL_END
