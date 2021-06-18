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
