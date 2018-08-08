//
//  SCPCancelable.h
//  StripePOS
//
//  Created by Ben Guo on 6/2/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPBlocks.h"

NS_ASSUME_NONNULL_BEGIN

/**
 An object representing an action that can be canceled.
 */
@interface SCPCancelable : NSObject

/**
 Indicates whether the command has completed. After the command has completed,
 subsequenc calls to cancel will fail.
 */
@property (nonatomic, readonly) BOOL completed;

/**
 Attempts to cancel the action in progress. If the action could not be canceled,
 e.g. it has already completed, the completion block will be called with NO.
 If the cancel was successful, the completion block will be called with YES.
 */
- (void)cancel:(SCPBoolCompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
