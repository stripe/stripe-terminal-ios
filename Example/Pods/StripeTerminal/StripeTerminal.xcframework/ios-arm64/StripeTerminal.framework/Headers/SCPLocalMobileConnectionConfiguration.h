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

#import <StripeTerminal/SCPConnectionConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This class lets you set options that define local mobile reader behavior throughout a given
 reader-to-SDK connection session.
 */
NS_SWIFT_NAME(LocalMobileConnectionConfiguration)
@interface SCPLocalMobileConnectionConfiguration : SCPConnectionConfiguration

/**
 The ID of the [Location](https://stripe.com/docs/api/terminal/locations) which the reader should be registered to during connection.

 If the provided ID matches the location the reader is already registered to, the
 location will not be changed.

 */
@property (nonatomic, copy, readonly) NSString *locationId;


/**
 If your integration is creating destination charges and using `on_behalf_of`,
 you must provide the `connected_account_id` in the `onBehalfOf` parameter as part of the `SCPLocalMobileConnectionConfiguration`
 @see: https://stripe.com/docs/terminal/features/connect#destination-payment-intents
*/
@property (nonatomic, copy, readonly, nullable) NSString *onBehalfOf;

/**

 Optional cardholder facing merchant display name that will be used in the prompt for the cardholder to present their card.

If this value is not provided, the merchant display name will be taken from the Terminal `Location.display_name`  associated with the connection
*/
@property (nonatomic, copy, readonly, nullable) NSString *merchantDisplayName;

/**
 Initialize ConnectionConfiguration with a location ID.
 @param locationId the ID of the location to be associated with the reader
 @return A new instance of the receiver configured with a location id
 */
- (instancetype)initWithLocationId:(NSString *)locationId;

/**
 Initialize ConnectionConfiguration with a location ID, custom merchant display name, and onBehalfOf connected account ID
 @param locationId the ID of the location to be associated with the reader
 @param merchantDisplayName Cardholder facing merchant display name that will be used in the prompt for the cardholder to present their card
 @param onBehalfOf Connected account id that the merchant is taking payments on behalf of
 @return A new instance of the receiver configured with a location id, merchant display name, and `on behalf of` connected account id
 */
- (instancetype)initWithLocationId:(NSString *)locationId
               merchantDisplayName:(NSString * _Nullable)merchantDisplayName
                        onBehalfOf:(NSString * _Nullable)onBehalfOf;
@end

NS_ASSUME_NONNULL_END
