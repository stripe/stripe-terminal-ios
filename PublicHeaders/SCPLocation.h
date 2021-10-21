//
//  SCPLocation.h
//  StripeTerminal
//
//  Created by Brian Cooke on 6/22/20.
//  Copyright © 2020 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPJSONDecodable.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPAddress;

/**
 A Location is used to group readers in the Stripe Terminal ecosystem. The
 Location to which a reader is registered can control regional behavior
 for that particular reader.

 You cannot create locations through the SDK. Instead, use the Stripe API
 from your backend to manage your account's locations.

 To fetch the Location objects associated with your account, call
 `Terminal.shared.listLocations()`.

 @see https://stripe.com/docs/api/terminal/locations
 */
NS_SWIFT_NAME(Location)
@interface SCPLocation : NSObject <SCPJSONDecodable>

/**
 The ID of the Location
 */
@property (nonatomic, copy, readonly) NSString *stripeId;

/**
 The address of this Location
 @see `SCPAddress`
 */
@property (nonatomic, nullable, strong, readonly) SCPAddress *address;

/**
 The display name of this Location
 */
@property (nonatomic, nullable, copy, readonly) NSString *displayName;

/**
 Whether this Location was created in livemode
 */
@property (nonatomic, assign, readonly) BOOL livemode;

/**
 Any metadata attached to this Location

 @see https://stripe.com/docs/api/terminal/locations/create#create_terminal_location-metadata
 */
@property (nonatomic, nullable, strong, readonly) NSDictionary<NSString *, NSString *> *metadata;

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
