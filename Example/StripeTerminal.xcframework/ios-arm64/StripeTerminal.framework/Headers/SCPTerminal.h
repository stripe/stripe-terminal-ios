//
//  SCPTerminal.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/28/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBlocks.h>
#import <StripeTerminal/SCPBluetoothReaderDelegate.h>
#import <StripeTerminal/SCPCardBrand.h>
#import <StripeTerminal/SCPCart.h>
#import <StripeTerminal/SCPCollectConfiguration.h>
#import <StripeTerminal/SCPCollectInputsParameters.h>
#import <StripeTerminal/SCPConnectionStatus.h>
#import <StripeTerminal/SCPCreateConfiguration.h>
#import <StripeTerminal/SCPDeviceType.h>
#import <StripeTerminal/SCPDisconnectReason.h>
#import <StripeTerminal/SCPDiscoveryMethod.h>
#import <StripeTerminal/SCPLocalMobileReaderDelegate.h>
#import <StripeTerminal/SCPLogLevel.h>
#import <StripeTerminal/SCPNetworkStatus.h>
#import <StripeTerminal/SCPOfflineDelegate.h>
#import <StripeTerminal/SCPOfflineStatus.h>
#import <StripeTerminal/SCPPaymentIntentParameters.h>
#import <StripeTerminal/SCPPaymentStatus.h>
#import <StripeTerminal/SCPReadMethod.h>
#import <StripeTerminal/SCPReaderEvent.h>
#import <StripeTerminal/SCPReaderSettingsParameters.h>
#import <StripeTerminal/SCPRefundConfiguration.h>
#import <StripeTerminal/SCPRefundParameters.h>
#import <StripeTerminal/SCPSetupIntentConfiguration.h>
#import <StripeTerminal/SCPSimulatorConfiguration.h>
#import <StripeTerminal/SCPUsbConnectionConfiguration.h>
#import <StripeTerminal/SCPUsbReaderDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The current version of this library.
 */
static NSString *const SCPSDKVersion = @"3.5.0";

@class SCPCancelable,
    SCPCreateConfiguration,
    SCPBluetoothConnectionConfiguration,
    SCPInternetConnectionConfiguration,
    SCPListLocationsParameters,
    SCPLocalMobileConnectionConfiguration,
    SCPPaymentIntentParameters;

@protocol SCPConnectionTokenProvider
, SCPTerminalDelegate, SCPDiscoveryDelegate, SCPDiscoveryConfiguration;

/**
 The `SCPTerminal` singleton object exposes an interface for discovering readers,
 connecting to a reader, creating payments, and saving card information for later
 use.

 Before accessing the singleton object using the `shared` property, you must set
 a ConnectionToken provider: an object that implements the `SCPConnectionTokenProvider`
 protocol. This object should authenticate with your backend, then fetch the [secret](https://stripe.com/docs/api/terminal/connection_tokens/object#terminal_connection_token_object-secret)
 from a freshly minted [ConnectionToken](https://stripe.com/docs/api/terminal/connection_tokens).

 The SCPTerminal singleton can only be connected to one reader at a time, and
 can only perform one operation at a time. As a general rule, make sure the
 completion handler of one operation has been called before calling another
 operation from within your app.

 The Stripe Terminal SDK sends updates to your app by using the delegate pattern.
 You may want multiple views in your app to respond to these delegate calls.
 We recommend creating a central delegate announcer which broadcasts all delegate
 calls to views and ViewControllers that register themselves with that announcer.
 We have an example implementation of a TerminalDelegateAnnouncer as [part of our
 example application](https://github.com/stripe/stripe-terminal-ios/blob/master/Example/Example/TerminalDelegateAnnouncer.swift).
 */
NS_SWIFT_NAME(Terminal)
API_AVAILABLE(ios(13.0))
@interface SCPTerminal : NSObject

#pragma mark Initializing and accessing the SCPTerminal singleton

/**
 Sets the token provider for the shared (singleton) `SCPTerminal` instance.

 You must set a token provider before calling `shared` to initialize the
 Terminal singleton. We recommend calling `setTokenProvider:` in your
 AppDelegate's `application:didFinishLaunchingWithOptions:` method.
 Alternatively, you can wrap your call to `setTokenProvider:` with a
 `dispatch_once` in Objective-C, or use a static constructor in Swift.

 Note that you may only set a token provider *before* requesting the shared
 Terminal instance for the first time. In order to switch accounts in your app,
 e.g. to switch between live and test Stripe API keys on your backend, refer
 to the documentation for the `clearCachedCredentials` method on the shared
 Terminal instance.
 */
+ (void)setTokenProvider:(id<SCPConnectionTokenProvider>)tokenProvider NS_SWIFT_NAME(setTokenProvider(_:));

/**
 Returns true if a token provider has been set, through `setTokenProvider:`
 */
+ (BOOL)hasTokenProvider;

/**
 Sets a block to listen for logs from the shared Terminal instance (optional).

 You can use this optional method to listen for logs from the Stripe Terminal
 SDK and incorporate them into your own remote logs. Note that these logs
 are subject to change, and provided for informational and debugging purposes
 only. You should not depend on them for behavior in your app. Also note that
 the block you provide may be called from any thread.

 To print internal logs from the SDK to the console, you can set `logLevel` to
 `SCPLogLevelVerbose` on the Terminal instance.
 */
+ (void)setLogListener:(SCPLogListenerBlock)listener;

/**
 Returns the shared (singleton) Terminal instance.

 Before accessing the singleton for the first time, you must first call
 `setTokenProvider:`.
 */
@property (class, nonatomic, readonly) SCPTerminal *shared;

