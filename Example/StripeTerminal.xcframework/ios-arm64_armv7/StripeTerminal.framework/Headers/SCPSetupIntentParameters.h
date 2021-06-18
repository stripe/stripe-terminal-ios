//
//  SCPSetupIntentParameters.h
//  StripeTerminal
//
//  Created by James Little on 10/13/20.
//  Copyright © 2020 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPSetupIntent.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Parameters for creating an `SCPSetupIntent`.

 @see https://stripe.com/docs/api/setup_intents/create
 */
NS_SWIFT_NAME(SetupIntentParameters)
@interface SCPSetupIntentParameters : NSObject

/**
 ID of the customer this SetupIntent belongs to, if one exists.

 If present, the SetupIntent’s payment method will be attached to the Customer
 on successful setup. Payment methods attached to other Customers cannot be
 used with this SetupIntent.
 */
@property (nonatomic, copy, nullable, readwrite) NSString *customer;

/**
 An arbitrary string attached to the object. Often useful for displaying to users.
 */
@property (nonatomic, copy, nullable, readwrite) NSString *stripeDescription;

/**
 Set of key-value pairs that you can attach to an object. This can be useful for
 storing additional information about the object in a structured format.
 */
@property (nonatomic, copy, nullable, readwrite) NSDictionary *metadata;

/**
 Indicates how the payment method is intended to be used in the future. If not
 provided, this value defaults to `SCPSetupIntentUsageOffSession`.
 */
@property (nonatomic, readwrite) SCPSetupIntentUsage usage;

/**
 **Connect Only:** The Stripe account ID for which this SetupIntent is created.
 */
@property (nonatomic, copy, nullable, readwrite) NSString *onBehalfOf;

/**
 Initializes SCPSetupIntentParameters with the given customer ID.

 @param customerId ID of the customer this SetupIntent belongs to, if one exists.
 Stripe will attach this SetupIntent to the customer on successful creation.
 */
- (instancetype)initWithCustomer:(NSString *_Nullable)customerId;

/**
 Use `initWithCustomer:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithCustomer:`
 */
+ (instancetype)new NS_UNAVAILABLE;

/**
 Use stripeDescription for the string attached to the object.
*/
@property (nonatomic, copy, readonly) NSString *description DEPRECATED_MSG_ATTRIBUTE("Did you mean to use stripeDescription?");

@end

NS_ASSUME_NONNULL_END
