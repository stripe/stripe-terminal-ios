//
//  SCPSimulatedCard.h
//  StripeTerminal
//
//  Created by Catriona Scott on 2/17/21.
//  Copyright © 2021 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPSimulatedCardType.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Simulated Card objects can be used with the shared `SCPSimulatorConfiguration`
 to simulate different card brand and error cases with a simulated Reader.

 Simulated Card objects are backed by one of Stripe's test card numbers, which
 are hardcoded to provide certain behavior within Stripe's backend. The
 Terminal SDK provides an `SCPSimulatedCardType` enum that automatically maps
 to the card numbers for convenience.

 @see https://stripe.com/docs/terminal/testing#simulated-test-cards
 */
NS_SWIFT_NAME(SimulatedCard)
@interface SCPSimulatedCard : NSObject

/**
 Create a Simulated Card object with a given simulated card type.

 @see `SCPSimulatedCardType`
 */
- (instancetype)initWithType:(SCPSimulatedCardType)type;

/**
 Create a Simulated Card object with a raw card number. This initializer is
 made available in case Stripe creates a new test card number without creating a
 corresponding `SCPSimulatedCardType`. The card number entered here must
 be in the [list of test card numbers](https://stripe.com/docs/terminal/testing#simulated-test-cards).

 @see https://stripe.com/docs/terminal/testing#simulated-test-cards
 */
- (instancetype)initWithTestCardNumber:(NSString *)testCardNumber;

/**
 You cannot instantiate this class without specifying a type or testcard number.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
    Returns true if the card is online pin enabled.
 */
- (BOOL)isOnlinePin;

/**
    Returns true if the card is offline pin enabled.
 */
- (BOOL)isOfflinePin;

/**
 You cannot instantiate this class without specifying a type or testcard number.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
