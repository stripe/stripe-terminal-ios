//
//  StripeTerminal.h
//  StripeTerminal
//
//  Created by Ben Guo on 7/26/17.
//  Copyright © 2017 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Availability.h>
// The Stripe Terminal iOS SDK requires iOS >= 10.0.
// If your app needs to target iOS 9, you can skip this check by defining
// `SCP_SKIP_OS_VERSION_CHECK` in your build settings.
// If you do this, make a runtime check and only use Terminal from iOS 10+,
// otherwise you may encounter undefined breakages.
#ifndef SCP_SKIP_OS_VERSION_CHECK
#if __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_10_0
#error Module StripeTerminal requires deployment target of iOS 10.0 or later.
#endif
#endif

#import <StripeTerminal/SCPAddress.h>
#import <StripeTerminal/SCPBatteryStatus.h>
#import <StripeTerminal/SCPBlocks.h>
#import <StripeTerminal/SCPBluetoothConnectionConfiguration.h>
#import <StripeTerminal/SCPBluetoothReaderDelegate.h>
#import <StripeTerminal/SCPCancelable.h>
#import <StripeTerminal/SCPCardBrand.h>
#import <StripeTerminal/SCPCardDetails.h>
#import <StripeTerminal/SCPCardFundingType.h>
#import <StripeTerminal/SCPCardPresentDetails.h>
#import <StripeTerminal/SCPCart.h>
#import <StripeTerminal/SCPCharge.h>
#import <StripeTerminal/SCPConfirmSetupIntentError.h>
#import <StripeTerminal/SCPConnectionConfiguration.h>
#import <StripeTerminal/SCPConnectionStatus.h>
#import <StripeTerminal/SCPConnectionTokenProvider.h>
#import <StripeTerminal/SCPDeprecations.h>
#import <StripeTerminal/SCPDeviceType.h>
#import <StripeTerminal/SCPDiscoveryConfiguration.h>
#import <StripeTerminal/SCPDiscoveryDelegate.h>
#import <StripeTerminal/SCPDiscoveryMethod.h>
#import <StripeTerminal/SCPErrors.h>
#import <StripeTerminal/SCPInternetConnectionConfiguration.h>
#import <StripeTerminal/SCPJSONDecodable.h>
#import <StripeTerminal/SCPListLocationsParameters.h>
#import <StripeTerminal/SCPLocation.h>
#import <StripeTerminal/SCPLocationStatus.h>
#import <StripeTerminal/SCPLogLevel.h>
#import <StripeTerminal/SCPPaymentIntent.h>
#import <StripeTerminal/SCPPaymentIntentParameters.h>
#import <StripeTerminal/SCPPaymentMethod.h>
#import <StripeTerminal/SCPPaymentMethodDetails.h>
#import <StripeTerminal/SCPPaymentMethodType.h>
#import <StripeTerminal/SCPPaymentStatus.h>
#import <StripeTerminal/SCPProcessPaymentError.h>
#import <StripeTerminal/SCPProcessRefundError.h>
#import <StripeTerminal/SCPReadReusableCardParameters.h>
#import <StripeTerminal/SCPReader.h>
#import <StripeTerminal/SCPReaderDisplayMessage.h>
#import <StripeTerminal/SCPReaderEvent.h>
#import <StripeTerminal/SCPReaderInputOptions.h>
#import <StripeTerminal/SCPReaderNetworkStatus.h>
#import <StripeTerminal/SCPReaderSoftwareUpdate.h>
#import <StripeTerminal/SCPReceiptDetails.h>
#import <StripeTerminal/SCPRefund.h>
#import <StripeTerminal/SCPRefundParameters.h>
#import <StripeTerminal/SCPSetupAttempt.h>
#import <StripeTerminal/SCPSetupAttemptCardPresentDetails.h>
#import <StripeTerminal/SCPSetupAttemptPaymentMethodDetails.h>
#import <StripeTerminal/SCPSetupIntent.h>
#import <StripeTerminal/SCPSetupIntentParameters.h>
#import <StripeTerminal/SCPSimulateReaderUpdate.h>
#import <StripeTerminal/SCPSimulatedCard.h>
#import <StripeTerminal/SCPSimulatedCardType.h>
#import <StripeTerminal/SCPSimulatorConfiguration.h>
#import <StripeTerminal/SCPTerminal.h>
#import <StripeTerminal/SCPTerminalDelegate.h>
