//
//  LogInfoViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/12/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit
import Static
import StripeTerminal

struct LogEvent: CustomStringConvertible {
    enum Result: CustomStringConvertible {
        case started
        case succeeded
        case errored
        case message(String)

        var description: String {
            switch self {
            case .started: return "started"
            case .succeeded: return "succeeded"
            case .errored: return "errored"
            case .message(let string): return string
            }
        }
    }

    enum Method: String {
        case createPaymentIntent = "terminal.createPaymentIntent"
        case backendCreatePaymentIntent = "backend.createPaymentIntent"
        case collectPaymentMethod = "terminal.collectPaymentMethod"
        case cancelCollectPaymentMethod = "terminal.cancelCollectPaymentMethod"
        case readReusableCard = "terminal.readReusableCard"
        case cancelReadReusableCard = "terminal.cancelReadReusableCard"
        case retrievePaymentIntent = "terminal.retrievePaymentIntent"
        case processPayment = "terminal.processPayment"
        case capturePaymentIntent = "backend.capturePaymentIntent"
        case requestReaderInput = "delegate.didRequestReaderInput"
        case requestReaderDisplayMessage = "delegate.didRequestReaderDisplayMessage"
        case reportReaderEvent = "delegate.didReportReaderEvent"
        case reportUnexpectedReaderDisconnect = "delegate.didReportUnexpectedReaderDisconnect"
        case attachPaymentMethod = "backend.attachPaymentMethod"
        case collectRefundPaymentMethod = "terminal.collectRefundPaymentMethod"
        case cancelCollectRefundPaymentMethod = "terminal.cancelCollectRefundPaymentMethod"
        case processRefund = "terminal.processRefund"
        case setReaderDisplay = "terminal.setReaderDisplay"
        case clearReaderDisplay = "terminal.clearReaderDisplay"
    }

    enum AssociatedObject {
        case none
        case error(NSError)
        case json([String: AnyObject])
        case paymentIntent(PaymentIntent)
        case paymentMethod(PaymentMethod)
        case refund(Refund)
        case object(CustomStringConvertible)
    }

    let method: Method
    var object: AssociatedObject = .none
    var result: Result = .started

    init(method: Method) {
        self.method = method
    }

    /// cell title
    var description: String {
        var string = ""
        switch method {
        case .requestReaderInput,
             .reportReaderEvent,
             .reportUnexpectedReaderDisconnect,
             .requestReaderDisplayMessage:
            return result.description
        case .createPaymentIntent, .backendCreatePaymentIntent:
            switch result {
            case .started: string = "Create PaymentIntent"
            case .succeeded: string = "Created PaymentIntent"
            case .errored: string = "Create PaymentIntent Failed"
            case .message(let message): string = message
            }
        case .collectPaymentMethod:
            switch result {
            case .started: string = "Collect PaymentMethod"
            case .succeeded: string = "Collected PaymentMethod"
            case .errored: string = "Collect PaymentMethod Failed"
            case .message(let message): string = message
            }
        case .processPayment:
            switch result {
            case .started: string = "Process Payment"
            case .succeeded: string = "Confirmed PaymentIntent"
            case .errored: string = "Confirm PaymentIntent Failed"
            case .message(let message): string = message
            }
        case .capturePaymentIntent:
            switch result {
            case .started: string = "Capture PaymentIntent"
            case .succeeded: string = "Captured PaymentIntent"
            case .errored: string = "Capture PaymentIntent Failed"
            case .message(let message): string = message
            }
        case .readReusableCard:
            switch result {
            case .started: string = "Read Reusable Card"
            case .succeeded: string = "Created Reusable Card"
            case .errored: string = "Read Reusable Card Failed"
            case .message(let message): string = message
            }
        case .retrievePaymentIntent:
            switch result {
            case .started: string = "Retrieve PaymentIntent"
            case .succeeded: string = "Retrieved PaymentIntent"
            case .errored: string = "Retrieve PaymentIntent Failed"
            case .message(let message): string = message
            }
        case .cancelCollectPaymentMethod:
            switch result {
            case .started: string = "Cancel Collect PaymentMethod"
            case .succeeded: string = "Canceled Collect PaymentMethod"
            case .errored: string = "Cancel Collect Payment Method Failed"
            case .message(let message): string = message
            }
        case .cancelReadReusableCard:
            switch result {
            case .started: string = "Cancel Read Reusable Card"
            case .succeeded: string = "Canceled Read Reusable Card"
            case .errored: string = "Cancel Read Reusable Card Failed"
            case .message(let message): string = message
            }
        case .attachPaymentMethod:
            switch result {
            case .started: string = "Attach PaymentMethod"
            case .succeeded: string = "Attached PaymentMethod"
            case .errored: string = "Attach PaymentMethod Failed"
            case .message(let message): string = message
            }
        case .collectRefundPaymentMethod:
            switch result {
            case .started: string = "Collect Refund PaymentMethod"
            case .succeeded: string = "Collected Refund PaymentMethod"
            case .errored: string = "Collect Refund PaymentMethod Failed"
            case .message(let message): string = message
            }
        case .processRefund:
            switch result {
            case .started: string = "Process Refund"
            case .succeeded: string = "Processed Refund"
            case .errored: string = "Process Refund Failed"
            case .message(let message): string = message
            }
        case .cancelCollectRefundPaymentMethod:
            switch result {
            case .started: string = "Cancel Collect Refund PaymentMethod"
            case .succeeded: string = "Canceled Collect Refund PaymentMethod"
            case .errored: string = "Cancel Collect Refund PaymentMethod Failed"
            case .message(let message): string = message
            }
        case .setReaderDisplay:
            switch result {
            case .started: string = "Setting Reader Display"
            case .succeeded: string = "Set Reader Display"
            case .errored: string = "Set Reader Display Failed"
            case .message(let message): string = message
            }
        case .clearReaderDisplay:
            switch result {
            case .started: string = "Clear Reader Display"
            case .succeeded: string = "Cleared Reader Display"
            case .errored: string = "Clear Reader Display Failed"
            case .message(let message): string = message
            }
        }
        return string
    }

