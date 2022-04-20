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
 Base class for BluetoothConnectionConfiguration and
 InternetConnectionConfiguration.

 Your app should use the subclasses depending on the reader
 type being connected to.
 */
NS_SWIFT_NAME(ConnectionConfiguration)
@interface SCPConnectionConfiguration : NSObject

/**
 You cannot directly instantiate this class.

 Use BluetoothConnectionConfiguration or
 InternetConnectionConfiguration depending on the reader
 you're connecting to.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.

 Use BluetoothConnectionConfiguration or
 InternetConnectionConfiguration depending on the reader
 you're connecting to.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
