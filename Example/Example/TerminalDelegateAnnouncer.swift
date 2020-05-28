//
//  TerminalDelegateAnnouncer.swift
//  Example
//
//  Created by Brian Cooke on 4/24/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import Foundation
import StripeTerminal

/**
 Allows the Example app to use a single persistent TerminalDelegate and still have the view controllers receive
 the TerminalDelegate events.
 */
class TerminalDelegateAnnouncer: NSObject, TerminalDelegate {
    static let shared = TerminalDelegateAnnouncer()

    private var listeners = [WeakBox<TerminalDelegate>]()

    func addListener(_ delegate: TerminalDelegate) {
        if listeners.contains(where: { $0.unbox === delegate }) {
            return
        }
        listeners.append(WeakBox(delegate))
    }

    func removeListener(_ delegate: TerminalDelegate) {
        // Remove the requested delegate if found and clear out any zero'd references while we're here filtering
        listeners = listeners.filter { $0.unbox !== delegate && $0.unbox != nil }
    }

    // MARK: - TerminalDelegate
    func terminal(_ terminal: Terminal, didReportUnexpectedReaderDisconnect reader: Reader) {
        announce { delegate in
            delegate.terminal(terminal, didReportUnexpectedReaderDisconnect: reader)
        }
    }

    func terminal(_ terminal: Terminal, didReportReaderEvent event: ReaderEvent, info: [AnyHashable: Any]?) {
        announce { delegate in
            delegate.terminal?(terminal, didReportReaderEvent: event, info: info)
        }
    }

    func terminalDidReportLowBatteryWarning(_ terminal: Terminal) {
        announce { delegate in
            delegate.terminalDidReportLowBatteryWarning?(terminal)
        }
    }

    func terminal(_ terminal: Terminal, didChangePaymentStatus status: PaymentStatus) {
        announce { delegate in
            delegate.terminal?(terminal, didChangePaymentStatus: status)
        }
    }

    func terminal(_ terminal: Terminal, didChangeConnectionStatus status: ConnectionStatus) {
        announce { delegate in
            delegate.terminal?(terminal, didChangeConnectionStatus: status)
        }
    }

    // MARK: - Internal

    private func announce(_ announcement: (TerminalDelegate) -> Void) {
        var zerodRefs = [WeakBox<TerminalDelegate>]()

        for weakListener in listeners {
            guard let listener = weakListener.unbox else {
                zerodRefs.append(weakListener)
                continue
            }
            announcement(listener)
        }

        // Remove any zero'd references
        listeners = listeners.filter { listener in
            !zerodRefs.contains(where: { zerod in zerod === listener })
        }
    }
}

final class WeakBox<A: AnyObject> {
    weak var unbox: A?
    init(_ value: A) {
        unbox = value
    }
}
