//
//  SCPDiscoveryDelegate.h
//  StripeTerminal
//
//  Created by Ben Guo on 11/1/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"
#import "SCPTerminal.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle a continually updating list
 of discovered readers. You must pass a `SCPDiscoveryDelegate`
 when calling `discoverReaders`.
 */
NS_SWIFT_NAME(DiscoveryDelegate)
@protocol SCPDiscoveryDelegate <NSObject>

/**
 This method will be called repeatedly until:
 - an error occurs
 - `discoverReaders` is canceled
 - `connect` is called with a discovered reader

 Your app should display an updating list of discovered readers if
 your user is connecting to a reader for the first time.
 Otherwise, you may automatically select a previously saved reader.
 Once a selection has been made, call the `connect` method to begin
 connecting to the reader.

 @param terminal        The originating SCPTerminal.
 @param readers         The discovered readers.
 */
- (void)terminal:(SCPTerminal *)terminal didUpdateDiscoveredReaders:(NSArray<SCPReader *>*)readers;

@end

NS_ASSUME_NONNULL_END
