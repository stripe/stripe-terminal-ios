//
//  PasteboardStore.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/29/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import Foundation
import UIKit

/**
 Stores a [String: String] in the general pasteboard
 */
class PasteboardStore: NSObject {
    static let shared = PasteboardStore()

    private let pasteboardType = "com.stripe.pasteboard-store"

    subscript(key: String) -> String? {
        get {
            return contents[key]
        }
        set {
            var currentContents = self.contents
            currentContents[key] = newValue?.description
            self.contents = currentContents
        }
    }

    private var contents: [String: String] {
        didSet {
            let data = NSKeyedArchiver.archivedData(withRootObject: contents)
            UIPasteboard.general.setData(data, forPasteboardType: pasteboardType)
        }
    }

    override init() {
        if let data = UIPasteboard.general.data(forPasteboardType: pasteboardType),
            let dict = NSKeyedUnarchiver.unarchiveObject(with: data) as? [String: String] {
            contents = dict
        }
        else {
            contents = [:]
        }
        super.init()
    }

}
