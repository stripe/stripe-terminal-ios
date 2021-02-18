//
//  SCPCancelable.h
//  StripeTerminal
//
//  Created by Ben Guo on 6/2/18.
//  Copyright © 2018 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"

NS_ASSUME_NONNULL_BEGIN

/**
 An object representing an action that can be canceled.
 */
NS_SWIFT_NAME(Cancelable)
@interface SCPCancelable : NSObject

/**
 Indicates whether the command has completed. After the command has completed,
 subsequent calls to cancel will fail.
 */
@property (nonatomic, readonly) BOOL completed;

/**
 Attempts to cancel the action in progress. If the action could not be canceled,
 e.g. it has already completed, the completion block will be called with an
 error. Otherwise, the completion block will be called with nil.
 */
- (void)cancel:(SCPErrorCompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
