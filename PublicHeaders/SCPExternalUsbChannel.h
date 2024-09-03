//
//  SCPExternalUsbChannel.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2024-07-29.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBlocks.h>
#import <StripeTerminal/SCPUsbConnectionConfiguration.h>
#import <StripeTerminal/SCPUsbReaderDelegate.h>

#ifdef SCP_EXTERNAL_CHANNEL_ENABLED

NS_ASSUME_NONNULL_BEGIN

/// Data completion used when reading from the external channel. data and error are mutually exclusive.
typedef void (^SCPExternalUsbChannelDataCompletion)(NSData *_Nullable data, NSError *_Nullable error);
/// Nullable error completion. A null error is success.
typedef void (^SCPExternalUsbChannelErrorCompletion)(NSError *_Nullable error);

// Available disconnect reasons for external connected readers
typedef NS_ENUM(NSUInteger, SCPExternalUsbChannelDisconnectReason) {
    // Reader unplugged from external connection
    SCPExternalUsbChannelDisconnectReasonReaderDisconnected,
    // External connection disconnected
    SCPExternalUsbChannelDisconnectReasonExternallyDisconnected,
    // Disconnect requested via Terminal.disconnectReader
    SCPExternalUsbChannelDisconnectReasonRequested,
    // Reader firmware reported disconnect
    SCPExternalUsbChannelDisconnectReasonReaderReset,
    // Error during read, SDK will disconnect
    SCPExternalUsbChannelDisconnectReasonReadError,
    // Error during write, SDK will disconnect
    SCPExternalUsbChannelDisconnectReasonWriteError,
};

/**
 Delegate to be set on the ExternalUsbChannel to receive any async messages we need.
 */
@protocol SCPExternalUsbChannelDelegate

/// Sent if the connected reader has been disconnected from the external channel.
- (void)didDisconnectWithReason:(SCPExternalUsbChannelDisconnectReason)reason;

@end

/**
 Protocol to implement for providing an external communication channel for a connected reader.

 Private developer preview.
 */
@protocol SCPExternalUsbChannel

/// The vendorId of the connected reader
@property (nonatomic, readonly) NSUInteger vendorId;
/// The productId of the connected reader
@property (nonatomic, readonly) NSUInteger productId;
/// Packet size read from the reader when connecting
@property (nonatomic, readonly) NSUInteger packetSize;
/// How frequently to poll for reading data - will be filled in by Terminal SDK
@property (nonatomic, readwrite) NSUInteger pollingIntervalMs;
/// How long to wait before giving up on a read or write operation - will be filled in by Terminal SDK
@property (nonatomic, readwrite) NSUInteger readWriteTimeoutMs;
/// Delegate should be set as soon as the channel instance is received
@property (nonatomic, weak) id<SCPExternalUsbChannelDelegate> delegate;

/// request to read data from the external channel.
- (void)readData:(SCPExternalUsbChannelDataCompletion)completion;
/// request to write data over the external channel.
- (void)writeData:(NSData *)data completion:(SCPExternalUsbChannelErrorCompletion)completion;
/// request to disconnect from the reader connected by the external channel.
- (void)disconnectWithReason:(SCPExternalUsbChannelDisconnectReason)reason;

@end

@interface SCPTerminal (ExternalUsbChannel)

/**
 Connect to a reader over the provided external USB channel. Reuses the existing UsbReaderDelegate
 and UsbConnectionConfiguration.

 The completion will be called with the SCPReader that has been connected to, or error.

 The SDK performs all the same actions as connectUsbReader:, including checking for and installing
 required updates.

 There is no need to call discoverReaders when using this channel.

 Once connected all interactions match the existing behavior for mobile readers.

 Private developer preview.
 */
- (void)connectExternalUsbChannel:(id<SCPExternalUsbChannel>)externalChannel
                         delegate:(id<SCPUsbReaderDelegate>)delegate
                 connectionConfig:(SCPUsbConnectionConfiguration *)connectionConfig
                       completion:(SCPReaderCompletionBlock)completion NS_SWIFT_NAME(connectExternalUsbChannel(_:delegate:connectionConfig:completion:));

@end

NS_ASSUME_NONNULL_END

#endif // SCP_EXTERNAL_CHANNEL_ENABLED
