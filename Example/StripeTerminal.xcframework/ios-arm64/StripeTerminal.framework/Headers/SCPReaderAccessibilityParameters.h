//
//  SCPReaderAccessibilityParameters.h
//  StripeTerminal
//
//  Created by Max Afonov on 12/6/23.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>
#import <StripeTerminal/SCPBuilder.h>
#import <StripeTerminal/SCPJSONDecodable.h>
#import <StripeTerminal/SCPReaderSettingsParameters.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The `SCPReaderAccessibilityParameters` class contains information used to update the
 reader's accessibility settings. To create a `ReaderAccessibilityParameters` instance,
 the `SCPReaderAccessibilityParametersBuilder` class should be used.
 */
NS_SWIFT_NAME(ReaderAccessibilityParameters)
@interface SCPReaderAccessibilityParameters : NSObject <SCPReaderSettingsParameters>

/**
 The text to speech via speakers status.
 */
@property (nonatomic, assign, readonly) BOOL textToSpeechViaSpeakers;

/**
 Use `SCPReaderSettingsParametersBuilder`
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPReaderSettingsParametersBuilder`
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 * A builder class for `SCPReaderSettingsParameters`.
 */
NS_SWIFT_NAME(ReaderAccessibilityParametersBuilder)
@interface SCPReaderAccessibilityParametersBuilder : SCPBuilder <SCPReaderAccessibilityParameters *>

/**
 * @see `SCPReaderAccessibilityParameters.textToSpeechViaSpeakers`
 */
- (SCPReaderAccessibilityParametersBuilder *)setTextToSpeechViaSpeakers:(BOOL)textToSpeechViaSpeakers;

@end

NS_ASSUME_NONNULL_END
