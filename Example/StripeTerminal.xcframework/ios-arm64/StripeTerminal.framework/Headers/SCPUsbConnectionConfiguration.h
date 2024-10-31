//
//  SCPUsbConnectionConfiguration.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2024-02-16.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#ifdef SCP_USB_ENABLED

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPConnectionConfiguration.h>
#import <StripeTerminal/SCPMobileReaderDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This class lets you define USB reader connection options.

 An object of this class should get passed into `Terminal.shared.connectReader()`.
 */
NS_SWIFT_NAME(UsbConnectionConfiguration)
@interface SCPUsbConnectionConfiguration : SCPConnectionConfiguration

/**
 The MobileReaderDelegate to use for this connection to the reader.
 */
@property (nonatomic, weak, readonly) id<SCPMobileReaderDelegate> delegate;

/**
 The ID of the [Location](https://stripe.com/docs/api/terminal/locations) which the reader should be registered to during connection.

 If the provided ID matches the location the reader is already registered to, the
 location will not be changed.

 When connecting to a simulated reader, pass in the reader's pre-existing mock location.
 You can find the mock location ID on the reader object returned to the DiscoveryDelegate,
 on the `locationId` property.

 @see https://stripe.com/docs/terminal/readers/fleet-management#bbpos-wisepad3-discovery
 */
@property (nonatomic, readonly) NSString *locationId;

/**
 When set to true, the Terminal SDK  will attempt a USB auto-reconnection on any unexpected disconnect.
 Implement the `reader:didStartReconnect:` and related callbacks  for your application to respond accordingly to
 reconnection attempts.

 When set to false, the SDK will immediately surface any disconnection through ReaderDelegate.

 Defaults to true.
 */
@property (nonatomic, assign, readonly) BOOL autoReconnectOnUnexpectedDisconnect;

/**
 Use `SCPUsbConnectionConfigurationBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPUsbConnectionConfigurationBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 The `UsbConnectionConfigurationBuilder` is used to create a `UsbConnectionConfiguration` object.
 */
NS_SWIFT_NAME(UsbConnectionConfigurationBuilder)
@interface SCPUsbConnectionConfigurationBuilder : SCPBuilder <SCPUsbConnectionConfiguration *>

/// Create a `UsbConnectionConfiguration` with the provided delegate and locationId.
- (instancetype)initWithDelegate:(id<SCPMobileReaderDelegate>)delegate locationId:(NSString *)locationId NS_DESIGNATED_INITIALIZER;

/// Set the locationId property for the `UsbConnectionConfiguration` object that will be built.
- (SCPUsbConnectionConfigurationBuilder *)setLocationId:(NSString *)locationId;

/// Set the autoReconnectOnUnexpectedDisconnect property for the `UsbConnectionConfiguration` object that will be built.
- (SCPUsbConnectionConfigurationBuilder *)setAutoReconnectOnUnexpectedDisconnect:(BOOL)autoReconnectOnUnexpectedDisconnect;

/**
 Use `initWithLocationId:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithLocationId:`
 */
+ (instancetype)new NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END

#endif // SCP_USB_ENABLED
