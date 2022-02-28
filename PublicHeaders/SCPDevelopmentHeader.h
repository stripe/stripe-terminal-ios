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

@end

#pragma mark - SCPReader

@interface SCPReader (Development)
@property (nonatomic, copy, nullable, readwrite) NSDictionary *hardwareInfo;
@end

@interface SCPStripeAPIOnlineClient : NSObject

@property (class, nonatomic, strong, readwrite) NSURL *apiBaseUrl;

@property (class, nonatomic, copy, readwrite) NSDictionary<NSString *, NSString *> *customHeaders;

@end

NS_ASSUME_NONNULL_END
