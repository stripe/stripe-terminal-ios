//
//  LocationStub.swift
//  Example
//
//  Created by Mindy Lou on 8/10/23.
//  Copyright © 2023 Stripe. All rights reserved.
//

import Foundation
import StripeTerminal

// Stub for shared location properties.
struct LocationStub: Codable, Hashable {
    var stripeId: String
    var displayName: String
}

extension LocationStub: Identifiable {
    var id: String { return stripeId }
}

extension Location {

    func toLocationStub() -> LocationStub {
        return LocationStub(stripeId: self.stripeId, displayName: self.displayName ?? self.stripeId)
    }

}
