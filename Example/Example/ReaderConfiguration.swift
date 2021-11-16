//
//  ReaderConfiguration.swift
//  Terminal
//
//  Created by James Little on 10/1/19.
//  Copyright © 2019 Stripe. All rights reserved.
//

import Foundation
import StripeTerminal

/**
 A data structure for storing a user's reader configuration. Useful for
 saving and loading to UserDefaults.
 */
struct ReaderConfiguration {
    var discoveryMethod: DiscoveryMethod = .bluetoothScan
    var allowCustomerCancel: Bool = false

    #if targetEnvironment(simulator)
    var simulated = true
    #else
    var simulated = false
    #endif
}

extension ReaderConfiguration: Codable {
    private static let userDefaultsKey = "com.stripe.terminal.readerconfig"

    /**
     Saves the given variable to UserDefaults as a JSON data blob under a standard key.
     */
    func saveToUserDefaults() -> Data? {
        do {
            let json = try JSONEncoder().encode(self)
            UserDefaults.standard.set(json, forKey: ReaderConfiguration.userDefaultsKey)
            return json
        } catch {
            return nil
        }
    }

    /**
     Loads the current ReaderConfiguration object from UserDefaults, or returns the default
     if no saved object has been found.
     */
    static func loadFromUserDefaults() -> ReaderConfiguration {
        guard let data = UserDefaults.standard.data(forKey: ReaderConfiguration.userDefaultsKey) else {
            return ReaderConfiguration()
        }

        do {
            let config = try JSONDecoder().decode(ReaderConfiguration.self, from: data)
            return config
        } catch {
            return ReaderConfiguration()
        }
    }
}

extension DeviceType: Codable { /* Nothing needed here */ }
extension DiscoveryMethod: Codable { /* Nothing needed here */ }
