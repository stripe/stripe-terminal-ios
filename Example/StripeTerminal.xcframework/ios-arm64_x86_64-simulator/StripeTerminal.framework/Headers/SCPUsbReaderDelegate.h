//
//  SCPUsbReaderDelegate.h
//  StripeTerminal
//
//  Created by Brian Cooke on 2024-02-21.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#ifdef SCP_USB_ENABLED

#import <StripeTerminal/SCPBluetoothReaderDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Implement this protocol to handle a connected USB reader's events throughout
 the lifetime of its connection.

 Implementing this delegate is required when connecting to any USB connected
 reader, such as the Stripe M2, BBPOS Chipper 2X BT, and the BBPOS WisePad 3.

 The provided delegate must be retained by your application until the reader disconnects.
 */
NS_SWIFT_NAME(UsbReaderDelegate)
@protocol SCPUsbReaderDelegate <SCPBluetoothReaderDelegate>
@end

NS_ASSUME_NONNULL_END

#endif // SCP_USB_ENABLED
