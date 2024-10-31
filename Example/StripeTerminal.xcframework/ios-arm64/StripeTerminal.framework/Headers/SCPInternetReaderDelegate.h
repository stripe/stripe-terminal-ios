//
//  SCPInternetReaderDelegate.h
//  StripeTerminal
//
//  Created by Brian Cooke on 10/10/2022.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPReaderDelegate.h>

@class SCPReader;

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle a connected internet reader's events throughout
 the lifetime of its connection.

 The provided delegate must be retained by your application until the reader disconnects.
 */
NS_SWIFT_NAME(InternetReaderDelegate)
@protocol SCPInternetReaderDelegate <SCPReaderDelegate>
@end

NS_ASSUME_NONNULL_END
