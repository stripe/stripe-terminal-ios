//
//  SCPActivationTokenProvider.h
//  StripePOS
//
//  Created by Ben Guo on 12/21/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"

@class SCPAddress;

NS_ASSUME_NONNULL_BEGIN

/**
 Before integrating the SDK, you should create an endpoint on your backend
 that creates a new Point of Sale activation token via the Stripe API.
 The SDK will request a new activation token from this endpoint whenever your
 app connects to a reader.

 We suggest making your application's API client conform to this protocol.

 For more information, follow the integration guide at
 https://stripe.com/docs/point-of-sale
 */
@protocol SCPActivationTokenProvider <NSObject>

/**
 On your backend, reset the terminal with the given pos_device_id and return the
 activation_token from the response to your app. In your app, call the
 completion block with the activation token, or an error if one occurred.

 @param posDeviceId     Pass this to your backend to create an activation token
 for the specified POS device.

 @param completion      Call this with an activation token, or an error if one occurred.
 */
- (void)getToken:(NSString *)posDeviceId completion:(SCPActivationTokenCompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
