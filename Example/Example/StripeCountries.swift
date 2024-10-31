//
//  StripeCountries.swift
//  Example
//
//  Created by Bibek Ghimire on 3/25/21.
//  Copyright © 2021 Stripe. All rights reserved.
//

import Foundation

struct StripeCountries {
    static let supportedByTerminal: [String] = [
        "US",
        "CA",
        "SG",
        "GB",
        "IE",
        "AU",
        "NZ",
        "FR",
        "DE",
        "NL",
        "BE",
        "AT",
        "ES",
        "DK",
        "IT",
        "SE",
        "LU",
        "PT",
        "NO",
        "FI",
        "CH",
        "CZ"
    ]

    static func countryName(forRegionCode code: String) -> String? {
        if let countryName = Locale.current.localizedString(forRegionCode: code) {
            return countryName
        }
        return nil
    }
}
