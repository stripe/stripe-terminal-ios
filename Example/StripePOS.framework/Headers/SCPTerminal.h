//
//  SCPTerminal.h
//  StripePOS
//
//  Created by Ben Guo on 7/28/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SCPReadCardDelegate.h"
#import "SCPBlocks.h"
#import "SCPPaymentStatus.h"

NS_ASSUME_NONNULL_BEGIN

/**
 The possible read types for attachSource and readSource.
 */
typedef NS_ENUM(NSUInteger, SCPSourceReadType) {
    /**
     Read a card using any of the entry methods supported on the connected
     reader.
     */
    SCPSourceReadTypeCard,
};

/**
 The current version of this library.
 */
static NSString *const SCPSDKVersion = @"0.9";

@class SCPCancelable, SCPDiscoveryConfiguration, SCPTerminalConfiguration, SCPPaymentParameters, SCPReadSourceParameters;

@protocol SCPActivationTokenProvider, SCPTerminalDelegate, SCPDiscoveryDelegate, SCPUpdateReaderDelegate;

/**
 The Point of Sale SDK is modeled as a set of commands you can issue to an
 instance of SCPTerminal. These commands let you discover card readers, connect
 to a specific reader, and initiate actions on the reader.

 Asynchronous commands end with a completion parameter, called after the command
 completes with the result of the command.

 If the asynchronous command can be canceled, the command will return an
 optional `SCPCancelable` object. If this object is non-nil, the command was
 successfully started. You can request to stop the command by calling `cancel`
 on the returned object.
 */
@interface SCPTerminal : NSObject

/**
 The terminal's delegate. @see SCPTerminalDelegate
 */
@property (nonatomic, weak, readwrite) id<SCPTerminalDelegate> terminalDelegate;

/**
 The configuration used to initialize the terminal.
 */
@property (nonatomic, readonly) SCPTerminalConfiguration *configuration;

/**
 Information about the connected reader, or nil if no reader is connected.
 */
@property (nonatomic, nullable, readonly) SCPReader *connectedReader;

/**
 The terminal's current connection status.
 */
@property (nonatomic, readonly) SCPConnectionStatus connectionStatus;

/**
 The terminal's current payment status.
 */
@property (nonatomic, readonly) SCPPaymentStatus paymentStatus;

/**
 Initializes `SCPTerminal` with the given configuration, activation token
 provider, and delegate. We suggest making your application's API client
 conform to `SCPActivationTokenProvider`.

 For more information on preparing up your backend, refer to our docs at
 https://stripe.com/docs/point-of-sale

 @param configuration           The configuration for the terminal.

 @param tokenProvider           Your activation token provider. @see SCPActivationTokenProvider

 @param delegate                The terminal's delegate. You must provide a
 TerminalDelegate to respond to updates from the terminal instance.
 */
- (instancetype)initWithConfiguration:(SCPTerminalConfiguration *)configuration
                        tokenProvider:(id<SCPActivationTokenProvider>)tokenProvider
                             delegate:(id<SCPTerminalDelegate>)delegate;

/**
 Begins discovering readers matching the given configuration.

 When `discover` is called, `SCPTerminal` begins scanning for readers using
 the settings in the given `SCPDiscoveryConfiguration`. You must implement
 `SCPDiscoveryDelegate` to handle displaying discovery results to your user and
 connecting to a selected reader.

 This command can be canceled, and returns an optional `SCPCancelable` object.
 If the returned object is nil, discovery did not start. To request that the
 command stop, call `cancel` on the returned `SCPCancelable` object.

 The discovery process will stop on its own when the `connect` method is
 successfully called, or if an error occurs (e.g. Bluetooth is disabled on the
 POS device). To end discovery after a specified time interval, set the
 `timeout` property on `SCPDiscoveryConfiguration`.

 @param configuration   The configuration for reader discovery.
 @param delegate        Your delegate for reader discovery.
 @param completion      The completion block called when the command completes.
 */
- (nullable SCPCancelable *)discover:(SCPDiscoveryConfiguration *)configuration
                            delegate:(id<SCPDiscoveryDelegate>)delegate
                          completion:(SCPErrorCompletionBlock)completion;

/**
 When `connect` is called, `SCPTerminal` attempts to connect to the specified
 reader. If the connect succeeds, the completion block will be called
 with an updated `SCPReader` object and `connectionStatus` will change to
 `Connected`. If the connect fails, the completion block will be called with
 an error.

 @param reader          The reader to connect to. This should be a reader
 recently returned to the `terminal:didUpdateDiscoveryResults:` method.
 @param completion      The completion block called when the command completes.
 */
- (void)connect:(SCPReader *)reader completion:(SCPReaderCompletionBlock)completion;

/**
 When `disconnect` is called, `SCPTerminal` attempts to disconnect from any
 currently connected reader. If the disconnect succeeds, the completion block
 is called with nil. If the disconnect fails, the completion block is called
 with an error.

 @param completion      The completion block called when the command completes.
 */
- (void)disconnect:(SCPErrorCompletionBlock)completion;

/**
 Creates a new PaymentIntent with the given parameters.

 @param params          The parameters for the payment intent.
 @param completion      The completion block called when the command completes.
 */
- (void)createPaymentIntent:(SCPPaymentParameters *)params
                 completion:(SCPPaymentIntentCompletionBlock)completion;

