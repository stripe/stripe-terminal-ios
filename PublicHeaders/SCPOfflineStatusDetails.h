//
//  SCPOfflineStatusDetails.h
//  StripeTerminal
//
//  Created by Bill Finn on 2023-08-18.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPNetworkStatus.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains status and statistics relevant to operating offline.
 */
NS_SWIFT_NAME(OfflineStatusDetails)
@interface SCPOfflineStatusDetails : NSObject

/**
 Returns the number of processed payment intents stored locally as an offline record to be forwarded when
 the iOS device goes back online.

 This count will be nil after calling `clearCachedCredentials`.
 */
@property (nonatomic, nullable, readonly, strong) NSNumber *paymentsCount;

/**
 Returns the total amount of processed offline payment intents stored locally. The key
 is the three-letter ISO currency code in lowercase. The amount is provided in the currency's
 smallest unit and matches the unit used when creating payment intents.

 example:
 ["usd": 1980,
  "cad": 2003]

 Use this in your application to be able to enforce custom limits on the total amount
 of payments to be stored offline. To prevent future payments from being created
 while offline, you can use the `CreateConfiguration`s `offlineBehavior` property when
 creating payment intents.

 This will reset to an empty dictionary after calling `clearCachedCredentials`.
 */
@property (nonatomic, readonly, strong) NSDictionary<NSString *, NSNumber *> *paymentAmountsByCurrency;

/**
 The current network status. At initialization, the network status has a value
 of `SCPNetworkStatusUnknown`.
 */
@property (nonatomic, readonly) SCPNetworkStatus networkStatus;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
