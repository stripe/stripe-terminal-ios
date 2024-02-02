//
//  SCPReconnectionCallback.h
//  StripeTerminal
//
//  Created by Matthew Krager on 6/1/22.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPTerminal.h>
NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle Bluetooth auto-reconnection.
 */
NS_SWIFT_NAME(ReconnectionDelegate)
@protocol SCPReconnectionDelegate <NSObject>
/**
 The SDK was able to reconnect to the previously connected Bluetooth reader.

 In your implementation of this method, you should notify your user that
 reader connection has been re-established.

 Requires `autoReconnectOnUnexpectedDisconnect` is set to `true` in the `SCPBluetoothConnectionConfig`

 @param reader  The reader that has now been reconnected to.
 */
- (void)readerDidSucceedReconnect:(SCPReader *)reader NS_SWIFT_NAME(readerDidSucceedReconnect(_:));

/**
 The SDK was not able to reconnect to the previously connected bluetooth reader. The SDK is now disconnected from any readers.

 In your implementation of this method, you should notify your user that
 the reader has disconnected.

 Requires `autoReconnectOnUnexpectedDisconnect` is set to `true` in the `SCPBluetoothConnectionConfig`

 @param reader    The reader that failed to be reconnected to.
 */
- (void)readerDidFailReconnect:(SCPReader *)reader NS_SWIFT_NAME(readerDidFailReconnect(_:));

@optional

/**
 The reader has lost Bluetooth connection to the SDK and reconnection attempts have been started.

 In your implementation of this method, you should notify your user that
 the reader disconnected and that reconnection attempts are being made.

 Requires `autoReconnectOnUnexpectedDisconnect` is set to `true` in the `SCPBluetoothConnectionConfig`

 @note Update to `reader:didStartReconnect:disconnectReason:` to get the reason the reader disconnected.
 If that method is not implemented, this method will be not be called. This method will be removed in 4.0.

 @param reader            The reader that is attempting to be reconnected to.
 @param cancelable        A cancelable that can be used to stop reconnection

 */
- (void)reader:(SCPReader *)reader didStartReconnect:(SCPCancelable *)cancelable NS_SWIFT_NAME(reader(_:didStartReconnect:)) __attribute__((deprecated("Use reader:didStartReconnect:disconnectReason: instead.")));

/**
 The reader has lost Bluetooth connection to the SDK and reconnection attempts have been started.

 In your implementation of this method, you should notify your user that
 the reader disconnected and that reconnection attempts are being made.

 Requires `autoReconnectOnUnexpectedDisconnect` is set to `true` in the `SCPBluetoothConnectionConfig`

 @param reader            The reader that is attempting to be reconnected to
 @param cancelable        A cancelable that can be used to stop reconnection
 @param disconnectReason  The reason the reader disconnected

 */
- (void)reader:(SCPReader *)reader didStartReconnect:(SCPCancelable *)cancelable disconnectReason:(SCPDisconnectReason)disconnectReason NS_SWIFT_NAME(reader(_:didStartReconnect:disconnectReason:));

@end

NS_ASSUME_NONNULL_END
