//
//  SCPReaderDelegate.h
//  StripeTerminal
//
//  Created by Brian Cooke on 10/10/2022.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPConnectionStatus.h>
#import <StripeTerminal/SCPDisconnectReason.h>

@class SCPReader, SCPCancelable;

NS_ASSUME_NONNULL_BEGIN

/**
 This is a base reader delegate protocol that all reader delegates inherit from.

 Don't implement this directly but instead implement the specific delegates needed for the reader types you'll use:
 SCPMobileReaderDelegate, SCPInternetReaderDelegate, or SCPTapToPayReaderDelegate
 */
NS_SWIFT_NAME(ReaderDelegate)
@protocol SCPReaderDelegate <NSObject>

@optional

/**
 Optional method that is called when the reader has disconnected from the SDK and includes the
 reason for the disconnect.

 @param reader      The originating reader.
 @param reason      The reason for the disconnect. @see `SCPDisconnectReason`
 */
- (void)reader:(SCPReader *)reader didDisconnect:(SCPDisconnectReason)reason NS_SWIFT_NAME(reader(_:didDisconnect:));

#pragma mark - Auto reconnect methods

/**
 Mobile readers and Tap to Pay only.

 The reader has lost connection to the SDK and reconnection attempts have been started.

 In your implementation of this method, you should notify your user that
 the reader disconnected and that reconnection attempts are being made.

 @param reader            The reader that is attempting to be reconnected to
 @param cancelable        A cancelable that can be used to stop reconnection
 @param disconnectReason  The reason the reader disconnected

 */
- (void)reader:(SCPReader *)reader didStartReconnect:(SCPCancelable *)cancelable disconnectReason:(SCPDisconnectReason)disconnectReason NS_SWIFT_NAME(reader(_:didStartReconnect:disconnectReason:));

/**
 Mobile readers and Tap to Pay only.

 The SDK was able to reconnect to the previously connected Bluetooth reader.

 In your implementation of this method, you should notify your user that
 reader connection has been re-established.

 Requires `autoReconnectOnUnexpectedDisconnect` is set to `true` in the `SCPBluetoothConnectionConfig`

 @param reader  The reader that has now been reconnected to.
 */
- (void)readerDidSucceedReconnect:(SCPReader *)reader NS_SWIFT_NAME(readerDidSucceedReconnect(_:));

/**
 Mobile readers and Tap to Pay only.

 The SDK was not able to reconnect to the previously connected bluetooth reader. The SDK is now disconnected from any readers.

 In your implementation of this method, you should notify your user that
 the reader has disconnected.

 Requires `autoReconnectOnUnexpectedDisconnect` is set to `true` in the `SCPBluetoothConnectionConfig`

 @param reader    The reader that failed to be reconnected to.
 */
- (void)readerDidFailReconnect:(SCPReader *)reader NS_SWIFT_NAME(readerDidFailReconnect(_:));

@end

NS_ASSUME_NONNULL_END