/**
 The Terminal singleton object's primary delegate. This delegate announces
 connection and payment status updates to your app.

 Setting this property is mandatory before connecting to a Bluetooth reader,
 like the BBPOS Chipper 2X BT or the BBPOS WisePad 3. Setting this property
 is optional before connecting to an internet reader, like the Verifone P400.

 A runtime assert will fire if your app attempts to connect to a reader that
 requires the delegate.
 */
@property (nonatomic, nullable, readwrite) id<SCPTerminalDelegate> delegate;

#pragma mark Accessing the current state of the singleton

/**
 Information about the connected `SCPReader`, or nil if no reader is connected.
 */
@property (nonatomic, nullable, readonly) SCPReader *connectedReader;

/**
 The Terminal instance's current connection status.
 */
@property (nonatomic, readonly) SCPConnectionStatus connectionStatus;

/**
 The log level for the SDK. The default value is `.none`.
 */
@property (nonatomic, assign, readwrite) SCPLogLevel logLevel;

/**
 The simulator configuration settings that will be used when connecting to
 and creating payments with a simulated reader. This object will always exist;
 to set the configuration settings, set the readwrite properties on
 `Terminal.shared.simulatorConfiguration`.

 @see SCPSimulatorConfiguration
 */
@property (nonatomic, readonly) SCPSimulatorConfiguration *simulatorConfiguration;

/**
 The Terminal instance's current payment status.
 */
@property (nonatomic, readonly) SCPPaymentStatus paymentStatus;

/**
 Clears the current connection token, saved reader sessions, and any other
 cached credentials. You can use this method to switch accounts in your app,
 e.g. to switch between live and test Stripe API keys on your backend.

 In order to switch accounts in your app:
 - if a reader is connected, call `disconnectReader:`
 - configure the `tokenProvider` object to return connection tokens for the new account.
 The `tokenProvider` is implemented by your code, and you can do this however you want.
 - call `clearCachedCredentials`
 - call `discoverReaders` and `connectReader` to connect to a reader. The `connect` call
 will request a new connection token from your backend server via the token provider.

 An overview of the lifecycle of a connection token under the hood:
 - When the Terminal singleton is initialized, the SDK attempts to proactively request
 a connection token from your backend server.
 - When `connect` is called, the SDK uses the connection token and reader
 information to create a reader session.
 - Subsequent calls to `connect` will re-use the reader session if the SDK
 has successfully connected to the reader already. Otherwise, it will require a
 new connection token when you call `connect` again.
 */
- (void)clearCachedCredentials NS_SWIFT_NAME(clearCachedCredentials());

#pragma mark Reader discovery, connection, and updates

/**
 Use this method to determine whether the mobile device supports a given reader type
 using a particular discovery method. This is useful for the Local Mobile reader
 discovery method where support will vary according to operating system
 and hardware capabilities.
 @param deviceType      Reader device type to determine support for.
 @param discoveryMethod Associated discovery method.
 @param simulated       Determines whether to check for availability of
                        simulated discovery to discover a device simulator.
                        The Terminal SDK comes with the ability to simulate behavior
                        without using physical hardware. This makes it easy to
                        quickly test your integration end-to-end,
                        from pairing with a reader to taking payments.
 @param error           If not supported, an error indicating the reason.
 @returns               YES if supported, NO otherwise.
 */
- (BOOL)supportsReadersOfType:(SCPDeviceType)deviceType
              discoveryMethod:(SCPDiscoveryMethod)discoveryMethod
                    simulated:(BOOL)simulated
                        error:(NSError **)error NS_REFINED_FOR_SWIFT;

/**
 Begins discovering readers based on the given discovery configuration.

 When `discoverReaders` is called, the terminal begins scanning for readers using
 the settings in the given `SCPDiscoveryConfiguration`. You must implement
 `SCPDiscoveryDelegate` to get notified of discovered readers and display
 discovery results to your user.

 You must call `connectBluetoothReader` or `connectInternetReader` while
 a discovery is taking place. You can only connect to a reader that was
 returned from the `SCPDiscoveryDelegate`'s `didUpdateDiscoveredReaders` method.

 The discovery process will stop on its own when the terminal successfully
 connects to a reader, if the command is canceled, or if a discovery error occurs.

 @see https://stripe.com/docs/terminal/readers/connecting

 @param configuration   The configuration for reader discovery.
 @param delegate        Your delegate for reader discovery.
 @param completion      The completion block called when the command completes.
 */
- (SCPCancelable *)discoverReaders:(id<SCPDiscoveryConfiguration>)configuration
                          delegate:(id<SCPDiscoveryDelegate>)delegate
                        completion:(SCPErrorCompletionBlock)completion NS_SWIFT_NAME(discoverReaders(_:delegate:completion:));

/**
 Attempts to connect to the given Bluetooth reader with a given connection
 configuration.

 To connect to a Bluetooth reader, your app must register that reader to a
 [Location](https://stripe.com/docs/api/terminal/locations/object) upon connection.
 You should create a `SCPBluetoothConnectionConfiguration`
 at some point before connecting which specifies the location to which this
 reader belongs.

 Throughout the lifetime of the connection, the reader will communicate
 with your app via the `SCPBluetoothReaderDelegate` to announce transaction
 status, battery level, and software update information.

 If the connection succeeds, the completion block will be called with the
 connected reader, and `SCPTerminal.connectionStatus` will change to `.connected`.

 If the connection fails, the completion block will be called with an error.

 The SDK must be actively discovering readers in order to connect to one.
 The discovery process will stop if this connection request succeeds, otherwise
 the SDK will continue discovering.

 When this method is called, the SDK uses a connection token and the given
 reader information to register the reader to your Stripe account. If the SDK
 does not already have a connection token, it will call the `fetchConnectionToken`
 method in your `SCPConnectionTokenProvider` implementation.

 If the reader's battery is critically low the connect call will fail with
 `SCPErrorBluetoothDisconnected`. Plug your reader in to start charging and
 try again.

 @see https://stripe.com/docs/terminal/readers/connecting

 @param reader          The reader to connect to. This should be a reader
 recently returned to the `didUpdateDiscoveredReaders:` method in the discovery delegate.
 @param delegate        The delegate used during the lifetime of the connection.
 See `SCPBluetoothReaderDelegate`.
 @param connectionConfig   The connection configuration for options while
 connecting to a reader. See `SCPBluetoothConnectionConfiguration` for more details.
 @param completion      The completion block called when the command completes.
 */
