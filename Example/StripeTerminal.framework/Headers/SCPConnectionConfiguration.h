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
 This class lets you set options that define reader behavior throughout a given
 reader-to-SDK connection session. Currently, the options are only applicable
 to the Verifone P400.
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
 then `failIfInUse` defaults to `NO`.

 @see https://stripe.com/docs/terminal/readers/connecting/verifone-p400#connect-reader-ios
 */
@property (nonatomic, readonly) BOOL failIfInUse;

/**
 If set to true, the customer will be able to press the red X button on the
 Verifone P400 to cancel a `collectPaymentMethod`, `collectReusableCard`, or
 `collectRefundPaymentMethod` command.
 
 The property defaults to `NO` if not set.
 
 This behavior is part of a private beta. Setting it will have no effect if you
 are not part of the allowCustomerCancel beta program.
 */
@property (nonatomic, readonly) BOOL allowCustomerCancel;

/**
 Initialize your connect options with all possible properties.
 */
- (instancetype)initWithFailIfInUse:(BOOL)failIfInUse
                allowCustomerCancel:(BOOL)allowCustomerCancel;

/**
 Initalize your connect options with fail if in use.
 */
- (instancetype)initWithFailIfInUse:(BOOL)failIfInUse;

/**
 Initialize your connect options with allowCustomerCancel.
 
 This property is in private beta, and will have no effect if you are not part
 of the allowCustomerCancel beta program.
 */
- (instancetype)initWithAllowCustomerCancel:(BOOL)allowCustomerCancel;

@end

NS_ASSUME_NONNULL_END
