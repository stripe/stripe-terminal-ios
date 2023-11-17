//
//  SCPWallet.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2023-10-11.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

/**
 If this payment is part of a card wallet, this contains the details of the card wallet.
 */
@interface SCPWallet : NSObject <SCPJSONDecodable>

/**
 The type of the card wallet.
 */
@property (nonatomic, nullable, readonly) NSString *type;

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