- (void)connectBluetoothReader:(SCPReader *)reader
                      delegate:(id<SCPBluetoothReaderDelegate>)delegate
              connectionConfig:(SCPBluetoothConnectionConfiguration *)connectionConfig
                    completion:(SCPReaderCompletionBlock)completion NS_SWIFT_NAME(connectBluetoothReader(_:delegate:connectionConfig:completion:));

/**
 Attempts to connect to the given Internet reader with a given connection
 configuration.

 If the connect succeeds, the completion block will be called with the
 connected reader, and `SCPTerminal.connectionStatus` will change to `.connected`.

 If the connect fails, the completion block will be called with an error.

 The SDK must be actively discovering readers in order to connect to one.
 The discovery process will stop if this connection request succeeds, otherwise
 the SDK will continue discovering.

 When this method is called, the SDK uses a connection token and the given
 reader information to create a reader session. If the SDK does not already
 have a connection token, it will call the `fetchConnectionToken method you
 defined to fetch one.

 If `connectionConfig` is set to `nil`, the SDK will resort to
 default connection behavior; see the `SCPInternetConnectionConfiguration`
 header documentation for more details.

 @see https://stripe.com/docs/terminal/readers/connecting

 @param reader          The reader to connect to. This should be a reader
 recently returned to the `didUpdateDiscoveredReaders:` method in the discovery delegate.
 @param connectionConfig   The connection configuration for options while
 connecting to a reader. See `SCPInternetConnectionConfiguration` for more details.
 @param completion      The completion block called when the command completes.
 */
- (void)connectInternetReader:(SCPReader *)reader
             connectionConfig:(nullable SCPInternetConnectionConfiguration *)connectionConfig
                   completion:(SCPReaderCompletionBlock)completion NS_SWIFT_NAME(connectInternetReader(_:connectionConfig:completion:));

/**
 Attempts to connect to the given Local Mobile reader with a given
 connection configuration.

 To connect to a Local Mobile reader, your app must register that reader to a
 [Location](https://stripe.com/docs/api/terminal/locations/object) upon connection.
 You should create a `SCPLocalMobileConnectionConfiguration`
before connecting which specifies the location to which this
 reader belongs.

 Throughout the lifetime of the connection, the reader will communicate
 with your app via the `SCPLocalMobileReaderDelegate` as appropriate.

 If the connection succeeds, the completion block will be called with the
 connected reader, and `SCPTerminal.connectionStatus` will change to `.connected`.

 If the connection fails, the completion block will be called with an error.

 The SDK must be actively discovering readers in order to connect to one.
 The discovery process will stop if this connection request succeeds, otherwise
 the SDK will continue discovering.

 When this method is called, the SDK uses a connection token and the given
 reader information to register the reader to your Stripe account. If the SDK
 does not already have a connection token, it will call the `fetchConnectionToken`
 method in your `SCPConnectionTokenProvider` implementation.

 Note that during connection, an update may occur to ensure that the
 local mobile reader has the most up to date software and configurations.

 @see https://stripe.com/docs/terminal/readers/connecting

 @param reader           The reader to connect to. This should be a reader
                         recently returned to the `didUpdateDiscoveredReaders:` method in
                         the discovery delegate.
 @param delegate         The delegate used during the lifetime of the connection.
                         See `SCPLocalMobileReaderDelegate`.
 @param connectionConfig The connection configuration for options while
                         connecting to a reader.
                         See `SCPLocalMobileConnectionConfiguration` for more details.
 @param completion       The completion block called when the command completes.
 */
- (void)connectLocalMobileReader:(SCPReader *)reader
                        delegate:(id<SCPLocalMobileReaderDelegate>)delegate
                connectionConfig:(SCPLocalMobileConnectionConfiguration *)connectionConfig
                      completion:(SCPReaderCompletionBlock)completion
    NS_SWIFT_NAME(connectLocalMobileReader(_:delegate:connectionConfig:completion:));

#ifdef SCP_USB_ENABLED
/**
 Attempts to connect to the given USB reader with a given connection
 configuration.

 To connect to a USB reader, your app must register that reader to a
 [Location](https://stripe.com/docs/api/terminal/locations/object) upon connection.
 You should create a `SCPUsbConnectionConfiguration`
 at some point before connecting which specifies the location to which this
 reader belongs.

 Throughout the lifetime of the connection, the reader will communicate
 with your app via the `SCPReaderDelegate` to announce transaction
 status, battery level, and software update information.

 If the connection succeeds, the completion block will be called with the
 connected reader, and `SCPTerminal.connectionStatus` will change to `.connected`.

 If the connection fails, the completion block will be called with an error.

 The SDK must be actively discovering readers in order to connect to one.
 The discovery process will stop if this connection request succeeds, otherwise
 the SDK will continue discovering.

 When this method is called, the SDK uses a connection token and the given
 reader information to register the reader to your Stripe account. If the SDK
 does not already have a connection token, it will call the `fetchConnectionToken`
 method in your `SCPConnectionTokenProvider` implementation.

 @see https://stripe.com/docs/terminal/readers/connecting

 @param reader          The reader to connect to. This should be a reader
 recently returned to the `didUpdateDiscoveredReaders:` method in the discovery delegate.
 @param delegate        The delegate used during the lifetime of the connection.
 See `SCPBluetoothReaderDelegate`.
 @param connectionConfig   The connection configuration for options while
 connecting to a reader. See `SCPBluetoothConnectionConfiguration` for more details.
 @param completion      The completion block called when the command completes.
 */
