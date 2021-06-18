
//
//  SCPListLocationsParameters.h
//  StripeTerminal
//
//  Created by Bibek Ghimire on 3/4/21.
//  Copyright © 2021 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Parameters to be used when calling `Terminal.shared.listLocations()` to list
 the Location objects associated with an account.

 @see https://stripe.com/docs/terminal/readers/connecting
 */
NS_SWIFT_NAME(ListLocationsParameters)
@interface SCPListLocationsParameters : NSObject

/**
 A limit on the number of objects to be returned. Limit can range between 1 and 100, and the default is 10.

 @see https://stripe.com/docs/api/terminal/locations/list#list_terminal_locations-limit
 */
@property (nonatomic, nullable, readwrite) NSNumber *limit;

/**
 A cursor for use in pagination. `ending_before` is an object ID that defines
 your place in the list. For instance, if you make a list request and receive 100
 objects, starting with `obj_bar`, your subsequent call can include
 `ending_before=obj_bar` in order to fetch the previous page of the list.
 
 @see https://stripe.com/docs/api/terminal/locations/list#list_terminal_locations-ending_before
 */
@property (nonatomic, copy, nullable, readwrite) NSString *endingBefore;

/**
 A cursor for use in pagination. `starting_after` is an object ID that defines
 your place in the list. For instance, if you make a list request and receive 100
 objects, ending with `obj_foo`, your subsequent call can include
 `starting_after=obj_foo` in order to fetch the next page of the list.

 @see https://stripe.com/docs/api/terminal/locations/list#list_terminal_locations-starting_after
 */
@property (nonatomic, copy, nullable, readwrite) NSString *startingAfter;

/**
 Initializes SCPListLocationsParameters with the given parameters.

 @param limit A limit on the number of objects to be returned. Limit can range between 1 and 100, and the default is 10.

 @param endingBefore A cursor for use in pagination. `ending_before` is an object ID that defines
 your place in the list. For instance, if you make a list request and receive 100
 objects, starting with `obj_bar`, your subsequent call can include
 `ending_before=obj_bar` in order to fetch the previous page of the list.

 @param startingAfter  A cursor for use in pagination. `starting_after` is an object ID that defines
 your place in the list. For instance, if you make a list request and receive 100
 objects, ending with `obj_foo`, your subsequent call can include
 `starting_after=obj_foo` in order to fetch the next page of the list.
 */
- (instancetype)initWithLimit:(nullable NSNumber *)limit
                 endingBefore:(nullable NSString *)endingBefore
                startingAfter:(nullable NSString *)startingAfter;

@end

NS_ASSUME_NONNULL_END
