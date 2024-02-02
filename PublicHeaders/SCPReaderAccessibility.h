//
//  SCPReaderAccessibility.h
//  StripeTerminal
//
//  Created by Max Afonov on 12/6/23.
//  Copyright © 2023 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Represents the current text to speech status of
 the reader.
 Note that the actual text to speech value returned here
 may not match what was last requested since the reader
 may switch to headphones if the customer plugs in
 headphones and the state will reset to off after
 reboots.

 See the [Reader Settings](https://stripe.com/docs/terminal/features/reader-accessibility)
 */
typedef NS_ENUM(NSUInteger, SCPReaderTextToSpeechStatus) {
    /**
     * Text to speech status is not known. This can happen if there was an error reading the text to speech status on the reader.
     * check the `error` property.
     */
    SCPReaderTextToSpeechStatusUnknown,

    /**
     * Text to speech is not enabled
     */
    SCPReaderTextToSpeechStatusOff,

    /**
     * Text to speech is enabled via headphones
     */
    SCPReaderTextToSpeechStatusHeadphones,

    /**
     * Text to speech is enabled via speakers
     */
    SCPReaderTextToSpeechStatusSpeakers,
} NS_SWIFT_NAME(ReaderTextToSpeechStatus);

/**
 Class representing the accessibility state of the reader.
 */
NS_SWIFT_NAME(ReaderAccessibility)
@interface SCPReaderAccessibility : NSObject

/**
 Text to speech status of the reader.
 */
@property (nonatomic, readonly) SCPReaderTextToSpeechStatus textToSpeechStatus;

/**
 If non-nil represents the error from the reader when attempting to read or set the accessibility settings.
 */
@property (nonatomic, nullable, readonly) NSError *error;

/**
 You cannot directly instantiate this class.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 You cannot directly instantiate this class.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
