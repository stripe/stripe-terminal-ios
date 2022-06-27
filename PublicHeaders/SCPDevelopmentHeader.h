//
//  SCPDevelopmentHeader.h
//  StripeTerminal
//
//  Created by Ben Guo on 11/30/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

/**
 This header contains APIs used for internal development.
 */

@class SCPVoidPromise;

#pragma mark - SCPTerminal

@interface SCPTerminal (Development)

/**
 Enables:
 1. Logging encrypted emv_data to console
 2. Throwing exceptions for fatal errors
 */
@property (nonatomic, assign) BOOL devModeEnabled;

/**
 Global setting for the URL to use when talking to Stripe.

 Changing this will immediately affect all subsequent API calls.
 */
@property (class, nonatomic, strong, readwrite) NSURL *apiBaseUrl;

/**
 Global setting for custom test headers when talking to Stripe.

 Changing this will add these headers to any subsequent API request made.
 */
@property (class, nonatomic, copy, readwrite) NSDictionary<NSString *, NSString *> *customHeaders;

@end

#pragma mark - SCPReader

@interface SCPReader (Development)
@property (nonatomic, copy, nullable, readwrite) NSDictionary *hardwareInfo;
@end

NS_ASSUME_NONNULL_END
