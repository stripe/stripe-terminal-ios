//
//  DiscoveryFilterType.swift
//  Example
//
//  Created by Brian Cooke on 10/31/25.
//  Copyright © 2025 Stripe. All rights reserved.
//

import Foundation

enum DiscoveryFilterType: String, CaseIterable, CustomStringConvertible {
    case none = "None"
    case bySerialNumber = "By Serial Number"
    case byReaderId = "By Reader ID"

    var description: String {
        return self.rawValue
    }

    var placeholder: String {
        switch self {
        case .none:
            return ""
        case .bySerialNumber:
            return "Enter serial number"
        case .byReaderId:
            return "Enter reader ID (tmr_*)"
        }
    }
}
