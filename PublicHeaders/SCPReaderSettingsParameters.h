//
//  SCPReaderSettingsParameters.h
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
 The protocol that classes that are able to be passed in to setReaderSettings must implement.

 You do not implement this protocol but instead use one of the existing SDK classes that conforms to this protocol:
 - `SCPReaderAccessibilityParameters`
 */
NS_SWIFT_NAME(ReaderSettingsParameters)
@protocol SCPReaderSettingsParameters <NSObject>
@end

NS_ASSUME_NONNULL_END
