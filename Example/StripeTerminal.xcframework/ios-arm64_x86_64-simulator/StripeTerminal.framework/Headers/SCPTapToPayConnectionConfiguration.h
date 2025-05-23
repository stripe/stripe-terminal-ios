//
//  SCPTapToPayConnectionConfiguration.h
//  StripeTerminal
//
//  Created by Ross Favero on 2/8/22.
//  Copyright © 2022 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPConnectionConfiguration.h>
#import <StripeTerminal/SCPTapToPayReaderDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This class lets you set options that define tap to pay reader behavior throughout a given
 reader-to-SDK connection session.
 */
NS_SWIFT_NAME(TapToPayConnectionConfiguration)
@interface SCPTapToPayConnectionConfiguration : SCPConnectionConfiguration

/**
 The TapToPayReaderDelegate to use for this connection to the reader.
 */
@property (nonatomic, weak, readonly) id<SCPTapToPayReaderDelegate> delegate;

/**
 The ID of the [Location](https://stripe.com/docs/api/terminal/locations) which the reader should be
 registered to during connection.
 If the provided ID matches the location the reader is already registered to, the location field on the reader
 object will not be changed.
 */
@property (nonatomic, copy, readonly) NSString *locationId;

/**
 If your integration is creating destination charges and using `on_behalf_of`, you must provide the
 `connected_account_id` in the `onBehalfOf` parameter as part of the
 `SCPTapToPayConnectionConfiguration`.
 Unlike other reader types which require this information on a per-transaction basis, the Tap To Pay reader
 requires this on a per-connection basis as well in order to establish a reader connection.
 @see https://stripe.com/docs/terminal/features/connect#destination-payment-intents
 */
@property (nonatomic, copy, readonly, nullable) NSString *onBehalfOf;

/**
 Optional cardholder facing merchant display name that will be used in the prompt for the cardholder
 to present their card. If this value is not provided, the merchant display name will be taken from
 the Terminal `Location.display_name` associated with the connection.
 */
@property (nonatomic, copy, readonly, nullable) NSString *merchantDisplayName;

/**
 In order to connect to a reader, merchant-specific terms of service may need to be accepted.
 Presenting the flow requires iCloud sign-in and an authorized individual. This attribute
 determines how the connection process should proceed if this situation is
 encountered.

 - If YES, the terms the terms of service should be presented during connection.
   If accepted successfully, the connection process will resume.
   If not accepted succesfully, the connection will fail with an error.
 - If NO, the terms of service will not be presented and the connection will fail with an error.

 @see SCPErrorTapToPayReaderTOSNotYetAccepted
 @note Defaults to `YES` when not otherwise specified.
 */
@property (nonatomic, assign, readonly, getter=isTOSAcceptancePermitted) BOOL tosAcceptancePermitted;

/**
 In iOS 16.4 and later, the tap to pay reader can return the card read results as soon as they are
 available instead of waiting for the system UI to dismiss completely. This flow can substantially reduce
 the amount of time it takes for a transaction to complete.
 @note Defaults to `YES` when not otherwise specified.
 */
@property (nonatomic, assign, readonly, getter=isReturnReadResultImmediatelyEnabled) BOOL returnReadResultImmediatelyEnabled;

/**
 When set to true, the Terminal SDK  will attempt a tap to pay auto-reconnection on any unexpected disconnect.
 Implement the `reader:didStartReconnect:` and related callbacks  for your application to respond accordingly to
 reconnection attempts.

 When set to false, the SDK will immediately surface any disconnection through ReaderDelegate.

 Defaults to true.
 */
@property (nonatomic, assign, readonly, getter=isAutoReconnectOnUnexpectedDisconnect) BOOL autoReconnectOnUnexpectedDisconnect;

/**
 Use `SCPTapToPayConnectionConfigurationBuilder`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPTapToPayConnectionConfigurationBuilder`
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 * A builder class for `SCPTapToPayConnectionConfiguration`.
 */
NS_SWIFT_NAME(TapToPayConnectionConfigurationBuilder)
@interface SCPTapToPayConnectionConfigurationBuilder : SCPBuilder <SCPTapToPayConnectionConfiguration *>

/**
 * @param delegate The TapToPayReaderDelegate to use for the connection to this reader.
 * @param locationId ID of the location to be associated with the reader.
 * @see `SCPTapToPayConnectionConfiguration.locationId`
 */
- (instancetype)initWithDelegate:(id<SCPTapToPayReaderDelegate>)delegate locationId:(NSString *)locationId NS_DESIGNATED_INITIALIZER;

/**
 * @param locationId ID of the location to be associated with the reader.
 * @note This is a required attribute of the connection configuration and cannot be nil or empty.
 * @see `SCPTapToPayConnectionConfiguration.locationId`
 */
- (SCPTapToPayConnectionConfigurationBuilder *)setLocationId:(NSString *)locationId;

/**
 * @param onBehalfOf Connected account id that the merchant is taking payments on behalf of.
 * @see `SCPTapToPayConnectionConfiguration.onBehalfOf`
 */
- (SCPTapToPayConnectionConfigurationBuilder *)setOnBehalfOf:(nullable NSString *)onBehalfOf;

/**
 * @param merchantDisplayName Cardholder facing merchant display name that will be used in the prompt
 *   for the cardholder to present their card.
 * @see `SCPTapToPayConnectionConfiguration.merchantDisplayName`
 */
- (SCPTapToPayConnectionConfigurationBuilder *)setMerchantDisplayName:(nullable NSString *)merchantDisplayName;

/**
 * @param tosAcceptancePermitted Determines how to handle the situation where merchant-specific
 *   terms of service need to be presented in order to connect to a reader.
 * @note If not set, defaults to `YES`.
 * @see `SCPTapToPayConnectionConfiguration.tosAcceptancePermitted`
 */
- (SCPTapToPayConnectionConfigurationBuilder *)setTosAcceptancePermitted:(BOOL)tosAcceptancePermitted;

/**
 * @param returnReadResultImmediatelyEnabled When possible the card read results are returned as
 *   early as possible, prior to the complete dismissal of card reader UI.
 * @note If not set, defaults to `YES`.
 * @see `SCPTapToPayConnectionConfiguration.returnReadResultImmediatelyEnabled`
 */
- (SCPTapToPayConnectionConfigurationBuilder *)setReturnReadResultImmediatelyEnabled:(BOOL)returnReadResultImmediatelyEnabled;

/**
 When set to true, the Terminal SDK  will attempt a tap to pay auto-reconnection on any unexpected disconnect.
 Implement the `reader:didStartReconnect:` and related callbacks  for your application to respond accordingly to
 reconnection attempts.

 When set to false, the SDK will immediately surface any disconnection through ReaderDelegate.

 Defaults to true.
 */
- (SCPTapToPayConnectionConfigurationBuilder *)setAutoReconnectOnUnexpectedDisconnect:(BOOL)autoReconnectOnUnexpectedDisconnect;

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
