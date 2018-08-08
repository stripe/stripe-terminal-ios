//
//  UITabBarItem+StripePOS.swift
//  Dev
//
//  Created by Ben Guo on 4/27/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit

extension UITabBarItem {
    static func buildItem(title: String) -> UITabBarItem {
        let item = UITabBarItem(title: title, image: nil, selectedImage: nil)
        item.titlePositionAdjustment = UIOffset(horizontal: 0, vertical: -14)
        let attributes: [NSAttributedStringKey: Any] = [
            .font: UIFont.preferredFont(forTextStyle: .headline)
        ]
        item.setTitleTextAttributes(attributes, for: .normal)
        item.setTitleTextAttributes(attributes, for: .selected)
        return item
    }
}
