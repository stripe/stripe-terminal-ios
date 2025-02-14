//
//  DelegateAnnouncer.swift
//  Example
//
//  Created by Brian Cooke on 4/24/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import Foundation
import StripeTerminal

/**
 Base class for a shareable announcer so multiple view controllers can receive the delegate callbacks as needed.
 */
class DelegateAnnouncer<Delegate: AnyObject>: NSObject {
    private var listeners = [WeakBox]()

    func addListener(_ delegate: Delegate) {
        if listeners.contains(where: { $0.unbox === delegate }) {
            return
        }
        listeners.append(WeakBox(delegate))
    }

    func removeListener(_ delegate: Delegate) {
        listeners = listeners.filter { $0.unbox !== delegate }
        listeners.compact()
    }

    internal func announce(_ announcement: (Delegate) -> Void) {
        listeners.compact()

        for weakListener in listeners {
            guard let listener = weakListener.unbox as? Delegate else { continue }
            announcement(listener)
        }
    }
}

/**
 Allows the Example app to use a single persistent TerminalDelegate and still have the
 view controllers receive the TerminalDelegate events.
 */
class TerminalDelegateAnnouncer: DelegateAnnouncer<TerminalDelegate>, TerminalDelegate {
    static let shared = TerminalDelegateAnnouncer()

    // MARK: - TerminalDelegate
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
}

// MARK: ReaderDelegate

class ReaderDelegateAnnouncer<T: ReaderDelegate>: DelegateAnnouncer<T>, ReaderDelegate {
    func reader(_ reader: Reader, didDisconnect reason: DisconnectReason) {
        announce { delegate in
            delegate.reader?(reader, didDisconnect: reason)
        }
    }

    func reader(_ reader: Reader, didStartReconnect cancelable: Cancelable, disconnectReason: DisconnectReason) {
        announce { delegate in
            delegate.reader?(reader, didStartReconnect: cancelable, disconnectReason: disconnectReason)
        }
    }

    func readerDidFailReconnect(_ reader: Reader) {
        announce { delegate in
            delegate.readerDidFailReconnect?(reader)
        }
    }

    func readerDidSucceedReconnect(_ reader: Reader) {
        announce { delegate in
            delegate.readerDidSucceedReconnect?(reader)
        }
    }
}

// MARK: MobileReaderDelegate

/**
 Allows the Example app to use a single persistent MobileReaderDelegate for the life of the connection
 and still have the view controllers receive the MobileReaderDelegate events.
 */
class MobileReaderDelegateAnnouncer: ReaderDelegateAnnouncer<MobileReaderDelegate>, MobileReaderDelegate {
    static let shared = MobileReaderDelegateAnnouncer()

    // MARK: - MobileReaderDelegate
    func reader(_ reader: Reader, didReportAvailableUpdate update: ReaderSoftwareUpdate) {
        announce { delegate in
            delegate.reader(reader, didReportAvailableUpdate: update)
        }
    }

    func reader(_ reader: Reader, didStartInstallingUpdate update: ReaderSoftwareUpdate, cancelable: Cancelable?) {
        announce { delegate in
            delegate.reader(reader, didStartInstallingUpdate: update, cancelable: cancelable)
        }
    }

    func reader(_ reader: Reader, didReportReaderSoftwareUpdateProgress progress: Float) {
        announce { delegate in
            delegate.reader(reader, didReportReaderSoftwareUpdateProgress: progress)
        }
    }

    func reader(_ reader: Reader, didFinishInstallingUpdate update: ReaderSoftwareUpdate?, error: Error?) {
        announce { delegate in
            delegate.reader(reader, didFinishInstallingUpdate: update, error: error)
        }
    }

    func reader(_ reader: Reader, didRequestReaderInput inputOptions: ReaderInputOptions = []) {
        announce { delegate in
            delegate.reader(reader, didRequestReaderInput: inputOptions)
        }
    }

