//
//  SCPCollectInputsParameters.h
//  StripeTerminal
//
//  Created by Stephen Lee on 2023-10-20.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPInput.h>

NS_ASSUME_NONNULL_BEGIN

/**
Contains information about the inputs to collect from the reader
 */
NS_SWIFT_NAME(CollectInputsParameters)
@interface SCPCollectInputsParameters : NSObject

/**
Inputs to collect
 */
@property (nonatomic, readonly, copy) NSArray<SCPInput *> *inputs;

/**
 Use `SCPCollectInputsParametersBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPCollectInputsParametersBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A builder class for `SCPCollectInputsParameters`
*/
NS_SWIFT_NAME(CollectInputsParametersBuilder)
@interface SCPCollectInputsParametersBuilder : SCPBuilder <SCPCollectInputsParameters *>

/**
 Initializes a new instance of the `SCPCollectInputsParametersBuilder` class with the provided
 inputs.
 */
- (instancetype)initWithInputs:(NSArray<SCPInput *> *)inputs;

/**
@see `SCPCollectInputsParameters.inputs`
 */
- (SCPCollectInputsParametersBuilder *)setInputs:(NSArray<SCPInput *> *)inputs;

/**
 Use `initWithInputs`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithInputs`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
