//
//  SCPSetupIntentCollectionReason.h
//  StripeTerminal
//
//  Created by Henry Xu on 1/22/25.
//  Copyright © 2025 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 A field used to indicate the reason for Setup Intent Collection. Changing this value can adjust the presented UI during collection.
 This value is only to be used with Tap To Pay readers.
 */
typedef NS_ENUM(NSUInteger, SCPSetupIntentCollectionReason) {
    /**
     This is the default value for setup intent collection. This value is used to indicate to the user that the presented card will be saved.
     */
    SCPSetupIntentCollectionReasonSaveCard,
    /**
     This value is used to indicate to the user that the presented card will be used for verification purposes.
     */
    SCPSetupIntentCollectionReasonVerify,
} NS_SWIFT_NAME(SetupIntentCollectionReason);

NS_ASSUME_NONNULL_END
