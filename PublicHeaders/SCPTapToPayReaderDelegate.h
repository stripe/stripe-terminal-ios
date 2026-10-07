//
//  SCPTapToPayReaderDelegate.h
//  StripeTerminal
//
//  Created by Martin Mroz on 2/16/22.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <StripeTerminal/SCPReaderInteractionDelegate.h>

@class SCPReader;

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle a connected tap to pay reader's events throughout
 the lifetime of its connection.

 Implementing this delegate is required when connecting to any Tap To Pay reader.

 The provided delegate must be retained by your application until the reader disconnects.
 */
NS_SWIFT_NAME(TapToPayReaderDelegate)
@protocol SCPTapToPayReaderDelegate <SCPReaderInteractionDelegate>

@optional

/**
 The reader is reporting that, as part of preparing to accept payments,
 the terms of service has been accepted.

 @param reader The originating reader.
 */
- (void)tapToPayReaderDidAcceptTermsOfService:(SCPReader *)reader
    NS_SWIFT_NAME(tapToPayReaderDidAcceptTermsOfService(_:));

@end

NS_ASSUME_NONNULL_END
