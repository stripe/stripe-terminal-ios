//
//  LogInfoViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/12/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import Static
import StripeTerminal
import UIKit

protocol Event {
    var result: LogEvent.Result { get }
    var method: LogEvent.Method? { get }
    var description: String { get }
    var viewController: UIViewController { get }
}

struct LogEvent: CustomStringConvertible, Event {
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
        case retrievePaymentIntent = "terminal.retrievePaymentIntent"
        case confirmPaymentIntent = "terminal.confirmPaymentIntent"
        case capturePaymentIntent = "backend.capturePaymentIntent"
        case requestReaderInput = "delegate.didRequestReaderInput"
        case requestReaderDisplayMessage = "delegate.didRequestReaderDisplayMessage"
        case reportReaderEvent = "delegate.didReportReaderEvent"
        case attachPaymentMethod = "backend.attachPaymentMethod"
        case collectRefundPaymentMethod = "terminal.collectRefundPaymentMethod"
        case cancelCollectRefundPaymentMethod = "terminal.cancelCollectRefundPaymentMethod"
        case confirmRefund = "terminal.confirmRefund"
        case setReaderDisplay = "terminal.setReaderDisplay"
        case clearReaderDisplay = "terminal.clearReaderDisplay"
        case createSetupIntent = "terminal.createSetupIntent"
        case collectSetupIntentPaymentMethod = "terminal.collectSetupIntentPaymentMethod"
        case cancelCollectSetupIntentPaymentMethod = "terminal.cancelCollectSetupIntentPaymentMethod"
        case confirmSetupIntent = "terminal.confirmSetupIntent"
        case backendCreateSetupIntent = "backend.createSetupIntent"
        case retrieveSetupIntent = "backend.retrieveSetupIntent"
        case captureSetupIntent = "backend.captureSetupIntent"
        case cancelPaymentIntent = "terminal.cancelPaymentIntent"
        case cancelSetupIntent = "terminal.cancelSetupIntent"
        case collectInputs = "terminal.collectInputs"
        case cancelCollectInputs = "terminal.cancelCollectInputs"
        case collectData = "terminal.collectData"
        case cancelCollectData = "terminal.cancelCollectData"
        case retrieveCollectedData = "terminal.retrieveCollectedData"
        case cancelConfirmPaymentIntent = "terminal.cancelConfirmPaymentIntent"
        case cancelConfirmSetupIntent = "terminal.cancelConfirmSetupIntent"
        case cancelConfirmRefund = "terminal.cancelConfirmRefund"
        case print = "terminal.print"
    }

    enum AssociatedObject {
        case none
        case error(NSError)
        case json([String: AnyObject])
        case paymentIntent(PaymentIntent)
        case paymentMethod(PaymentMethod)
        case refund(Refund)
        case setupIntent(SetupIntent)
        case collectInputs([CollectInputsResult])
        case collectedData(CollectedData)
        case object(CustomStringConvertible)
    }

    let method: Method?
    var object: AssociatedObject = .none
    var result: Result = .started

    init(method: Method) {
        self.method = method
    }

    /// cell title
    var description: String {
        var string = ""
        guard let method = self.method else {
            return "Unknown"
        }
        switch method {
        case .requestReaderInput,
            .reportReaderEvent,
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
        case .confirmPaymentIntent:
            switch result {
            case .started: string = "Confirm Payment"
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
        case .confirmRefund:
            switch result {
            case .started: string = "Confirm Refund"
            case .succeeded: string = "Confirmed Refund"
            case .errored: string = "Confirm Refund Failed"
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
        case .createSetupIntent, .backendCreateSetupIntent:
            switch result {
            case .started: string = "Create SetupIntent"
            case .succeeded: string = "Created SetupIntent"
            case .errored: string = "Create SetupIntent Failed"
            case .message(let message): string = message
            }
        case .cancelCollectSetupIntentPaymentMethod:
            switch result {
            case .started: string = "Cancel Collect SetupIntent PaymentMethod"
            case .succeeded: string = "Canceled Collect SetupIntent PaymentMethod"
            case .errored: string = "Cancel Collect SetupIntent PaymentMethod Failed"
            case .message(let message): string = message
            }
        case .collectSetupIntentPaymentMethod:
            switch result {
            case .started: string = "Collect SetupIntent PaymentMethod"
            case .succeeded: string = "Collected SetupIntent PaymentMethod"
            case .errored: string = "Collect SetupIntent PaymentMethod Failed"
            case .message(let message): string = message
            }
        case .confirmSetupIntent:
            switch result {
            case .started: string = "Confirm SetupIntent"
            case .succeeded: string = "Confirmed SetupIntent"
            case .errored: string = "Confirm SetupIntent Failed"
            case .message(let message): string = message
            }
        case .retrieveSetupIntent:
            switch result {
            case .started: string = "Retrieve SetupIntent"
            case .succeeded: string = "Retrieved SetupIntent"
            case .errored: string = "Retrieve SetupIntent Failed"
            case .message(let message): string = message
            }
        case .captureSetupIntent:
            switch result {
            case .started: string = "Capture SetupIntent"
            case .succeeded: string = "Captured SetupIntent"
            case .errored: string = "Capture SetupIntent Failed"
            case .message(let message): string = message
            }
        case .cancelPaymentIntent:
            switch result {
            case .started: string = "Cancel PaymentIntent"
            case .succeeded: string = "Canceled PaymentIntent"
            case .errored: string = "Cancel PaymentIntent Failed"
            case .message(let message): string = message
            }
        case .cancelSetupIntent:
            switch result {
            case .started: string = "Cancel SetupIntent"
            case .succeeded: string = "Canceled SetupIntent"
            case .errored: string = "Cancel SetupIntent Failed"
            case .message(let message): string = message
            }
        case .collectInputs:
            switch result {
            case .started: string = "Started CollectInputs"
            case .succeeded: string = "Completed CollectInputs"
            case .errored: string = "CollectInputs Failed"
            case .message(let message): string = message
            }
        case .cancelCollectInputs:
            switch result {
            case .started: string = "Cancel CollectInputs"
            case .succeeded: string = "Canceled CollectInputs"
            case .errored: string = "Cancel CollectInputs Failed"
            case .message(let message): string = message
            }
        case .collectData:
            switch result {
            case .started: string = "Started CollectData"
            case .succeeded: string = "Completed CollectData"
            case .errored: string = "CollectData Failed"
            case .message(let message): string = message
            }
        case .cancelCollectData:
            switch result {
            case .started: string = "Cancel CollectData"
            case .succeeded: string = "Canceled CollectData"
            case .errored: string = "Cancel CollectData Failed"
            case .message(let message): string = message
            }
        case .retrieveCollectedData:
            switch result {
            case .started: string = "Retrieve Collected Data"
            case .succeeded: string = "Retrieved Collected Data"
            case .errored: string = "Retrieve Collected Data Failed"
            case .message(let message): string = message
            }
        case .cancelConfirmPaymentIntent:
            switch result {
            case .started: string = "Cancel Confirm PaymentIntent"
            case .succeeded: string = "Canceled Confirm PaymentIntent"
            case .errored: string = "Cancel Confirm Payment Intent Failed"
            case .message(let message): string = message
            }
        case .cancelConfirmSetupIntent:
            switch result {
            case .started: string = "Cancel Confirm SetupIntent"
            case .succeeded: string = "Canceled Confirm SetupIntent"
            case .errored: string = "Cancel Confirm Setup Intent Failed"
            case .message(let message): string = message
            }
        case .cancelConfirmRefund:
            switch result {
            case .started: string = "Cancel Confirm Refund"
            case .succeeded: string = "Canceled Confirm Refund"
            case .errored: string = "Cancel Confirm Refund Failed"
            case .message(let message): string = message
            }
        case .print:
            switch result {
            case .started: string = "Print Content"
            case .succeeded: string = "Printing succeeded"
            case .errored: string = "Printing failed"
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
            return Terminal.stringFromPaymentIntentStatus(intent.status)
        }
        return nil
    }

    var viewController: UIViewController {
        LogEventViewController(event: self)
    }
}

extension LogEvent.AssociatedObject {
    var title: String {
        switch self {
        case .none: return "NONE"
        case .error(is ConfirmPaymentIntentError): return "CONFIRM PAYMENT ERROR"
        case .error(is ConfirmSetupIntentError): return "CONFIRM SETUPINTENT ERROR"
        case .error: return "ERROR"
        case .json: return "OBJECT"
        case .paymentIntent: return "PAYMENTINTENT"
        case .paymentMethod: return "PAYMENTMETHOD"
        case .refund: return "REFUND"
        case .setupIntent: return "SETUPINTENT"
        case .collectInputs: return "COLLECTINPUTS"
        case .collectedData: return "COLLECTDATA"
        case .object: return "OBJECT"
        }
    }

    var description: String? {
        switch self {
        case .none:
            return nil
        case .error(let error as ConfirmPaymentIntentError):
            var userInfoToPrint = error.userInfo
            userInfoToPrint.removeValue(forKey: ErrorKey.stripeAPIPaymentIntent.rawValue)

            var output = """
                Error Domain: \(error.domain)
                Error Code: \(prettyPrintErrorCode(error))

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
            return """
                Error Domain: \(error.domain)
                Error Code: \(prettyPrintErrorCode(error))
                Error User Info: \(prettyPrint(json: error.userInfo))
                """
        case .json(let json):
            return prettyPrint(json: json)
        case .paymentIntent(let intent):
            return !intent.originalJSON.isEmpty
                ? "\(prettyPrint(json: intent.originalJSON)) \nOFFLINE DETAILS:\n\(intent.offlineDetails.debugDescription)"
                : intent.debugDescription
        case .paymentMethod(let paymentMethod):
            return prettyPrint(json: paymentMethod.originalJSON)
        case .refund(let refund):
            return prettyPrint(json: refund.originalJSON)
        case .setupIntent(let setupIntent):
            return prettyPrint(json: setupIntent.originalJSON)
        case .collectInputs(let collectInputs):
            return collectInputs.description
        case .collectedData(let collectedData):
            return collectedData.description
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
            let data = try JSONSerialization.data(
                withJSONObject: sanitizedJson,
                options: [.prettyPrinted, .sortedKeys]
            )
            return String(data: data, encoding: .utf8) ?? sanitizedJson.description
        } catch _ {
            return json.description
        }
    }

    private func prettyPrintErrorCode(_ error: NSError) -> String {
        if error.domain == StripeTerminal.ErrorDomain {
            let errorCode = ErrorCode(_nsError: error)
            return Terminal.stringFromError(errorCode.code)
        } else {
            return "\(error.code)"
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
        let methodView = MonospaceTextView(text: event.method?.rawValue ?? "Unknown Event")
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