- (void)connectUsbReader:(SCPReader *)reader
                delegate:(id<SCPUsbReaderDelegate>)delegate
        connectionConfig:(SCPUsbConnectionConfiguration *)connectionConfig
              completion:(SCPReaderCompletionBlock)completion NS_SWIFT_NAME(connectUsbReader(_:delegate:connectionConfig:completion:));
#endif // SCP_USB_ENABLED

/**
 Retrieves a list of `SCPLocation` objects belonging to your merchant. You must specify
 the ID of one of these locations to register the reader to while connecting to a Bluetooth reader.

 @see https://stripe.com/docs/terminal/readers/fleet-management#bluetooth-readers

 @param parameters The optional parameters to pass to the [List all Locations](https://stripe.com/docs/api/terminal/locations/list) API endpoint. Pass `nil` to use the default parameters.
 @param completion The completion block called when the command completes.
 */
- (void)listLocations:(nullable SCPListLocationsParameters *)parameters
           completion:(SCPLocationsCompletionBlock)completion NS_SWIFT_NAME(listLocations(parameters:completion:));

/**
 Installs the available update for the connected reader.

 Stripe Terminal reader updates will either be updated automatically upon connection,
 or announced as available but not automatically installed. When the Stripe Terminal
 SDK announces an optional update, you can present that update to your app's user
 and let them decide when to perform that update. When your user chooses to perform
 a reader update, call this method to start the installation.

 In your app you should display the progress of the update to the user.
 You should also instruct the user to wait for the update to complete:
 "Do not leave this page, and keep the reader in range and powered on until
 the update is complete." You can set `UIApplication.shared.isIdleTimerDisabled`
 to true while the update is being installed to prevent the device from automatically
 locking.

 If an error occurs while installing the update (e.g. because the update was
 interrupted), the `SCPBluetoothReaderDelegate` will receive
 `reader:didFinishInstallingUpdate:error:` with the error. If the update
 completed successfully, the same method will be called with `nil` error.

 You must implement the ability to update your reader's software in your app.
 Though we expect required software updates to be very rare, by using Stripe
 Terminal, you are obligated to include this functionality.

 @note It is an error to call this method when the SDK is connected to the Verifone
 P400 or WisePOS E readers.

 @see https://stripe.com/docs/terminal/readers/bbpos-chipper2xbt#updating-reader-software
 @see https://stripe.com/docs/terminal/readers/bbpos-wisepad3#updating-reader-software
 */
- (void)installAvailableUpdate;

/**
 Reboots the connected reader.

 If the reboot succeeds, the completion block is called with `nil`. If the
 reboot fails, the completion block is called with an error.

 @note: This method is only available for Bluetooth readers.

 @see https://stripe.com/docs/terminal/readers/connecting

 @param completion      The completion block called when the command completes.
 */
- (void)rebootReader:(SCPErrorCompletionBlock)completion NS_SWIFT_NAME(rebootReader(_:));

/**
 Attempts to disconnect from the currently connected reader.

 If the disconnect succeeds, the completion block is called with `nil`. If the
 disconnect fails, the completion block is called with an error.

 @see https://stripe.com/docs/terminal/readers/connecting

 @param completion      The completion block called when the command completes.
 */
- (void)disconnectReader:(SCPErrorCompletionBlock)completion NS_SWIFT_NAME(disconnectReader(_:));

#pragma mark Taking payments

/**
 Creates a new `SCPPaymentIntent` with the given parameters.

 Note: If the information required to create a PaymentIntent isn't readily
 available in your app, you can create the PaymentIntent on your server and use
 the `retrievePaymentIntent` method to retrieve the PaymentIntent in your app.

     @note This cannot be used with the Verifone P400. If used with the
     Verifone P400, the completion handler will be called with
     an SCPErrorFeatureNotAvailableWithConnectedReader error.

 @see https://stripe.com/docs/terminal/payments#create

 @param parameters      The parameters for the PaymentIntent to be created.
 @param completion      The completion block called when the command completes.
 */
- (void)createPaymentIntent:(SCPPaymentIntentParameters *)parameters
                 completion:(SCPPaymentIntentCompletionBlock)completion NS_SWIFT_NAME(createPaymentIntent(_:completion:));

/**
 Retrieves a `SCPPaymentIntent` with a client secret.

 If the information required to create a PaymentIntent isn't readily available
 in your app, you can create the PaymentIntent on your server and use this
 method to retrieve the PaymentIntent in your app.

 @see https://stripe.com/docs/terminal/payments#create

 @param clientSecret    The client secret of the PaymentIntent to be retrieved.
 @param completion      The completion block called when the command completes.
 */
- (void)retrievePaymentIntent:(NSString *)clientSecret
                   completion:(SCPPaymentIntentCompletionBlock)completion NS_SWIFT_NAME(retrievePaymentIntent(clientSecret:completion:));

