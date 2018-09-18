//
//  UIView+Layout.swift
//  Dashboard
//
//  Created by Brian Dorfman on 7/26/16.
//  Copyright © 2016 Stripe. All rights reserved.
//
import UIKit

extension UIView {
    // MARK: - Autolayout Helpers
    /**
     Add constraints to superview that anchor this view's top, leading, trailing
     and bottom edges to the superview's.
     This is *not* margin or safe area aware.
     - warning: This will crash if this view does not have a superview.
     - returns: A tuple containing the top, leading, trailing, and bottom
     constraints
     */
    @discardableResult
    public func anchorToSuperviewAnchors(withInsets insets: UIEdgeInsets = UIEdgeInsets.zero) ->
        (top: NSLayoutConstraint, leading: NSLayoutConstraint, trailing: NSLayoutConstraint, bottom: NSLayoutConstraint) {
            guard let superview = superview else {
                fatalError("must have a superview to anchor to")
            }

            let top = topAnchor.constraint(equalTo: superview.topAnchor, constant: insets.top)
            let leading = leadingAnchor.constraint(equalTo: superview.leadingAnchor, constant: insets.left)
            let trailing = superview.trailingAnchor.constraint(equalTo: trailingAnchor, constant: insets.right)
            let bottom = superview.bottomAnchor.constraint(equalTo: bottomAnchor, constant: insets.bottom)

            NSLayoutConstraint.activate([top, leading, trailing, bottom])
            return (top, leading, trailing, bottom)
    }

    /**
     Add & activate constraints that set this view's top, leading, trailing, and bottom
     edges equal to the corresponding edge in the provided UILayoutGuide.
     - parameter layoutGuide: the UILayoutGuide to constrain to
     - parameter insets: optional insets from the layoutGuide
     */
    public func anchor(to layoutGuide: UILayoutGuide, withInsets insets: UIEdgeInsets = .zero) {
        topAnchor.constraint(equalTo: layoutGuide.topAnchor, constant: insets.top).isActive = true
        leadingAnchor.constraint(equalTo: layoutGuide.leadingAnchor, constant: insets.left).isActive = true
        trailingAnchor.constraint(equalTo: layoutGuide.trailingAnchor, constant: -insets.right).isActive = true
        bottomAnchor.constraint(equalTo: layoutGuide.bottomAnchor, constant: -insets.bottom).isActive = true
    }

    /**
     Using required inequality constraints, force this view to be within it's superview (+ optional insets).
     In the general case, these constraints alone will lead to an ambiguous layout.
     - parameter insets: optional (minimum) insets from the superview
     */
    public func constrainInsideSuperview(withInsets insets: UIEdgeInsets = .zero) {
        guard let superview = superview else {
            fatalError("must have a superview to create constraints to")
        }

        topAnchor.constraint(greaterThanOrEqualTo: superview.topAnchor, constant: insets.top).isActive = true
        leadingAnchor.constraint(greaterThanOrEqualTo: superview.leadingAnchor, constant: insets.left).isActive = true
        trailingAnchor.constraint(lessThanOrEqualTo: superview.trailingAnchor, constant: -insets.right).isActive = true
        bottomAnchor.constraint(lessThanOrEqualTo: superview.bottomAnchor, constant: -insets.bottom).isActive = true

    }
}
