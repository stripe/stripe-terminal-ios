//
//  SCPLocalMobileConnectionConfiguration.h
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
#import <StripeTerminal/SCPReconnectionDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This class lets you set options that define local mobile reader behavior throughout a given
 reader-to-SDK connection session.
 */
NS_SWIFT_NAME(LocalMobileConnectionConfiguration)
@interface SCPLocalMobileConnectionConfiguration : SCPConnectionConfiguration

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
 `SCPLocalMobileConnectionConfiguration`.
 Unlike other reader types which require this information on a per-transaction basis, the Apple Built-In reader
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

 @see SCPErrorAppleBuiltInReaderTOSNotYetAccepted
 @note Defaults to `YES` when not otherwise specified.
 */
@property (nonatomic, assign, readonly, getter=isTOSAcceptancePermitted) BOOL tosAcceptancePermitted;

/**
 In iOS 16.4 and later, the local mobile reader can return the card read results as soon as they are
 available instead of waiting for the system UI to dismiss completely. This flow can substantially reduce
 the amount of time it takes for a transaction to complete.
 @note Defaults to `YES` when not otherwise specified.
 */
@property (nonatomic, assign, readonly, getter=isReturnReadResultImmediatelyEnabled) BOOL returnReadResultImmediatelyEnabled;

/**
 When set to true, the Terminal SDK  will attempt a local mobile auto-reconnection on any unexpected disconnect.
 You must also set an `autoReconnectionDelegate` for your application to respond accordingly to reconnection attempts.
 Enabling `autoReconnectOnUnexpectedDisconnect` without providing an `autoReconnectionDelegate` will error with `SCPErrorReaderConnectionConfigurationInvalid`.

 When set to false, we will immediately surface any disconnection through TerminalDelegate.

 Defaults to false.
 */
@property (nonatomic, assign, readonly, getter=isAutoReconnectOnUnexpectedDisconnect) BOOL autoReconnectOnUnexpectedDisconnect;

/**
 Contains callback methods for local mobile auto-reconnection.
 */
@property (nonatomic, weak, readonly, nullable) id<SCPReconnectionDelegate> autoReconnectionDelegate;

/**
 Use `SCPLocalMobileConnectionConfigurationBuilder`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPLocalMobileConnectionConfigurationBuilder`
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 * A builder class for `SCPLocalMobileConnectionConfiguration`.
 */
NS_SWIFT_NAME(LocalMobileConnectionConfigurationBuilder)
@interface SCPLocalMobileConnectionConfigurationBuilder : SCPBuilder <SCPLocalMobileConnectionConfiguration *>

/**
 * @param locationId ID of the location to be associated with the reader.
 * @see `SCPLocalMobileConnectionConfiguration.locationId`
 */
- (instancetype)initWithLocationId:(NSString *)locationId NS_DESIGNATED_INITIALIZER;

/**
 * @param locationId ID of the location to be associated with the reader.
 * @note This is a required attribute of the connection configuration and cannot be nil or empty.
 * @see `SCPLocalMobileConnectionConfiguration.locationId`
 */
- (SCPLocalMobileConnectionConfigurationBuilder *)setLocationId:(NSString *)locationId;

/**
 * @param onBehalfOf Connected account id that the merchant is taking payments on behalf of.
 * @see `SCPLocalMobileConnectionConfiguration.onBehalfOf`
 */
- (SCPLocalMobileConnectionConfigurationBuilder *)setOnBehalfOf:(nullable NSString *)onBehalfOf;

/**
 * @param merchantDisplayName Cardholder facing merchant display name that will be used in the prompt
 *   for the cardholder to present their card.
 * @see `SCPLocalMobileConnectionConfiguration.merchantDisplayName`
 */
- (SCPLocalMobileConnectionConfigurationBuilder *)setMerchantDisplayName:(nullable NSString *)merchantDisplayName;

/**
 * @param tosAcceptancePermitted Determines how to handle the situation where merchant-specific
 *   terms of service need to be presented in order to connect to a reader.
 * @note If not set, defaults to `YES`.
 * @see `SCPLocalMobileConnectionConfiguration.tosAcceptancePermitted`
 */
- (SCPLocalMobileConnectionConfigurationBuilder *)setTosAcceptancePermitted:(BOOL)tosAcceptancePermitted;

/**
 * @param returnReadResultImmediatelyEnabled When possible the card read results are returned as
 *   early as possible, prior to the complete dismissal of card reader UI.
 * @note If not set, defaults to `YES`.
 * @see `SCPLocalMobileConnectionConfiguration.returnReadResultImmediatelyEnabled`
 */
- (SCPLocalMobileConnectionConfigurationBuilder *)setReturnReadResultImmediatelyEnabled:(BOOL)returnReadResultImmediatelyEnabled;

/**
 When set to true, the Terminal SDK  will attempt a local mobile auto-reconnection on any unexpected disconnect.
 You must also set an `autoReconnectionDelegate` for your application to respond accordingly to reconnection attempts.
 Enabling `autoReconnectOnUnexpectedDisconnect` without providing an `autoReconnectionDelegate` will error with `SCPErrorReaderConnectionConfigurationInvalid`.

 When set to false, we will immediately surface any disconnection through TerminalDelegate.

 Defaults to false.
 */
- (SCPLocalMobileConnectionConfigurationBuilder *)setAutoReconnectOnUnexpectedDisconnect:(BOOL)autoReconnectOnUnexpectedDisconnect;

/**
 Contains callback methods for local mobile auto-reconnection.
 */
- (SCPLocalMobileConnectionConfigurationBuilder *)setAutoReconnectionDelegate:(nullable id<SCPReconnectionDelegate>)autoReconnectionDelegate;

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
