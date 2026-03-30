//
//  SCPApiError.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2025-08-29.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An API error returned by Stripe when a request fails.

 @see https://stripe.com/docs/api/errors
 */
NS_SWIFT_NAME(ApiError)
@interface SCPApiError : NSObject <NSCopying>

/**
 The type of error returned.
 */
@property (nonatomic, nullable, readonly) NSString *type;

/**
 ID of failed charge, if applicable.
 */
@property (nonatomic, nullable, readonly) NSString *charge;

/**
 For some errors that could be handled programmatically, a short string indicating the error code reported.

 @see https://stripe.com/docs/error-codes
 */
@property (nonatomic, nullable, readonly) NSString *code;

/**
 For card errors resulting from a card issuer decline, a short string indicating the card issuer's reason for the decline if they provide one.

 @see https://stripe.com/docs/declines#issuer-declines
 */
@property (nonatomic, nullable, readonly) NSString *declineCode;

/**
 A URL to more information about the error code reported.
 */
@property (nonatomic, nullable, readonly) NSString *docUrl;

/**
 A human-readable message providing more details about the error. For card errors, these messages can be shown to your users.
 */
@property (nonatomic, nullable, readonly) NSString *message;

/**
 If the error is parameter-specific, the parameter related to the error. For example, you can use this to display a message near the correct form field.
 */
@property (nonatomic, nullable, readonly) NSString *param;

/**
 A URL to the request log entry in your dashboard.

 For ApiErrors returned from smart readers, a minimum version of 2.41 is
 required for this field to be populated.
 */
@property (nonatomic, nullable, readonly) NSString *requestLogUrl;

/**
 For payments declined by the network, an alphanumeric code which indicates the reason the payment failed.

 For ApiErrors returned from smart readers, a minimum version of 2.41 is
 required for this field to be populated.
 */
@property (nonatomic, nullable, readonly) NSString *networkDeclineCode;

/**
 For card errors resulting from a card issuer decline, a short string indicating how to proceed with an error if they provide one.

 For ApiErrors returned from smart readers, a minimum version of 2.41 is
 required for this field to be populated.

 @see https://docs.stripe.com/declines#retrying-issuer-declines
 */
@property (nonatomic, nullable, readonly) NSString *adviceCode;

/**
 For card errors resulting from a card issuer decline, a 2 digit code which indicates the advice given to merchant by the card network on how to proceed with an error.

 For ApiErrors returned from smart readers, a minimum version of 2.41 is
 required for this field to be populated.
 */
@property (nonatomic, nullable, readonly) NSString *networkAdviceCode;

/**
 You cannot directly instantiate this class. You should only use ApiErrors
 that have been returned by other methods in our SDK.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class. You should only use ApiErrors
 that have been returned by other methods in our SDK.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
