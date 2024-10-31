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
#import <StripeTerminal/SCPReaderDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Base class for all ConnectionConfiguration subclasses.

 Your app should use the subclasses depending on the reader
 type and connection method being used.
 */
NS_SWIFT_NAME(ConnectionConfiguration)
@interface SCPConnectionConfiguration : NSObject

/**
 The ReaderDelegate for this connection. Must be set to the appropriate type using the subclasses builder.
 */
@property (nonatomic, readonly, weak) id<SCPReaderDelegate> delegate;

/**
 You cannot directly instantiate this class.

 Use BluetoothConnectionConfiguration, TapToPayConnectionConfiguration, or
 InternetConnectionConfiguration depending on the reader
 you're connecting to.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.

 Use BluetoothConnectionConfiguration, TapToPayConnectionConfiguration, or
 InternetConnectionConfiguration depending on the reader
 you're connecting to.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