/**
 Collects a payment method for the given `SCPPaymentIntent`.

 Note: `collectPaymentMethod` does not apply any changes to the PaymentIntent
 API object. Updates to the PaymentIntent are local to the SDK, and persisted
 in-memory.

 If collecting a payment method fails, the completion block will be called with
 an error. After resolving the error, you may call `collectPaymentMethod` again
 to either try the same card again, or try a different card.

 If collecting a payment method succeeds, the completion block will be called
 with a PaymentIntent with status `.requiresConfirmation`, indicating that you
 should call `confirmPaymentIntent:completion:` to finish the payment.

 Note that if `collectPaymentMethod` is canceled, the completion block will be
 called with a `Canceled` error.

 @see https://stripe.com/docs/terminal/payments#collect

 @param paymentIntent       The PaymentIntent to collect a payment method for.
 @param completion          The completion block called when the command completes.
 */
- (nullable SCPCancelable *)collectPaymentMethod:(SCPPaymentIntent *)paymentIntent
                                      completion:(SCPPaymentIntentCompletionBlock)completion NS_SWIFT_NAME(collectPaymentMethod(_:completion:));

/**
 Collects a payment method for the given `PaymentIntent`, with the specified configuration.

 Note: `collectPaymentMethod` does not apply any changes to the PaymentIntent
 API object. Updates to the PaymentIntent are local to the SDK, and persisted
 in-memory.

 @param paymentIntent       The PaymentIntent to collect a payment method for.
 @param collectConfig   The CollectConfiguration object that contains settings for this call.
 @param completion          The completion block called when the command completes.
 */
- (nullable SCPCancelable *)collectPaymentMethod:(SCPPaymentIntent *)paymentIntent
                                   collectConfig:(nullable SCPCollectConfiguration *)collectConfig
                                      completion:(SCPPaymentIntentCompletionBlock)completion;

/**
 Confirm a payment after collecting a payment method succeeds.

 Synchronous capture
 -------------------

 Stripe Terminal uses two-step card payments to prevent unintended and duplicate
 payments. When `confirmPaymentIntent` completes successfully, a charge has been
 authorized on the customer's card, but not yet been "captured". Your app must
 **synchronously notify your backend** to capture the PaymentIntent
 in order to settle the funds to your account.

 Handling failures
 -----------------

 When `confirmPaymentIntent` fails, the SDK returns an error that includes the
 updated `SCPPaymentIntent`. Your app should inspect the updated PaymentIntent
 to decide how to retry the payment.

 1. If the updated PaymentIntent is `nil`, the request to Stripe's servers timed
 out and the PaymentIntent's status is unknown. We recommend that you retry
 `confirmPaymentIntent` with the original PaymentIntent. If you instead choose to
 abandon the original PaymentIntent and create a new one, **do not capture**
 the original PaymentIntent. If you do, you might charge your customer twice.

 2. If the updated PaymentIntent's status is still `.requiresConfirmation` (e.g.,
 the request failed because your app is not connected to the internet), you
 can call `confirmPaymentIntent` again with the updated PaymentIntent to retry
 the request.

 3. If the updated PaymentIntent's status changes to `.requiresPaymentMethod` (e.g., the
 request failed because the card was declined), call `collectPaymentMethod` with the
 updated PaymentIntent to try charging another card.

 @see https://stripe.com/docs/terminal/payments#process

 @param paymentIntent   The PaymentIntent to confirm.
 @param completion      The completion block called when the confirm completes.
 */
- (void)confirmPaymentIntent:(SCPPaymentIntent *)paymentIntent
                  completion:(SCPConfirmPaymentIntentCompletionBlock)completion NS_SWIFT_NAME(confirmPaymentIntent(_:completion:));

/**
 Cancels an `SCPPaymentIntent`.

 If the cancel request succeeds, the completion block will be called with the
 updated PaymentIntent object with status Canceled. If the cancel request
 fails, the completion block will be called with an error.

 @note This cannot be used with the Verifone P400 reader.  If used with the
 Verifone P400, the completion handler will be called with
 an `SCPErrorFeatureNotAvailableWithConnectedReader` error.

 @see https://stripe.com/docs/terminal/payments/refunds

 @param paymentIntent     The PaymentIntent to cancel.
 @param completion        The completion block called when the cancel completes.
 */
- (void)cancelPaymentIntent:(SCPPaymentIntent *)paymentIntent
                 completion:(SCPPaymentIntentCompletionBlock)completion NS_SWIFT_NAME(cancelPaymentIntent(_:completion:));

#pragma mark Saving payment details for later use

/**
 Creates a new `SCPSetupIntent` with the given parameters.

 @see https://stripe.com/docs/api/setup_intents/create

 @param setupIntentParams   The parameters that control the creation of the SetupIntent.
 @param completion          The completion block called when the command completes.
 */
- (void)createSetupIntent:(SCPSetupIntentParameters *)setupIntentParams
               completion:(SCPSetupIntentCompletionBlock)completion NS_SWIFT_NAME(createSetupIntent(_:completion:));

/**
 Retrieves an `SCPSetupIntent` with a client secret.

 If you've created a SetupIntent on your backend, you must retrieve it in the
 Stripe Terminal SDK before calling `collectSetupIntentPaymentMethod`.

 @param clientSecret    The client secret of the SetupIntent to be retrieved.
 @param completion      The completion block called when the command completes.
 */
- (void)retrieveSetupIntent:(NSString *)clientSecret
                 completion:(SCPSetupIntentCompletionBlock)completion NS_SWIFT_NAME(retrieveSetupIntent(clientSecret:completion:));

/**
 Cancels an `SCPPaymentIntent`.

 If the cancel request succeeds, the completion block will be called with the
 updated PaymentIntent object with status Canceled. If the cancel request
 fails, the completion block will be called with an error.

 @see https://stripe.com/docs/api/setup_intents/cancel

 @param intent      The SetupIntent to cancel.
 @param completion  The completion block called when cancellation completes.
 */
