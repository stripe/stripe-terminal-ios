//
//  SCPConfirmSetupIntentError.h
//  StripeTerminal
//
//  Created by James Little on 1/18/21.
//  Copyright © 2021 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPErrors.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPSetupIntent;

/**
 An error from `-[SCPTerminal confirmSetupIntent:completion:]`
 */
NS_SWIFT_NAME(ConfirmSetupIntentError)
@interface SCPConfirmSetupIntentError : NSError

/**
 The updated SetupIntent after `confirmSetupIntent` failed.
 */
@property (nonatomic, nullable, readonly) SCPSetupIntent *setupIntent;

/**
 If `confirmSetupIntent` failed because the underlying network request errored,
 this property contains additional details about the error.
 */
@property (nonatomic, nullable, readonly) NSError *requestError;

/**
 If `confirmSetupIntent` failed because the payment method was declined, this
 property contains the decline code.
 */
@property (nonatomic, nullable, readonly) NSString *declineCode;

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
