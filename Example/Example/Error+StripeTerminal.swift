//
//  Error+StripeTerminal.swift
//  StripeTerminal
//
//  Created by Max Afonov on 1/11/24.
//  Copyright © 2024 Stripe. All rights reserved.
//
//  Use of this SDK is subject to the Stripe Terminal Terms:
//  https://stripe.com/terminal/legal
//

import Foundation

extension Error {
    var domain: String { (self as NSError).domain }
    var code: Int { (self as NSError).code }
    var scp_userInfo: [String: String] {
        return Dictionary(uniqueKeysWithValues: (self as NSError).userInfo
            .filter {$0.key != "NSLocalizedDescription"}
            .map {($0.replacingOccurrences(of: domain, with: ""), "\($1)")}
            .filter {$0.0 != ":Message"}
        )
    }
}