/**
 Attaches a source to the given payment intent.

 This command can be canceled, and returns a nullable `SCPCancelable` object.
 If the returned object is nil, the attach source command did not start. To
 request that the command stop, call `cancel` on the returned `SCPCancelable`
 object.

 If attaching a source fails, the completion block will be called with an
 AttachSourceError. After resolving the error, you should call attachSource
 again to either try the same card again, or try a different card. The error's
 paymentIntent object will have a RequiresSource, indicating you should call
 attachSource again to try to read another card.

 If attaching a source succeeds, the completion block will be called with a
 PaymentIntent with status RequiresConfirmation, indicating that you should
 call confirmPaymentIntent to finish the payment.

 @param intent      The payment intent to attach a source to.
 @param delegate    Your delegate for handling read card events.
 @param completion  The completion block called when the command completes.
 */
- (nullable SCPCancelable *)attachSource:(SCPPaymentIntent *)intent
                        readCardDelegate:(id<SCPReadCardDelegate>)delegate
                              completion:(SCPPaymentIntentCompletionBlock)completion;

/**
 Confirms a payment intent. You should call this immediately after receiving a
 PaymentIntent with status RequiresConfirmation from `attachSource.

 If confirming the intent fails, the completion block will be called with a
 ConfirmError. You should inspect the status of the error's paymentIntent object
 to decide how to proceed:
 - RequiresSource: the source was declined. Call attachSource to try attaching
 a different source to the PaymentIntent.
 - RequiresConfirm: the confirm failed but can be retried. Inspect the error's
 code and call confirmPaymentIntent again when the underlying issue has been
 addressed.

 If confirming the intent succeeds, the completion block will be called with a
 PaymentIntent object with status RequiresCapture, indicating that a charge was
 created. You should inspect the PaymentIntent's charge property and send the
 charge's stripeId to your backend to complete the charge and fulfill the order.

 @param intent          The payment intent confirm.
 @param completion      The completion block called when the confirm completes.
 */
- (void)confirmPaymentIntent:(SCPPaymentIntent *)intent
                  completion:(SCPConfirmPaymentIntentCompletionBlock)completion;

/**
 Cancels a payment intent.

 If the cancel request succeeds, the completion block will be called with the
 updated PaymentIntent object with status Canceled. If the cancel request
 fails, the completion block will be called with an error.

 @param intent          The payment intent to cancel.
 @param completion      The completion block called when the cancel completes.
 */
- (void)cancelPaymentIntent:(SCPPaymentIntent *)intent
                 completion:(SCPPaymentIntentCompletionBlock)completion;

/**
 Reads a source with the given parameters and returns a Stripe source. Note that
 sources created using this method cannot be charged. Use `attachSource`
 and `confirmPaymentIntent` if you are collecting a payment from a customer.
 Use `readSource` if you need to read payment details without charging the
 customer.

 To cancel attaching a source, call `cancel` on the returned `SCPCancelable` object.

 If reading a source fails, the completion block will be called with a
 `NSError` containing details about the failure. If reading a source
 succeeds, the completion block will be called with a `CardPresentSource`.
 You should send the ID of the source to your backend for further processing.
 For example, you can use source's fingerprint to look up a charge created
 using the same card.

 @param parameters  The parameters for reading the source.
 @param delegate    Your delegate for handling read card events.
 @param completion  The completion block called when the command completes.
 */
- (nullable SCPCancelable *)readSource:(SCPReadSourceParameters *)parameters
                      readCardDelegate:(id<SCPReadCardDelegate>)delegate
                            completion:(SCPCardPresentSourceCompletionBlock)completion;

/**
 Checks for a reader update and prompts your app to begin installing the update.

 If an update is available, the completion block will be called with nil.
 `SCPUpdateReaderDelegate`'s  `readerUpdateAvailable:` method will be called,
 and you will have the opportunity to begin or cancel the update.

 If no update is available, or an error occurs checking for an update, the
 completion block will be called with an error.

 @param delegate    Your delegate for handling update events.
 @param completion  The completion block called when checking for an update
 completes.
 */
- (void)updateReader:(id<SCPUpdateReaderDelegate>)delegate
          completion:(SCPErrorCompletionBlock)completion;

/**
 You must first install the Stripe iOS SDK to use this method.
 @see https://stripe.com/docs/mobile/ios#getting-started

 Creates a card source using the contents of STPPaymentCardTextField. If the
 STPPaymentCardTextField is not valid, the completion block is called with an
 error.

 @param textField   The STPPaymentCardTextField in which a user has entered
 card details.

 @param completion  The completion block called when the command completes.
 */
- (void)createKeyedSourceWithSTPPaymentCardTextField:(id)textField completion:(SCPCardSourceCompletionBlock)completion;

/**
 Returns an unlocalized string for the given card presentation type.
 ex. "Swipe / Insert"
 */
+ (NSString *)stringFromCardPresentationType:(SCPCardPresentationType)type;

/**
 Returns an unlocalized string for the given read card prompt.
 ex. "Retry Card"
 */
+ (NSString *)stringFromReadCardPrompt:(SCPReadCardPrompt)prompt;

/**
 Returns an unlocalized string for the given connection status.
 ex. "Connecting"
 */
+ (NSString *)stringFromConnectionStatus:(SCPConnectionStatus)state;

/**
 Returns an unlocalized string for the given payment status.
 ex. "Not Ready"
 */
+ (NSString *)stringFromPaymentStatus:(SCPPaymentStatus)state;

/**
 Use `initWithConfiguration:tokenProvider:delegate:`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithConfiguration:tokenProvider:delegate:`
 */
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
