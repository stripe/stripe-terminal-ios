//
//  SCPSimulatorConfiguration.h
//  StripeTerminal
//
//  Created by Brian Cooke on 5/29/20.
//  Copyright © 2020 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPSimulateReaderUpdate.h>
#import <StripeTerminal/SCPSimulatedCard.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Simulator specific configurations you can set to test your integration's
 behavior in different scenarios. We recommend changing these properties during
 testing to ensure your app works as expected for different reader updates
 and for different presented cards.

 Do not create new instances of this class. Instead, set the properties via
 `SCPTerminal.shared.simulatorConfiguration`.
 */
NS_SWIFT_NAME(SimulatorConfiguration)
@interface SCPSimulatorConfiguration : NSObject

/**
 Set this to different values of the `SCPSimulateReaderUpdate` enum to
 test your integration with different reader software update scenarios.

 @note This is only valid for simulated Bluetooth readers.
 */
@property (nonatomic, assign) SCPSimulateReaderUpdate availableReaderUpdate;

/**
 Create a SCPSimulatedCard and set it on the shared configuration object to
 test your integration with different card brands and in error scenarios.

 @note Simulated Internet reader refunds do not use the specified simulated card.

 @see https://stripe.com/docs/terminal/testing#simulated-test-cards
 */
@property (nonatomic, readwrite) SCPSimulatedCard *simulatedCard;

/**
 Set this to simulate a Terminal configuration object with this fixed tip
 amount for all currencies.
 */
@property (nonatomic, readwrite, nullable) NSNumber *simulatedTipAmount;

/**
 You cannot directly instantiate this class.
 Set exposed properties via `SCPTerminal.shared.simulatorConfiguration`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 Set exposed properties via `SCPTerminal.shared.simulatorConfiguration`
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