- (void)cancelSetupIntent:(SCPSetupIntent *)intent
               completion:(SCPSetupIntentCompletionBlock)completion NS_SWIFT_NAME(cancelSetupIntent(_:completion:));

/**
 Collects a payment method for the given `SCPSetupIntent`.

 This method does not update the SetupIntent API object. All updates are local
 to the SDK and only persisted in memory. You must confirm the SetupIntent to
 create a PaymentMethod API object and (optionally) attach that PaymentMethod
 to a customer.

 If collecting a payment method fails, the completion block will be called with
 an error. After resolving the error, you may call `collectSetupIntentPaymentMethod`
 again to either try the same card again, or try a different card.

 If collecting a payment method succeeds, the completion block will be called
 with a SetupIntent with status `.requiresConfirmation`, indicating that you
 should call `confirmSetupIntent:customerConsentCollected:completion:` to
 finish the payment.

 Note that if `collectSetupIntentPaymentMethod` is canceled, the completion
 block will be called with a `Canceled` error.

 Collecting cardholder consent
 -----------------------------

 Card networks require that you collect consent from the customer before saving
 and reusing their card information. The SetupIntent confirmation API method
 normally takes a `mandate_data` hash that lets you specify details about the
 customer's consent. The Stripe Terminal SDK will fill in the `mandate_data`
 hash with relevant information, but in order for it to do so, you must specify
 whether you have gathered consent from the cardholder to collect their payment
 information in this method's second parameter.

 The payment method will not be collected without the cardholder's consent.

 @param setupIntent     The SetupIntent to which payment method information is attached.
 @param customerConsentCollected    A boolean that should be set to true if you
 have successfully collected consent from the cardholder to save their payment information.
 @param completion      The completion block called when collection completes.
 */
- (nullable SCPCancelable *)collectSetupIntentPaymentMethod:(SCPSetupIntent *)setupIntent
                                   customerConsentCollected:(BOOL)customerConsentCollected
                                                 completion:(SCPSetupIntentCompletionBlock)completion NS_SWIFT_NAME(collectSetupIntentPaymentMethod(_:customerConsentCollected:completion:));

/**
 Collects a payment method for the given `SCPSetupIntent`.

 This method does not update the SetupIntent API object. All updates are local
 to the SDK and only persisted in memory. You must confirm the SetupIntent to
 create a PaymentMethod API object and (optionally) attach that PaymentMethod
 to a customer.

 If collecting a payment method fails, the completion block will be called with
 an error. After resolving the error, you may call `collectSetupIntentPaymentMethod`
 again to either try the same card again, or try a different card.

 If collecting a payment method succeeds, the completion block will be called
 with a SetupIntent with status `.requiresConfirmation`, indicating that you
 should call `confirmSetupIntent:customerConsentCollected:completion:` to
 finish the payment.

 Note that if `collectSetupIntentPaymentMethod` is canceled, the completion
 block will be called with a `Canceled` error.

 Collecting cardholder consent
 -----------------------------

 Card networks require that you collect consent from the customer before saving
 and reusing their card information. The SetupIntent confirmation API method
 normally takes a `mandate_data` hash that lets you specify details about the
 customer's consent. The Stripe Terminal SDK will fill in the `mandate_data`
 hash with relevant information, but in order for it to do so, you must specify
 whether you have gathered consent from the cardholder to collect their payment
 information in this method's second parameter.

 The payment method will not be collected without the cardholder's consent.

 @param setupIntent     The SetupIntent to which payment method information is attached.
 @param customerConsentCollected    A boolean that should be set to true if you
 have successfully collected consent from the cardholder to save their payment information.
 @param setupConfig     An optional SCPSetupIntentConfiguration to configure per-setup overrides.
 @param completion      The completion block called when collection completes.
 */
- (nullable SCPCancelable *)collectSetupIntentPaymentMethod:(SCPSetupIntent *)setupIntent
                                   customerConsentCollected:(BOOL)customerConsentCollected
                                                setupConfig:(nullable SCPSetupIntentConfiguration *)setupConfig
                                                 completion:(SCPSetupIntentCompletionBlock)completion NS_SWIFT_NAME(collectSetupIntentPaymentMethod(_:customerConsentCollected:setupConfig:completion:));

/**
 Confirms a SetupIntent after the payment method has been successfully collected.

 Handling failures
 -----------------

 When `confirmSetupIntent` fails, the SDK returns an error that includes the
 updated `SCPSetupIntent`. Your app should inspect the updated SetupIntent
 to decide how to proceed.

 1. If the updated SetupIntent is `nil`, the request to Stripe's servers timed
 out and the SetupIntent's status is unknown. We recommend that you retry
 `confirmSetupIntent` with the original SetupIntent.

 2. If the updated SetupIntent's status is still `.requiresConfirmation` (e.g.,
 the request failed because your app is not connected to the internet), you
 can call `confirmSetupIntent` again with the updated SetupIntent to retry
 the request.

 3. If the updated SetupIntent's status is `.requiresAction`, there might be
 authentication the cardholder must perform offline before the saved
 PaymentMethod can be used.

 @see https://stripe.com/docs/api/setup_intents/confirm

 @param setupIntent     The SetupIntent to confirm
 @param completion                  The completion block called when the confirmation completes
 */
- (void)confirmSetupIntent:(SCPSetupIntent *)setupIntent
                completion:(SCPConfirmSetupIntentCompletionBlock)completion NS_SWIFT_NAME(confirmSetupIntent(_:completion:));

#pragma mark Card-present refunds

