//
//  SCPNetworks.h
//  StripeTerminal
//
//  Created by Brian Cooke on 8/29/22.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Contains information about card networks that can be used to process the payment.

 @see https://stripe.com/docs/api/payment_methods/object#payment_method_object-card-networks-available
 */
@interface SCPNetworks : NSObject <SCPJSONDecodable>

/**
 All available networks for the card.

 Contains SCPCardBrand's represented as NSNumber.
 */
@property (nonatomic, copy, readonly, nullable) NSArray<NSNumber *> *available;

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
