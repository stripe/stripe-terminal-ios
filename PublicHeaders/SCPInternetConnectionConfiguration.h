//
//  SCPInternetConnectionConfiguration.h
//  StripeTerminal
//
//  Created by Catriona Scott on 8/6/19.
//  Copyright © 2019 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPConnectionConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This class lets you set options that define internet reader behavior throughout a given
 reader-to-SDK connection session.
 */

NS_SWIFT_NAME(InternetConnectionConfiguration)
@interface SCPInternetConnectionConfiguration : SCPConnectionConfiguration

/**
 When set to true, the connection will automatically error if the reader is already
 connected to a device and collecting payment. When set to false, this will allow
 you to connect to a reader already connected to another device, and will break
 the existing reader-to-SDK connection on the other device when it attempts to
 collect payment.

 If `Terminal.connectReader` is invoked without a `SCPInternetConnectionConfiguration`,
 then `failIfInUse` defaults to `NO`.

 @see https://stripe.com/docs/terminal/readers/connecting/verifone-p400#connect-reader-ios
 */
@property (nonatomic, readonly) BOOL failIfInUse;

/**
 If set to true, the customer will be able to press the red X button on the
 Verifone P400 to cancel a `collectPaymentMethod`, `collectReusableCard`, or
 `collectRefundPaymentMethod` command.

 The property defaults to `NO` if not set.

 @note This behavior is part of a private beta. Setting this property will have
 no effect if you are not part of the allowCustomerCancel beta program.
 */
@property (nonatomic, readonly) BOOL allowCustomerCancel;

/**
 Use `SCPInternetConnectionConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPInternetConnectionConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Use this to build `SCPInternetConnectionConfiguration` objects.
 */
NS_SWIFT_NAME(InternetConnectionConfigurationBuilder)
@interface SCPInternetConnectionConfigurationBuilder : SCPBuilder <SCPInternetConnectionConfiguration *>

/// Set the `failIfInUse` property for the `SCPInternetConnectionConfiguration` object that will be built.
- (SCPInternetConnectionConfigurationBuilder *)setFailIfInUse:(BOOL)failIfInUse;

/// Set the `allowCustomerCancel` property for the `SCPInternetConnectionConfiguration` object that will be built.
- (SCPInternetConnectionConfigurationBuilder *)setAllowCustomerCancel:(BOOL)allowCustomerCancel;

@end

NS_ASSUME_NONNULL_END