/**
 Initiates an in-person refund with a given set of `SCPRefundParameters` by
 collecting the payment method that is to be refunded.

 Some payment methods, like Interac Debit payments, require that in-person payments
 also be refunded while the cardholder is present. The cardholder must present
 the Interac card to the card reader; these payments cannot be refunded via the
 dashboard or the API.

 For payment methods that don't require the cardholder be present, see
 https://stripe.com/docs/terminal/payments/refunds

 This method, along with `confirmRefund`, allow you to design an in-person refund
 flow into your app.

 If collecting a payment method fails, the completion block will be called with
 an error. After resolving the error, you may call `collectRefundPaymentMethod`
 again to either try the same card again, or try a different card.

 If collecting a payment method succeeds, the completion block will be called
 with an `nil` error. At that point, you can call `confirmRefund` to finish
 refunding the payment method.

 Calling any other SDK methods between `collectRefundPaymentMethod` and
 `confirmRefund` will result in undefined behavior.

 Note that if `collectRefundPaymentMethod` is canceled, the completion block
 will be called with a `Canceled` error.

 @see https://stripe.com/docs/terminal/canada#interac-refunds

 @param refundParams  The SCPRefundParameters object that describes how the
 refund will be created.
 @param completion  The completion block called when the command completes.
 */
- (nullable SCPCancelable *)collectRefundPaymentMethod:(SCPRefundParameters *)refundParams
                                            completion:(SCPErrorCompletionBlock)completion
    NS_SWIFT_NAME(collectRefundPaymentMethod(_:completion:));

/**
 Initiates an in-person refund with a given set of `SCPRefundParameters` by
 collecting the payment method that is to be refunded.

 Some payment methods, like Interac Debit payments, require that in-person payments
 also be refunded while the cardholder is present. The cardholder must present
 the Interac card to the card reader; these payments cannot be refunded via the
 dashboard or the API.

 For payment methods that don't require the cardholder be present, see
 https://stripe.com/docs/terminal/payments/refunds

 This method, along with `confirmRefund`, allow you to design an in-person refund
 flow into your app.

 If collecting a payment method fails, the completion block will be called with
 an error. After resolving the error, you may call `collectRefundPaymentMethod`
 again to either try the same card again, or try a different card.

 If collecting a payment method succeeds, the completion block will be called
 with an `nil` error. At that point, you can call `confirmRefund` to finish
 refunding the payment method.

 Calling any other SDK methods between `collectRefundPaymentMethod` and
 `confirmRefund` will result in undefined behavior.

 Note that if `collectRefundPaymentMethod` is canceled, the completion block
 will be called with a `Canceled` error.

 @see https://stripe.com/docs/terminal/canada#interac-refunds

 @param refundParams  The SCPRefundParameters object that describes how the
 refund will be created.
 @param refundConfig An optional SCPRefundConfiguration to configure per-refund overrides.
 @param completion  The completion block called when the command completes.
 */
- (nullable SCPCancelable *)collectRefundPaymentMethod:(SCPRefundParameters *)refundParams
                                          refundConfig:(nullable SCPRefundConfiguration *)refundConfig
                                            completion:(SCPErrorCompletionBlock)completion
    NS_SWIFT_NAME(collectRefundPaymentMethod(_:refundConfig:completion:));

/**
 Confirms an in-person refund after the refund payment method has been collected.

 The completion block will either be called with the successful `SCPRefund` or
 with an `SCPConfirmRefundError`.

 When `confirmRefund` fails, the SDK returns an error that either includes the
 failed `SCPRefund` or the `SCPRefundParameters` that led to a failure.
 Your app should inspect the `SCPConfirmRefundError` to decide how to proceed.

 1. If the refund property is `nil`, the request to Stripe's servers timed
 out and the refund's status is unknown. We recommend that you retry
 `confirmRefund` with the original `SCPRefundParameters`.

 2. If the `SCPConfirmRefundError` has a `failure_reason`, the refund was declined.
 We recommend that you take action based on the decline code you received.

 @note `collectRefundPaymentMethod:completion` and `confirmRefund` are only
 available for payment methods that require in-person refunds. For all other
 refunds, use the Stripe Dashboard or the Stripe API.

 @see https://stripe.com/docs/terminal/canada#interac-refunds

 @param completion  The completion block called when the command completes.
 */
- (void)confirmRefund:(SCPConfirmRefundCompletionBlock)completion NS_SWIFT_NAME(confirmRefund(completion:));

#pragma mark Offline mode

/** Set to receive offline reporting events from the SDK.
 */
@property (nonatomic, nullable, readwrite) id<SCPOfflineDelegate> offlineDelegate;

/**
 The offline-related statistics and status for both the SDK and any connected smart reader.
 */
@property (nonatomic, readonly) SCPOfflineStatus *offlineStatus;

/**
 Creates a new `SCPPaymentIntent` with the given parameters.

 Note: If the information required to create a PaymentIntent isn't readily
 available in your app, you can create the PaymentIntent on your server and use
 the `retrievePaymentIntent` method to retrieve the PaymentIntent in your app.

     @note This cannot be used with the Verifone P400. If used with the
     Verifone P400, the completion handler will be called with
     an SCPErrorFeatureNotAvailableWithConnectedReader error.

 @see https://stripe.com/docs/terminal/payments#create

 @param parameters      The parameters for the PaymentIntent to be created.
 @param createConfig    Optional configuration overrides used when creating this payment intent.
 @param completion      The completion block called when the command completes.
 */
- (void)createPaymentIntent:(SCPPaymentIntentParameters *)parameters
               createConfig:(nullable SCPCreateConfiguration *)createConfig
                 completion:(SCPPaymentIntentCompletionBlock)completion NS_SWIFT_NAME(createPaymentIntent(_:createConfig:completion:));

