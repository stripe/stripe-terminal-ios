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

#import <StripeTerminal/SCPBuilder.h>

NS_ASSUME_NONNULL_BEGIN

@class SCPCartLineItem;

/**
 An `SCPCart` object contains information about what line items are included in
 the current transaction. A cart object should be created and then passed into
 `Terminal.shared.setReaderDisplay()`, which will display the cart's contents
 on the reader's screen.

 The `SCPCart` only represents exactly what will be shown on the screen, and is
 not reflective of what the customer is actually charged. You are
 responsible for making sure that tax and total reflect what is in the cart.

 These values are exactly what will be shown on the screen and do not reflect
 what the user is actually charged.

 @note Only Internet readers support setReaderDisplay functionality

 @see https://stripe.com/docs/terminal/checkout/cart-display
*/
NS_SWIFT_NAME(Cart)
@interface SCPCart : NSObject

/// The cart's line items. Default's to an empty array of line items.
@property (nonatomic, strong, readonly) NSArray<SCPCartLineItem *> *lineItems;

/// The displayed tax amount, provided in the currency's smallest unit. Defaults to 0.
@property (nonatomic, assign, readonly) NSInteger tax;

/// The cart's total balance, provided in the currency's smallest unit.
@property (nonatomic, assign, readonly) NSInteger total;

/// The currency of the cart.
@property (nonatomic, copy, readonly) NSString *currency;

/**
 Use `SCPCartBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPCartBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A builder class for `SCPCart` objects.
*/
NS_SWIFT_NAME(CartBuilder)
@interface SCPCartBuilder : SCPBuilder <SCPCart *>

/**
 Initializes a new instance of the `SCPCartBuilder` class with the provided
 currency.

 @param currency The currency of the cart. This is a required attribute of the
 cart and cannot be nil.
*/
- (instancetype)initWithCurrency:(NSString *)currency NS_DESIGNATED_INITIALIZER;

/**
 @see `SCPCart.currency`
 @note This is a required attribute of the cart and cannot be nil.
 @return `self` for convenience with method chaining.
 */
- (SCPCartBuilder *)setCurrency:(NSString *)currency;

/**
 @see `SCPCart.tax`
 @note If not set, defaults to 0.
 @return `self` for convenience with method chaining.
 */
- (SCPCartBuilder *)setTax:(NSInteger)tax;

/**
 @see `SCPCart.total`
 @note If not set, defaults to 0.
 @return `self` for convenience with method chaining.
 */
- (SCPCartBuilder *)setTotal:(NSInteger)total;

/**
 @see `SCPCart.lineItems`
 @note If not set, defaults to an empty array.
 @return `self` for convenience with method chaining.
 */
- (SCPCartBuilder *)setLineItems:(NSArray<SCPCartLineItem *> *)lineItems;

/**
 Use `initWithCurrency`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithCurrency`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 Represents a single line item in an `SCPCart`, displayed on the reader's screen
 during checkout.

 The values here will be shown on the screen as-is. Make sure you're
 correctly calculating and setting the `SCPCart`'s tax and total -- the reader
 will not calculate tax or total for you. Similarly, make sure the values
 displayed reflect what the customer is actually charged.
*/
NS_SWIFT_NAME(CartLineItem)
@interface SCPCartLineItem : NSObject

/// The quantity of the line item being purchased.
@property (nonatomic, assign, readonly) NSInteger quantity;

/// The description or name of the item.
@property (nonatomic, copy, readonly) NSString *displayName;

/**
 The price of the item, provided in the cart's currency's smallest unit.
 The line item will assume the currency of the parent `SCPCart`.

 @see https://stripe.com/docs/currencies#zero-decimal
 */
@property (nonatomic, assign, readonly) NSInteger amount;

/**
 Use `SCPCartLineItemBuilder`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `SCPCartLineItemBuilder`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

/**
 A builder class for `SCPCartLineItem` objects.
*/
NS_SWIFT_NAME(CartLineItemBuilder)
@interface SCPCartLineItemBuilder : SCPBuilder <SCPCartLineItem *>

/**
 Initializes a new instance of `SCPCartLineItemBuilder` with the required fields.

 @param displayName The description or name of the item.
 */
- (instancetype)initWithDisplayName:(NSString *)displayName NS_DESIGNATED_INITIALIZER;

/**
 @see `SCPCartLineItem.displayName`
 @return `self` for convenience with method chaining.
 */
- (SCPCartLineItemBuilder *)setDisplayName:(NSString *)displayName;

/**
 @see `SCPCartLineItem.quantity`
 @note If not set, defaults to 1.
 @return `self` for convenience with method chaining.
 */
- (SCPCartLineItemBuilder *)setQuantity:(NSInteger)quantity;

/**
 @see `SCPCartLineItem.amount`
 @note if not set, defaults to 0
 @return `self` for convenience with method chaining.
 */
- (SCPCartLineItemBuilder *)setAmount:(NSInteger)amount;

/**
 Use `initWithDisplayName`.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 Use `initWithDisplayName`.
 */
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
