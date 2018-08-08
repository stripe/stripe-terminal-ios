//
//  StripePOS+CustomStringConvertible.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/8/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import StripePOS

extension SCPConnectionStatus: CustomStringConvertible {
    public var description: String {
        return SCPTerminal.string(from: self)
    }
}

extension SCPPaymentStatus: CustomStringConvertible {
    public var description: String {
        return SCPTerminal.string(from: self)
    }
}

extension SCPDeviceType: LosslessStringConvertible {
    public var description: String {
        return SCPDiscoveryConfiguration.string(from: self)
    }

    public init?(_ description: String) {
        if description == "Chipper 2X" {
            self = .chipper2X
        }
        return nil
    }
}

extension SCPPaymentIntentStatus: CustomStringConvertible {
    public var description: String {
        switch self {
        case .requiresCapture: return "Requires Capture"
        case .requiresConfirmation: return "Requires Confirmation"
        case .requiresSource: return "Requires Source"
        case .canceled: return "Canceled"
        case .succeeded: return "Succeeded"
        }
    }
}

extension SCPUpdateTimeEstimate: CustomStringConvertible {
    public var description: String {
        switch self {
        case .estimateLessThan1Minute: return "<1 minute"
        case .estimate1To2Minutes: return "1-2 minutes"
        case .estimate2To5Minutes: return "2-5 minutes"
        case .estimate5To10Minutes: return "5-10 minutes"
        }
    }
}