#pragma mark Displaying information to customers

/**
 Clears the reader display and resets it to the splash screen.

 @param completion  The completion block called when the command completes.

 @note Only available for the Verifone P400 and BBPOS WisePOS E.
 */
- (void)clearReaderDisplay:(SCPErrorCompletionBlock)completion NS_SWIFT_NAME(clearReaderDisplay(_:));

/**
 Updates the reader display with cart information.
 This method is for display purposes only and has no correlation with what the customer is
 actually charged. Tax and total are also not automatically calculated and must be set in SCPCart.

 @param cart  The cart containing the information that will be displayed.
 @param completion  The completion block called when the command completes.

 @note Only available for the Verifone P400 and BBPOS WisePOS E.
 */
- (void)setReaderDisplay:(SCPCart *)cart
              completion:(SCPErrorCompletionBlock)completion
    NS_SWIFT_NAME(setReaderDisplay(_:completion:));

/**
 Configures settings on the connected reader.

 @param params The `SCPReaderSettingsParameters` instance with the values to set on the reader.
 @param completion The `SCPReaderSettingsCompletionBlock` to be called when the operation completes.
 */
- (void)setReaderSettings:(id<SCPReaderSettingsParameters>)params
               completion:(SCPReaderSettingsCompletionBlock)completion
    NS_SWIFT_NAME(setReaderSettings(_:completion:));

/**
 Retrieves the current settings from the connected reader.

 @param completion The `SCPReaderSettingsCompletionBlock` to be called when the operation completes.
 */
- (void)retrieveReaderSettings:(SCPReaderSettingsCompletionBlock)completion
    NS_SWIFT_NAME(retrieveReaderSettings(_:));

/**
 Displays forms and collects information from customers. Available for BBPOS WisePOS E and Stripe S700.

 @param collectInputsParams  parameters to configure forms
 @param completion  The completion block called when the command completes.

 @see https://stripe.com/docs/terminal/features/collect-inputs

 */
- (nullable SCPCancelable *)collectInputs:(SCPCollectInputsParameters *)collectInputsParams
                               completion:(SCPCollectInputsCompletionBlock)completion
    NS_SWIFT_NAME(collectInputs(_:completion:));

/**
 Returns an unlocalized string for the given reader input options, e.g.
 "Swipe / Insert"
 */
+ (NSString *)stringFromReaderInputOptions:(SCPReaderInputOptions)options NS_SWIFT_NAME(stringFromReaderInputOptions(_:));

/**
 Returns an unlocalized string for the given reader display message, e.g.
 "Retry Card"
 */
+ (NSString *)stringFromReaderDisplayMessage:(SCPReaderDisplayMessage)message NS_SWIFT_NAME(stringFromReaderDisplayMessage(_:));

/**
 Returns an unlocalized string for the given reader event, e.g.
 "Card Inserted"
 */
+ (NSString *)stringFromReaderEvent:(SCPReaderEvent)event NS_SWIFT_NAME(stringFromReaderEvent(_:));

/**
 Returns an unlocalized string for the given connection status, e.g.
 "Connecting"
 */
+ (NSString *)stringFromConnectionStatus:(SCPConnectionStatus)status NS_SWIFT_NAME(stringFromConnectionStatus(_:));

/**
 Returns an unlocalized string for the given payment status, e.g.
 "Not Ready"
 */
+ (NSString *)stringFromPaymentStatus:(SCPPaymentStatus)status NS_SWIFT_NAME(stringFromPaymentStatus(_:));

/**
 Returns an unlocalized string for the given device type.
 */
+ (NSString *)stringFromDeviceType:(SCPDeviceType)deviceType NS_SWIFT_NAME(stringFromDeviceType(_:));

/**
 Returns an unlocalized string for the given discovery method.
 */
+ (NSString *)stringFromDiscoveryMethod:(SCPDiscoveryMethod)method NS_SWIFT_NAME(stringFromDiscoveryMethod(_:));

/**
 Returns an unlocalized string for the given card brand.
 */
+ (NSString *)stringFromCardBrand:(SCPCardBrand)cardBrand NS_SWIFT_NAME(stringFromCardBrand(_:));

/**
 Returns an unlocalized string for the given payment intent status.
 */
+ (NSString *)stringFromPaymentIntentStatus:(SCPPaymentIntentStatus)paymentIntentStatus NS_SWIFT_NAME(stringFromPaymentIntentStatus(_:));

/**
 Returns an unlocalized string for the given capture method.
 */
+ (NSString *)stringFromCaptureMethod:(SCPCaptureMethod)captureMethod NS_SWIFT_NAME(stringFromCaptureMethod(_:));

/**
 Returns an unlocalized string for the given read method.
 */
+ (NSString *)stringFromReadMethod:(SCPReadMethod)method NS_SWIFT_NAME(stringFromReadMethod(_:));

/**
 Returns an unlocalized string for the given network status, e.g. "Online"
 */
+ (NSString *)stringFromNetworkStatus:(SCPNetworkStatus)networkStatus NS_SWIFT_NAME(stringFromNetworkStatus(_:));

/**
 Returns an unlocalized string for the given disconnect reason, e.g. "Reboot requested"
 */
+ (NSString *)stringFromDisconnectReason:(SCPDisconnectReason)reason NS_SWIFT_NAME(stringFromDisconnectReason(_:));

/**
 Returns an unlocalized string for the given offline behavior.
 */
+ (NSString *)stringFromOfflineBehavior:(SCPOfflineBehavior)behavior NS_SWIFT_NAME(stringFromOfflineBehavior(_:));

/**
 Use `initWithConfiguration:tokenProvider:delegate:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithConfiguration:tokenProvider:delegate:`
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
