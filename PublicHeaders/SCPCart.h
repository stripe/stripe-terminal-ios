//
//  SCPCart.h
//  StripeTerminal
//
//  Created by Matthew Krager on 6/5/20.
//  Copyright © 2020 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
    Dictates what will be shown on the screen through setReaderDisplay.
    Represents exactly what will be shown on the screen.
 */
@interface SCPCartLineItem : NSObject

/** The quantity of the line item being purchased.*/
@property (nonatomic, readwrite, assign) NSInteger quantity;

/** The description or name of the item.*/
@property (nonatomic, copy) NSString *displayName;

/** The price of the item in cents. */
@property (nonatomic, readwrite, assign) NSInteger amount;

/**
    The values set here will be shown on the screen as-is. Make sure
    you're correctly calculating and setting the SCPCart's
    tax and total -- the Verifone P400 will not calculate tax or total for you.
    Similarly, make sure the values displayed reflect what the customer is actually charged.

 @param displayName                       Description or name of the item
 @param quantity                              The how many of the item should show in the cart
 @param amount                                  The price in cents, will assume the currency of the SCPCart
*/
- (instancetype)initWithDisplayName:(NSString *)displayName
                           quantity:(NSInteger)quantity
                             amount:(NSInteger)amount;
@end

/**
    SCPCart contains information about what should display on the reader's cart.
    It should be created and then passed into setReaderDisplay, which will place
    the contents of the cart on the reader's display.

    You can pass the same SCPCart to multiple calls of setReaderDisplay since the cart
    is not coupled to any specific call of setReaderDisplay.

    The SCPCart only represents exactly what will be shown on the screen, and is
    not reflective of what the customer is actually charged. You are
    responsible for making sure that tax and total reflect what is in the cart.

    @note Only the Verifone P400 supports setReaderDisplay functionality

    @see https://stripe.com/docs/terminal/checkout/cart-display
*/
@interface SCPCart : NSObject

/** You can add or remove line items from this array individually or reassign the array entirely.
    After making your desired changes, call setReaderDisplay to update the cart on the reader's screen.*/
@property (nonatomic, strong, readwrite) NSMutableArray<SCPCartLineItem *> *lineItems;

/** The amount of tax in cents.  */
@property (nonatomic, assign, readwrite) NSInteger tax;

/** Total balance of cart due in cents. */
@property (nonatomic, assign, readwrite) NSInteger total;

/** The currency of the basket (i.e. USD or AUD). */
@property (nonatomic, copy) NSString *currency;

/**
 Initializes an SCPCart with tax and total, in cents, as well as the currency.
 These values are exactly what will be shown on the screen and do not reflect
 what the user is actually charged.

 Will initialize lineItems as an empty array.

 @param tax                 The tax in cents
 @param total             The total in cents
 @param currency      The currency of the basket (i.e. USD or AUD)
*/
- (instancetype)initWithCurrency:(NSString *)currency
                             tax:(NSInteger)tax
                           total:(NSInteger)total;

/** Use initWithTax: */
- (instancetype)init NS_UNAVAILABLE;
/** Use initWithTax: */
+ (instancetype)new NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
