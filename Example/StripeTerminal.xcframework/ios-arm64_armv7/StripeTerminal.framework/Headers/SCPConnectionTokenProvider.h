//
//  SCPConnectionTokenProvider.h
//  StripeTerminal
//
//  Created by Ben Guo on 12/21/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Before integrating the SDK, you should create an endpoint on your backend
 server that creates a new connection token via the Stripe Terminal API. The
 connection token is used by the SDK to connect to a reader.

 An overview of the lifecycle of a connection token:
 - When Stripe Terminal is initialized, the SDK attempts to proactively request
 an connection token from your backend server.
 - The SDK uses the connection to connect to a reader.
 - Subsequent calls to connect require a new connection token. If you disconnect
 from a reader, and then call connect again, the SDK will need a new connection
 token from your backend server.

 We suggest making your application's API client conform to this protocol.

 @see https://stripe.com/docs/terminal/sdk/ios#connection-token
 */
NS_SWIFT_NAME(ConnectionTokenProvider)
@protocol SCPConnectionTokenProvider

/**
 Fetches a connection token from your backend server.

 On your backend server, use Stripe's `/v1/terminal/connection_tokens` endpoint to
 create a connection token, and return the `connection_token` string from the response
 to your app. In your app, call the completion block with the connection token,
 or an error if fetching the token failed.

 @see https://stripe.com/docs/api/terminal/connection_tokens/create

 @param completion      Call this with a connection token, or an error if
 creating the connection token failed.
 */
- (void)fetchConnectionToken:(SCPConnectionTokenCompletionBlock)completion NS_SWIFT_NAME(fetchConnectionToken(_:));

@end

NS_ASSUME_NONNULL_END
