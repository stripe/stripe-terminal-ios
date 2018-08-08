//
//  SCPDiscoveryDelegate.h
//  StripePOS
//
//  Created by Ben Guo on 11/1/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"
#import "SCPTerminal.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle events when connecting to a reader. You
 must pass a `SCPDiscoveryDelegate` when calling `connect`.
 */
@protocol SCPDiscoveryDelegate <NSObject>

/**
 This method will be called repeatedly until:
 - an error occurs
 - `discover` is canceled
 - `connect` is called with a discovered reader

 Your app should either display an updating list of discovered readers, or
 automatically select a previously saved reader. Once a selection has been made,
 call `SCPTerminal`'s `connect` method to begin connecting to the reader.

 @param terminal        The originating SCPTerminal.
 @param readers         The discovered readers.
 */
- (void)terminal:(SCPTerminal *)terminal didUpdateDiscoveryResults:(NSArray<SCPReader *>*)readers;

@end

NS_ASSUME_NONNULL_END