    var resultDetail: String {
        if case .error(let error) = object {
            return error.localizedDescription
        } else if case .paymentIntent = object {
            return description
        } else {
            switch method {
            case .requestReaderInput:
                return "ReaderInputOptions: \(result)"
            case .requestReaderDisplayMessage:
                return "ReaderDisplayMessage: \(result)"
            default:
                return description
            }
        }
    }

    var paymentIntentStatus: String? {
        if case .paymentIntent(let intent) = object {
            if intent.status == .requiresConfirmation {
                return "requires_confirmation"
            } else if let status = intent.originalJSON["status"] as? String {
                return status
            } else {
                return "unknown"
            }
        }
        return nil
    }
}

extension LogEvent.AssociatedObject {
    var title: String {
        switch self {
        case .none: return "NONE"
        case .error(is ProcessPaymentError): return "PROCESS PAYMENT ERROR"
        case .error: return "ERROR"
        case .json: return "OBJECT"
        case .paymentIntent: return "PAYMENTINTENT"
        case .paymentMethod: return "PAYMENTMETHOD"
        case .refund: return "REFUND"
        case .object: return "OBJECT"
        }
    }

    var description: String? {
        switch self {
        case .none:
            return nil
        case .error(let error as ProcessPaymentError):
            var userInfoToPrint = error.userInfo
            userInfoToPrint.removeValue(forKey: ErrorKey.stripeAPIPaymentIntent.rawValue)

            var output = """
            Error Domain: \(error.domain)
            Error Code: \(error.code)

            """
            if let requestError = error.requestError {
                output += """
                Request Error: \(requestError.localizedDescription)

                """
            }
            if let declineCode = error.declineCode {
                output += """
                Decline Code: \(declineCode)

                """
            }
            output += """

            Error UserInfo: \(prettyPrint(json: userInfoToPrint))

            """
            if let intent = error.paymentIntent {
                output += """

                PaymentIntent: \(prettyPrint(json: intent.originalJSON))
                """
            }

            return output
        case .error(let error):
            return prettyPrint(json: error.userInfo)
        case .json(let json):
            return prettyPrint(json: json)
        case .paymentIntent(let intent) where intent.status == .requiresConfirmation:
            return nil
        case .paymentIntent(let intent):
            return prettyPrint(json: intent.originalJSON)
        case .paymentMethod(let paymentMethod):
            return prettyPrint(json: paymentMethod.originalJSON)
        case .refund(let refund):
            return prettyPrint(json: refund.originalJSON)
        case .object(let object):
            return object.description
        }
    }

    func prettyPrint(json: [AnyHashable: Any]) -> String {
        var sanitizedJson: [AnyHashable: Any] = [:]
        if JSONSerialization.isValidJSONObject(json) {
            // easy case: most of the times this method is called is using a dict that came from JSON
            sanitizedJson = json
        } else {
            for (key, value) in json {
                if JSONSerialization.isValidJSONObject(value) {
                    sanitizedJson[key] = value
                } else if let jsonable = value as? JSONDecodable {
                    sanitizedJson[key] = jsonable.originalJSON
                } else if let describable = value as? CustomStringConvertible {
                    sanitizedJson[key] = describable.description
                }
            }
        }
        do {
            let data: Data = try JSONSerialization.data(withJSONObject: sanitizedJson,
                                                        options: .prettyPrinted)
            return String(data: data, encoding: .utf8) ?? sanitizedJson.description
        } catch _ {
            return json.description
        }
    }
}

class LogEventViewController: TableViewController {

    private let event: LogEvent

    init(event: LogEvent) {
        self.event = event
        super.init(style: .grouped)
        self.title = "Event"
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        self.addKeyboardDisplayObservers()

        var sections: [Section] = []
        let methodView = MonospaceTextView(text: event.method.rawValue)
        let methodSection = Section(header: "METHOD", rows: [], footer: Section.Extremity.autoLayoutView(methodView))
        sections.append(methodSection)
        let resultView = MonospaceTextView(text: event.resultDetail)
        let resultSection = Section(header: "RESULT", rows: [], footer: Section.Extremity.autoLayoutView(resultView))
        sections.append(resultSection)
        if let status = event.paymentIntentStatus {
            let view = MonospaceTextView(text: status)
            let section = Section(header: "STATUS", rows: [], footer: Section.Extremity.autoLayoutView(view))
            sections.append(section)
        }
        if let description = event.object.description {
            let view = MonospaceTextView(text: description)
            let title = event.object.title
            let header = Section.Extremity.title(title)
            let section = Section(header: header, rows: [], footer: Section.Extremity.autoLayoutView(view))
            sections.append(section)
        }
        dataSource.sections = sections
    }

    @objc
    func doneAction() {
        dismiss(animated: true, completion: nil)
    }

}
