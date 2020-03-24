//
//  SCPReaderNetworkStatus.h
//  StripeTerminal
//
//  Created by Catriona Scott on 7/1/19.
//  Copyright © 2019 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

NS_ASSUME_NONNULL_BEGIN

/**
 The possible device types for a reader.

 @see https://stripe.com/docs/api/terminal/readers/object
 */
typedef NS_ENUM(NSUInteger, SCPReaderNetworkStatus) {

    /**
     The reader is offline. Note that Chipper2x will also default to 'offline'.
     */
    SCPReaderNetworkStatusOffline,

    /**
     The reader is online.
     */
    SCPReaderNetworkStatusOnline,
} NS_SWIFT_NAME(ReaderNetworkStatus);

NS_ASSUME_NONNULL_END
