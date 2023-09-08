//
//  SCPTerminal+OfflineMode.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2023-08-16.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

/**
 While offline mode is in beta the public interfaces may change. To opt-in,
 in Xcode select your project > select your application target > add SCP_OFFLINE_MODE=1 to Preprocessor Macros.
 */
#ifdef SCP_OFFLINE_MODE

#import <StripeTerminal/SCPNetworkStatus.h>
#import <StripeTerminal/SCPOfflineStatus.h>
#import <StripeTerminal/SCPPaymentIntent.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPOfflineDetails, SCPCreateConfiguration;

@interface SCPTerminal (OfflineMode)

/// Set to receive offline reporting events from the SDK.
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

/**
 Returns an unlocalized string for the given network status, e.g. "Online"
 */
+ (NSString *)stringFromNetworkStatus:(SCPNetworkStatus)networkStatus NS_SWIFT_NAME(stringFromNetworkStatus(_:));

@end

@interface SCPPaymentIntent (OfflineMode)

/**
 The offline details for this intent, if created or processed while offline.

 When created offline the intent.stripeId will be nil. The OfflineDetails stripeId will
 contain a unique identifier that can be used to identify this intent.

 The `OfflineDetails` `requiresUpload` can be used to
 identify that the intent was processed offline and requires the device to be
 brought back online so the intent can be forwarded.

 @see https://stripe.com/docs/terminal/features/operate-offline/
 */
- (nullable SCPOfflineDetails *)offlineDetails;

@end

NS_ASSUME_NONNULL_END

#endif // SCP_OFFLINE_MODE
