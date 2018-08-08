//
//  SCPAddress.h
//  StripePOS
//
//  Created by Ben Guo on 8/29/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPJSONDecodable.h"

NS_ASSUME_NONNULL_BEGIN

/**
 An object representing a street address.
 */
@interface SCPAddress : NSObject <SCPJSONDecodable>

/**
 The first line of the street address (e.g. "123 Fake St").
 */
@property (nonatomic, nullable, readonly) NSString *line1;

/**
 The apartment, floor number, etc of the street address (e.g. "Apartment 1A").
 */
@property (nonatomic, nullable, readonly) NSString *line2;

/**
 The city of the street address (e.g. "San Francisco").
 */
@property (nonatomic, nullable, readonly) NSString *city;

/**
 The state of the street address (e.g. "CA").
 */
@property (nonatomic, nullable, readonly) NSString *state;

/**
 The postal code of the street address (e.g. "90210").
 */
@property (nonatomic, nullable, readonly) NSString *postalCode;

/**
 The ISO country code of the address (e.g. "US")
 */
@property (nonatomic, nullable, readonly) NSString *country;

/**
 Initializes a new SCPStripeAddress with the given parameters.
 */
- (instancetype)initWithLine1:(NSString *)line1
                        line2:(nullable NSString *)line2
                         city:(NSString *)city
                        state:(NSString *)state
                   postalCode:(NSString *)postalCode
                      country:(NSString *)country;



/**
 Use `initWithLine1:...`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithLine1:...`
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
