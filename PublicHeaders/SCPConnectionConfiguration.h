//
//  SCPConnectionConfiguration.h
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
 Configuration for connecting to readers. Currently only used to set the
 `failIfInUse` property when connecting to the Verifone P400 reader.
 */

NS_SWIFT_NAME(ConnectionConfiguration)
@interface SCPConnectionConfiguration : NSObject

/**
 If set to true, the connection will automatically error if the reader is already
 connected to a device and collecting payment. When set to false, this will allow
 you to connect to a reader already connected to another device, and will break
 the existing reader-to-SDK connection on the other device when it attempts to
 collect payment.
 
 Note that this parameter is only applicable for the Verifone P400.
 
 If `Terminal.connectReader` is invoked without a `SCPConnectionConfiguration`,
 then `failIfInUse` defaults to `false`.

 @see https://stripe.com/docs/terminal/readers/connecting/verifone-p400#connect-reader-ios
 */
@property (nonatomic, readonly) BOOL failIfInUse;

/**
 Initalize your connect options with fail if in use.
 */
- (instancetype)initWithFailIfInUse:(BOOL)failIfInUse;

@end

NS_ASSUME_NONNULL_END
