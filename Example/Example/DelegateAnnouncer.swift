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
    func terminal(_ terminal: Terminal, didReportUnexpectedReaderDisconnect reader: Reader) {
        announce { delegate in
            delegate.terminal(terminal, didReportUnexpectedReaderDisconnect: reader)
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
}

/**
 Allows the Example app to use a single persistent BluetoothReaderDelegate for the life of the connection
 and still have the view controllers receive the BluetoothReaderDelegate events.
 */
class BluetoothReaderDelegateAnnouncer: DelegateAnnouncer<BluetoothReaderDelegate>, BluetoothReaderDelegate {
    static let shared = BluetoothReaderDelegateAnnouncer()

    // MARK: - BluetoothReaderDelegate
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

/**
 Allows the Example app to use a single persistent LocalMobileReaderDelegate for the life of the connection
 and still have the view controllers receive the LocalMobileReaderDelegate events.
 */
class LocalMobileReaderDelegateAnnouncer: DelegateAnnouncer<LocalMobileReaderDelegate>, LocalMobileReaderDelegate {
    static let shared = LocalMobileReaderDelegateAnnouncer()

    // MARK: - LocalMobileReaderDelegate

    func localMobileReader(_ reader: Reader, didStartInstallingUpdate update: ReaderSoftwareUpdate, cancelable: Cancelable?) {
        announce { delegate in
            delegate.localMobileReader(reader, didStartInstallingUpdate: update, cancelable: cancelable)
        }
    }

    func localMobileReader(_ reader: Reader, didReportReaderSoftwareUpdateProgress progress: Float) {
        announce { delegate in
            delegate.localMobileReader(reader, didReportReaderSoftwareUpdateProgress: progress)
        }
    }

    func localMobileReader(_ reader: Reader, didFinishInstallingUpdate update: ReaderSoftwareUpdate?, error: Error?) {
        announce { delegate in
            delegate.localMobileReader(reader, didFinishInstallingUpdate: update, error: error)
        }
    }

    func localMobileReaderDidAcceptTermsOfService(_ reader: Reader) {
        announce { delegate in
            delegate.localMobileReaderDidAcceptTermsOfService?(reader)
        }
    }

    func localMobileReader(_ reader: Reader, didRequestReaderInput inputOptions: ReaderInputOptions = []) {
        announce { delegate in
            delegate.localMobileReader(reader, didRequestReaderInput: inputOptions)
        }
    }

    func localMobileReader(_ reader: Reader, didRequestReaderDisplayMessage displayMessage: ReaderDisplayMessage) {
        announce { delegate in
            delegate.localMobileReader(reader, didRequestReaderDisplayMessage: displayMessage)
        }
    }
}

class ReconnectionDelegateAnnouncer: DelegateAnnouncer<ReconnectionDelegate>, ReconnectionDelegate {
    static let shared = ReconnectionDelegateAnnouncer()

    func reader(_ reader: Reader, didStartReconnect cancelable: Cancelable) {
        announce { delegate in
            delegate.reader(reader, didStartReconnect: cancelable)
        }
    }

    func readerDidFailReconnect(_ reader: Reader) {
        announce { delegate in
            delegate.readerDidFailReconnect(reader)
        }
    }

    func readerDidSucceedReconnect(_ reader: Reader) {
        announce { delegate in
            delegate.readerDidSucceedReconnect(reader)
        }
    }
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
