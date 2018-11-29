//
//  SCPUpdateReaderSoftwareParameters.h
//  StripeTerminal
//
//  Created by Ben Guo on 9/29/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The possible environments a reader software update.
 */
typedef NS_ENUM(NSUInteger, SCPUpdateReaderSoftwareEnvironment) {
    /**
     The production update environment. Use this environment if you received
     your reader as part of the Stripe Terminal Beta program.
     */
    SCPUpdateReaderSoftwareEnvironmentProduction,
    /**
     The test update environment. If you received readers as part of the Stripe
     Terminal alpha program, you may need to use this environment in order
     to update your reader. If this is the case, please contact your account
     manager to arrange exchanging this test device.
     */
    SCPUpdateReaderSoftwareEnvironmentTest,

} NS_SWIFT_NAME(UpdateReaderSoftwareEnvironment);

/**
 Parameters for updating reader software.
 */
NS_SWIFT_NAME(UpdateReaderSoftwareParameters)
@interface SCPUpdateReaderSoftwareParameters : NSObject

/**
 The environment for the reader software update. The default is production.
 In nearly all cases, your reader will be registered in the production
 environment. If you received readers as part of the Stripe Terminal alpha
 program, you may need to use this environment in order to update your
 reader.
 */
@property (nonatomic, assign, readwrite) SCPUpdateReaderSoftwareEnvironment environment;

@end

NS_ASSUME_NONNULL_END
