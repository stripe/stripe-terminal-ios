//
//  UserDefaultsBacked.swift
//  Terminal
//
//  Created by Brian Cooke on 4/11/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import Foundation

@propertyWrapper
struct UserDefaultsBacked<Value: Codable> {
    let key: String
    let defaultValue: Value

    var wrappedValue: Value {
        get {
            // Retrieve data values for a key
            guard let data = UserDefaults.standard.data(forKey: key) else {
                return defaultValue
            }
            return (try? PropertyListDecoder().decode([Value].self, from: data))?.first ?? defaultValue
        }
        set {
            // Use PropertyListEncoder to support `Encodable` but wrap in an
            // array to handle `Bool` which PropertyListEncoder doesn't encode.
            // Decoder above will pull from .first to take it out of the
            // wrapping array.
            let data = try? PropertyListEncoder().encode([newValue])
            UserDefaults.standard.set(data, forKey: key)
        }
    }
}