    func reader(_ reader: Reader, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {
        announce { delegate in
            delegate.reader(reader, didRequestReaderDisplayMessage: displayMessage)
        }
    }

    func reader(_ reader: Reader, didReportReaderEvent event: ReaderEvent, info: [AnyHashable: Any]?) {
        announce { delegate in
            delegate.reader?(reader, didReportReaderEvent: event, info: info)
        }
    }

    func reader(_ reader: Reader, didReportBatteryLevel batteryLevel: Float, status: BatteryStatus, isCharging: Bool) {
        announce { delegate in
            delegate.reader?(reader, didReportBatteryLevel: batteryLevel, status: status, isCharging: isCharging)
        }
    }

    func readerDidReportLowBatteryWarning(_ reader: Reader) {
        announce { delegate in
            delegate.readerDidReportLowBatteryWarning?(reader)
        }
    }
}

// MARK: - TapToPayReaderDelegate

/**
 Allows the Example app to use a single persistent TapToPayReaderDelegate for the life of the connection
 and still have the view controllers receive the TapToPayReaderDelegate events.
 */
class TapToPayReaderDelegateAnnouncer: ReaderDelegateAnnouncer<TapToPayReaderDelegate>, TapToPayReaderDelegate {
    static let shared = TapToPayReaderDelegateAnnouncer()

    // MARK: - TapToPayReaderDelegate

    func tapToPayReader(
        _ reader: Reader,
        didStartInstallingUpdate update: ReaderSoftwareUpdate,
        cancelable: Cancelable?
    ) {
        announce { delegate in
            delegate.tapToPayReader(reader, didStartInstallingUpdate: update, cancelable: cancelable)
        }
    }

    func tapToPayReader(_ reader: Reader, didReportReaderSoftwareUpdateProgress progress: Float) {
        announce { delegate in
            delegate.tapToPayReader(reader, didReportReaderSoftwareUpdateProgress: progress)
        }
    }

    func tapToPayReader(_ reader: Reader, didFinishInstallingUpdate update: ReaderSoftwareUpdate?, error: Error?) {
        announce { delegate in
            delegate.tapToPayReader(reader, didFinishInstallingUpdate: update, error: error)
        }
    }

    func tapToPayReaderDidAcceptTermsOfService(_ reader: Reader) {
        announce { delegate in
            delegate.tapToPayReaderDidAcceptTermsOfService?(reader)
        }
    }

    func tapToPayReader(_ reader: Reader, didRequestReaderInput inputOptions: ReaderInputOptions = []) {
        announce { delegate in
            delegate.tapToPayReader(reader, didRequestReaderInput: inputOptions)
        }
    }

    func tapToPayReader(_ reader: Reader, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {
        announce { delegate in
            delegate.tapToPayReader(reader, didRequestReaderDisplayMessage: displayMessage)
        }
    }
}

// MARK: - InternetReaderDelegate

/**
 Allows the Example app to use a single persistent InternetReaderDelegate for the life of the connection
 and still have the view controllers receive the InternetReaderDelegate events.
 */
class InternetReaderDelegateAnnouncer: ReaderDelegateAnnouncer<InternetReaderDelegate>, InternetReaderDelegate {
    static let shared = InternetReaderDelegateAnnouncer()

    // All implementated in the ReaderDelegateAnnouncer
}

class OfflineDelegateAnnouncer: DelegateAnnouncer<OfflineDelegate>, OfflineDelegate {
    static let shared = OfflineDelegateAnnouncer()

    func terminal(_ terminal: Terminal, didChange offlineStatus: OfflineStatus) {
        announce { delegate in
            delegate.terminal(terminal, didChange: offlineStatus)
        }
    }

    func terminal(_ terminal: Terminal, didForwardPaymentIntent intent: PaymentIntent, error: Error?) {
        announce { delegate in
            delegate.terminal(terminal, didForwardPaymentIntent: intent, error: error)
        }
    }

    func terminal(_ terminal: Terminal, didReportForwardingError error: Error) {
        announce { delegate in
            delegate.terminal(terminal, didReportForwardingError: error)
        }
    }
}

final class WeakBox {
    weak var unbox: AnyObject?
    init(_ value: AnyObject) {
        unbox = value
    }
}

extension Array where Element: WeakBox {
    mutating func compact() {
        self.removeAll { $0.unbox == nil }
    }
}
