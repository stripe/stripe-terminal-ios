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
 Implement this protocol to handle bluetooth auto-reconnection.
 */
NS_SWIFT_NAME(ReconnectionDelegate)
@protocol SCPReconnectionDelegate <NSObject>
/**
 The reader has lost Bluetooth connection to the SDK and reconnection attempts have been started.

 In your implementation of this method, you should notify your user that
 the reader disconnected and that reconnection attempts are being made.

 Requires `autoReconnectOnUnexpectedDisconnect` is set to `true` in the `SCPBluetoothConnectionConfig`

 @param terminal          The originating terminal.
 @param cancelable        A cancelable that can be used to stop reconnection

 */
- (void)terminal:(SCPTerminal *)terminal didStartReaderReconnect:(SCPCancelable *)cancelable NS_SWIFT_NAME(terminal(_:didStartReaderReconnect:));

/**
 The SDK was able to reconnect to the previously connected Bluetooth reader.

 In your implementation of this method, you should notify your user that
 reader connection has been re-established.

 Requires `autoReconnectOnUnexpectedDisconnect` is set to `true` in the `SCPBluetoothConnectionConfig`

 @param terminal            The originating terminal.
 */
- (void)terminalDidSucceedReaderReconnect:(SCPTerminal *)terminal NS_SWIFT_NAME(terminalDidSucceedReaderReconnect(_:));

/**
 The SDK was not able to reconnect to the previously connected bluetooth reader. The SDK is now disconnected from any readers.

 In your implementation of this method, you should notify your user that
 the reader has disconnected.

 Requires `autoReconnectOnUnexpectedDisconnect` is set to `true` in the `SCPBluetoothConnectionConfig`

 @param terminal            The originating terminal.
 */
- (void)terminalDidFailReaderReconnect:(SCPTerminal *)terminal NS_SWIFT_NAME(terminalDidFailReaderReconnect(_:));
@end

NS_ASSUME_NONNULL_END
