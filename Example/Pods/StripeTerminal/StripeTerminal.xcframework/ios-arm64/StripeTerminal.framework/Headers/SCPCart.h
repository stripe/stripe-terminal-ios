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
 Represents a single line item in an `SCPCart`, displayed on the reader's screen
 during checkout.
 */
NS_SWIFT_NAME(CartLineItem)
@interface SCPCartLineItem : NSObject

/** The quantity of the line item being purchased.*/
@property (nonatomic, readwrite, assign) NSInteger quantity;

/** The description or name of the item. */
@property (nonatomic, copy) NSString *displayName;

/**
 The price of the item, provided in the cart's currency's smallest unit.
 
 @see https://stripe.com/docs/currencies#zero-decimal
 */
@property (nonatomic, readwrite, assign) NSInteger amount;

/**
 The values set here will be shown on the screen as-is. Make sure you're
 correctly calculating and setting the SCPCart's tax and total -- the reader
 will not calculate tax or total for you. Similarly, make sure the values
 displayed reflect what the customer is actually charged.

 @param displayName The description or name of the item.
 @param quantity    The quanitity of the item that should show in the cart.
 @param amount      The price in the currency's smallest unit. The line item
                    will assume the currency of the parent `SCPCart`.
*/
- (instancetype)initWithDisplayName:(NSString *)displayName
                           quantity:(NSInteger)quantity
                             amount:(NSInteger)amount;
@end

/**
 An `SCPCart` object contains information about what line items are included in
 the current transaction. A cart object should be created and then passed into
 `Terminal.shared.setReaderDisplay()`, which will display the cart's contents
 on the reader's screen.

 The `SCPCart` only represents exactly what will be shown on the screen, and is
 not reflective of what the customer is actually charged. You are
 responsible for making sure that tax and total reflect what is in the cart.

 @note Only Internet readers support setReaderDisplay functionality

 @see https://stripe.com/docs/terminal/checkout/cart-display
*/
NS_SWIFT_NAME(Cart)
@interface SCPCart : NSObject

/** You can add or remove line items from this array individually or reassign the array entirely.
    After making your desired changes, call setReaderDisplay to update the cart on the reader's screen.*/
@property (nonatomic, strong, readwrite) NSMutableArray<SCPCartLineItem *> *lineItems;

/** The displayed tax amount, provided in the currency's smallest unit. */
@property (nonatomic, assign, readwrite) NSInteger tax;

/** The cart's total balance, provided in the currency's smallest unit. */
@property (nonatomic, assign, readwrite) NSInteger total;

/** The currency of the cart. */
@property (nonatomic, copy) NSString *currency;

/**
 Initializes an SCPCart with tax and total, in cents, as well as the currency.
 These values are exactly what will be shown on the screen and do not reflect
 what the user is actually charged.

 This initializer will initialize `lineItems` as an empty array.

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
