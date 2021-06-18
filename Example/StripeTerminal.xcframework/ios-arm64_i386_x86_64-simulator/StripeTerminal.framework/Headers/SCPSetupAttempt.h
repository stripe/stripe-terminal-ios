//
//  SCPSetupAttempt.h
//  StripeTerminal
//
//  Created by James Little on 1/18/21.
//  Copyright © 2021 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPSetupAttemptPaymentMethodDetails;

/**
 A SetupAttempt describes one attempted confirmation of a SetupIntent,
 whether that confirmation was successful or unsuccessful. You can use
 SetupAttempts to inspect details of a specific attempt at setting up a
 payment method using a SetupIntent.

 @see https://stripe.com/docs/api/setup_attempts
 */
NS_SWIFT_NAME(SetupAttempt)
@interface SCPSetupAttempt : NSObject <SCPJSONDecodable>

/**
 The ID of the Connect application that created the SetupIntent.
 */
@property (nonatomic, nullable, readonly) NSString *application;

/**
 Time at which the object was created.
 */
@property (nonatomic, readonly) NSDate *created;

/**
 ID of the Customer this SetupIntent belongs to, if one exists.
 */
@property (nonatomic, nullable, readonly) NSString *customer;

/**
 (Connect) The account (if any) for which the setup is intended.
 */
@property (nonatomic, nullable, readonly) NSString *onBehalfOf;

/**
 ID of the payment method used with this SetupAttempt.
 */
@property (nonatomic, nullable, readonly) NSString *paymentMethod;

/**
 Details about the payment method at the time of SetupIntent confirmation.
 */
@property (nonatomic, nullable, readonly) SCPSetupAttemptPaymentMethodDetails *paymentMethodDetails;

/**
 ID of the SetupIntent that this attempt belongs to.
 */
@property (nonatomic, readonly) NSString *setupIntent;

/**
 The status of this SetupAttempt. One of: `requires_confirmation`,
 `requires_action`, `processing`, `succeeded`, `failed`, or `abandoned`.
 */
@property (nonatomic, readonly) NSString *status;

/**
 The unique identifier for the SetupAttempt.
 */
@property (nonatomic, readonly) NSString *stripeId;

@end

NS_ASSUME_NONNULL_END
