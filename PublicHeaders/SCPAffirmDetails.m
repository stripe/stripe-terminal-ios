//
//  SCPAffirmDetails.m
//  StripeTerminal
//
//  Created by Henry Xu on 9/4/24.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import "SCPAffirmDetails.h"
#import "NSDictionary+StripeTerminal.h"

NS_ASSUME_NONNULL_BEGIN

static NSString *const JsonKeyLocation = @"location";
static NSString *const JsonKeyReader = @"reader";
static NSString *const JsonKeyTransactionId = @"transaction_id";

@implementation SCPAffirmDetails
@synthesize originalJSON = _originalJSON;

+ (nullable instancetype)decodedObjectFromJSON:(nullable NSDictionary *)json {
    if (!json) {
        return nil;
    }
    NSDictionary *dict = [json scp_dictionaryByRemovingNulls];

    SCPAffirmDetails *object = [self new];
    object->_originalJSON = dict;
    object->_location = [[dict scp_stringForKey:JsonKeyLocation] copy];
    object->_reader = [[dict scp_stringForKey:JsonKeyReader] copy];
    object->_transactionId = [[dict scp_stringForKey:JsonKeyTransactionId] copy];
    return object;
}

- (NSString *)description {
    NSArray *props = @[
        [NSString stringWithFormat:@"%@: %p", NSStringFromClass([self class]), self],
        [NSString stringWithFormat:@"location = %@", self.location],
        [NSString stringWithFormat:@"reader = %@", self.reader],
        [NSString stringWithFormat:@"transactionId = %@", self.transactionId]
    ];

    return [NSString stringWithFormat:@"<%@>", [props componentsJoinedByString:@"; "]];
}
@end

NS_ASSUME_NONNULL_END
