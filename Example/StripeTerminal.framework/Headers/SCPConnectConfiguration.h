//
//  SCPConnectConfiguration.h
//  StripeTerminal
//
//  Created by Catriona Scott on 8/6/19.
//  Copyright © 2019 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Configuration for connecting to readers.
 */

NS_SWIFT_NAME(ConnectConfiguration)
@interface SCPConnectConfiguration : NSObject

/**
 If set to true, connection will automatically error if the reader is already
 connected to a device and collecting payment. When set to false this will allow
 you to connect to a reader already connected to another device. This will
 auto-disconnect the reader from the other device when it attempts to collect
 payment. Note that is only applicable for VerifoneP400 reader.

 @see https://stripe.com/docs/terminal/ios-verifone-p400?#connecting-verifone
 */
@property (nonatomic, readonly) BOOL failIfInUse;

/**
 Initalize your connect options with fail if in use.
 */
- (instancetype)initWithFailIfInUse:(BOOL)failIfInUse;

@end

NS_ASSUME_NONNULL_END
