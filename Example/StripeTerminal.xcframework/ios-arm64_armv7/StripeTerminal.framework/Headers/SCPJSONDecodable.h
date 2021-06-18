//
//  SCPJSONDecodable.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/26/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Objects conforming to this protocol can be instantiated by decoding a JSON
 dictionary.
 */
NS_SWIFT_NAME(JSONDecodable)
@protocol SCPJSONDecodable <NSObject>

/**
 Parses a JSON dictionary into an instance of the class. Returns nil if the
 object could not be decoded.
 */
+ (nullable instancetype)decodedObjectFromJSON:(nullable NSDictionary *)json;

/**
 The raw JSON used to create the object. This may be useful for accessing
 fields that haven't yet been made into properties in the SDK.
 */
@property (nonatomic, readonly) NSDictionary *originalJSON;

@end

NS_ASSUME_NONNULL_END
