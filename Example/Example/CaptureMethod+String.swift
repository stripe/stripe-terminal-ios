//
//  CaptureMethod+String.swift
//  Example
//
//  Created by Mindy Lou on 7/18/22.
//  Copyright © 2022 Stripe. All rights reserved.
//

import StripeTerminal

extension CaptureMethod {
    func toString() -> String {
        switch self {
        case .automatic:
            return "automatic"
        case .manual:
            return "manual"
        case .automaticAsync:
            return "automatic_async"
        @unknown default:
            fatalError()
        }
    }
}
