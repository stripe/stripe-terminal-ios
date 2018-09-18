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
        case succeeded
        case errored
        case message(String)

        var description: String {
            switch self {
            case .succeeded: return "succeeded"
            case .errored: return "errored"
            case .message(let string): return string
            }
        }
    }

    enum Method: String {
        case createPaymentIntent = "terminal.createPaymentIntent"
        case collectPaymentMethod = "terminal.collectPaymentMethod"
        case cancelCollectPaymentMethod = "terminal.cancelCollectPaymentMethod"
        case confirmPaymentIntent = "terminal.confirmPaymentIntent"
        case capturePaymentIntent = "backend.capturePaymentIntent"
        case waitingForReaderInput = "delegate.didBeginWaitingForReaderInput"
        case readSourcePrompt = "delegate.didRequestReaderInputPrompt"
        case readSource = "terminal.readSource"
    }

    let method: Method
    var object: Any? = nil
    var result: Result = .succeeded

    init(method: Method) {
        self.method = method
    }

    /// cell title
    var description: String {
        var string = ""
        switch method {
        case .waitingForReaderInput:
            return result.description
        case .readSourcePrompt:
            return result.description
        case .createPaymentIntent:
            switch result {
            case .succeeded: string = "Created PaymentIntent"
            case .errored: string = "Create PaymentIntent Failed"
            case .message(let message): string = message
            }
        case .collectPaymentMethod:
            switch result {
            case .succeeded: string = "Collected Payment Method"
            case .errored: string = "Collect Payment Method Failed"
            case .message(let message): string = message
            }
        case .confirmPaymentIntent:
            switch result {
            case .succeeded: string = "Confirmed PaymentIntent"
            case .errored: string = "Confirm PaymentIntent Failed"
            case .message(let message): string = message
            }
        case .capturePaymentIntent:
            switch result {
            case .succeeded: string = "Captured PaymentIntent"
            case .errored: string = "Capture PaymentIntent Failed"
            case .message(let message): string = message
            }
        case .readSource:
            switch result {
            case .succeeded: string = "Created Source"
            case .errored: string = "Read Source Failed"
            case .message(let message): string = message
            }
        case .cancelCollectPaymentMethod:
            switch result {
            case .succeeded: string = "Collect Payment Method Canceled"
            case .errored: string = "Cancel Collect Payment Method Failed"
            case .message(let message): string = message
            }
        }
        return string
    }

    var resultDetail: String {
        if let error = object as? Error {
            return error.localizedDescription
        }
        else if let _ = object as? PaymentIntent {
            return description
        }
        else {
            switch method {
            case .waitingForReaderInput:
                return "ReaderInputOptions: \(result)"
            case .readSourcePrompt:
                return "ReaderInputPrompt: \(result)"
            default:
                return description
            }
        }
    }

    var paymentIntentStatus: String? {
        if let intent = object as? PaymentIntent {
            if intent.status == .requiresConfirmation {
                return "requires_confirmation"
            }
            else if let status = intent.originalJSON["status"] as? String {
                return status
            }
            else {
                return "unknown"
            }
        }
        return nil
    }

    func prettyPrint(json: [AnyHashable: Any]) -> String? {
        var sanitizedJson: [AnyHashable: Any] = [:]
        for (key, value) in json {
            if let jsonable = value as? JSONDecodable {
                sanitizedJson[key] = jsonable.originalJSON
            }
            else if let describable = value as? CustomStringConvertible {
                sanitizedJson[key] = describable.description
            }
        }
        do {
            let data: Data = try JSONSerialization.data(withJSONObject: sanitizedJson,
                                                        options: .prettyPrinted)
            return String(data: data, encoding: .utf8)
        } catch _ {
            return json.description
        }
    }

    var objectTitle: String {
        if let _ = object as? NSError {
            return "ERROR"
        }
        else if let _ = object as? PaymentIntent {
            return "PAYMENTINTENT"
        }
        else if let _ = object as? CardPresentSource {
            return "SOURCE"
        }
        else {
            return "OBJECT"
        }
    }

    var objectDescription: String? {
        guard let object = object else { return nil }
        if let apiObject = object as? JSONDecodable,
            let prettyJson = prettyPrint(json: apiObject.originalJSON) {
            if let intent = object as? PaymentIntent,
                intent.status == .requiresConfirmation {
                return nil
            }
            return prettyJson
        }
        else if let error = object as? NSError {
            return prettyPrint(json: error.userInfo)
        }
        else if let describable = object as? CustomStringConvertible {
            return describable.description
        }
        return nil
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
        if let description = event.objectDescription {
            let view = MonospaceTextView(text: description)
            let title = event.objectTitle
            let header = Section.Extremity.title(title)
            let section = Section(header: header, rows: [], footer: Section.Extremity.autoLayoutView(view))
            sections.append(section)
        }
        dataSource.sections = sections
    }

    @objc func doneAction() {
        dismiss(animated: true, completion: nil)
    }

}


