//
//  SCPDiscoveryDelegate.h
//  StripeTerminal
//
//  Created by Ben Guo on 11/1/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"
#import "SCPTerminal.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle a continually updating list
 of discovered readers. You must pass an `SCPDiscoveryDelegate`
 when calling `-[SCPTerminal discoverReaders:delegate:completion:]`.

 @see https://stripe.com/docs/terminal/readers/connecting
 */
NS_SWIFT_NAME(DiscoveryDelegate)
@protocol SCPDiscoveryDelegate <NSObject>

/**
 This method will be called repeatedly until:
 - an error occurs
 - `-[SCPTerminal discoverReaders:delegate:completion:]` is canceled via the
 `SCPCancelable` that it returned.
 - `-[SCPTerminal connectReader:completion:]` is called with a discovered reader

 You should *not* cache the `SCPReader` objects in the readers array. In other
 words, after calling `connectReader:` with a discovered reader, you should not
 attempt to cache and re-use the `Reader` object. The connectivity information
 associated with the discovered `Reader` object will become stale. If no readers
 have been found `didUpdateDiscoveredReaders` will be called with an empty
 array.

 Bluetooth Scan
 --------------

 When discovering a reader using this method, this `didUpdateDiscoveredReaders`
 delegate method will be called multiple times as the Bluetooth scan
 proceeds.

 Your app should display an updating list of discovered readers if
 your user is connecting to a reader for the first time.

 Otherwise, you may automatically select a previously saved reader.
 Once a selection has been made, call the `connectReader` method to begin
 connecting to the reader.

 Bluetooth Proximity
 -------------------

 When discovering a reader using this method, this `didUpdateDiscoveredReaders`
 delegate method will be called twice. It will be called for the first time
 when the reader is initially discovered. The reader's LEDs will begin
 flashing. After a short delay, `didUpdateDiscoveredReaders` will be called
 a second time with an updated reader object, populated with additional
 info about the device, like its battery level.

 == Internet ==

 When discovering a reader using this method, the `didUpdateDiscoveredReaders`
 delegate method will only be called once. Both readers online and offline will
 be sent to `didUpdateDiscoveredReaders`. Only an online reader can be connected
 to, so it will be up to you to check its network status. If you have not
 registered any readers to your account `didUpdateDiscoveredReaders` will be
 called with an empty array. Note that this discovery method is currently only
 compatable with VerifoneP400.

 @param terminal        The originating SCPTerminal.
 @param readers         The discovered readers.
 */
- (void)terminal:(SCPTerminal *)terminal didUpdateDiscoveredReaders:(NSArray<SCPReader *>*)readers NS_SWIFT_NAME(terminal(_:didUpdateDiscoveredReaders:));

@end

NS_ASSUME_NONNULL_END
