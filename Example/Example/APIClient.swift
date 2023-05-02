//
//  APIClient.swift
//  Stripe POS
//
//  Created by Ben Guo on 3/12/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import Foundation
import Alamofire
import StripeTerminal

class APIClient: NSObject, ConnectionTokenProvider {
    // This comes from `AppDelegate.backendUrl`, set URL there
    var baseURLString: String?

    private var baseURL: URL {
        if let urlString = self.baseURLString, let url = URL(string: urlString) {
            return url
        } else {
            fatalError()
        }
    }

    // MARK: ConnectionTokenProvider
    func fetchConnectionToken(_ completion: @escaping ConnectionTokenCompletionBlock) {
        let url = self.baseURL.appendingPathComponent("connection_token")

        AF.request(url, method: .post, parameters: [:])
            .validate(statusCode: 200..<300)
            .stripeResponseJSON { (result, afDataResponse) in
                switch result {
                case .success(let json):
                    if let secret = json["secret"] as? String {
                        completion(secret, nil)
                    } else {
                        fallthrough // fallthrough and report failed to decode
                    }
                case .failure where afDataResponse.response?.statusCode == 402:
                    let description = afDataResponse.data.flatMap({ String(data: $0, encoding: .utf8) })
                    ?? "Failed to decode connection token"
                    let error = NSError(domain: "example",
                                        code: 1,
                                        userInfo: [
                                            NSLocalizedDescriptionKey: description
                                        ])
                    completion(nil, error)
                case .failure(let error):
                    completion(nil, error)
                }
            }
    }

    // MARK: Endpoints for App

    /// Create PaymentIntent using https://github.com/stripe/example-terminal-backend
    ///
    /// - Parameters:
    ///   - params: parameters for PaymentIntent creation
    ///   - completion: called with result: either PaymentIntent client_secret, or the error
    func createPaymentIntent(_ params: PaymentIntentParameters, completion: @escaping (Swift.Result<String, Error>) -> Void) {
        let url = self.baseURL.appendingPathComponent("create_payment_intent")

        var cardPresent: Parameters = [:]

        let requestExtendedAuth = params.paymentMethodOptionsParameters.cardPresentParameters.requestExtendedAuthorization
        if requestExtendedAuth {
            cardPresent["request_extended_authorization"] = String(requestExtendedAuth)
        }

        let requestIncrementalAuth = params.paymentMethodOptionsParameters.cardPresentParameters.requestIncrementalAuthorizationSupport
        if requestIncrementalAuth {
            cardPresent["request_incremental_authorization_support"] = String(requestIncrementalAuth)
        }

        AF.request(url, method: .post,
                          parameters: [
                            "amount": params.amount,
                            "currency": params.currency,
                            "capture_method": params.captureMethod.toString(),
                            "description": params.statementDescriptor ?? "Example PaymentIntent",
                            "payment_method_types": params.paymentMethodTypes,
                            "payment_method_options": [
                                "card_present": cardPresent
                            ]
        ])
        .validate(statusCode: 200..<300)
        .stripeResponseJSON { (result, afDataResponse) in
            switch result {
            case .success(let json):
                if let secret = json["secret"] as? String {
                    completion(.success(secret))
                    return
                }
                fallthrough
            case .failure where afDataResponse.response?.statusCode == 402:
                let description = afDataResponse.data.flatMap({ String(data: $0, encoding: .utf8) })
                ?? "Failed to create PaymentIntent"
                let error = NSError(domain: "example",
                                    code: 4,
                                    userInfo: [
                                        NSLocalizedDescriptionKey: description
                                    ])
                completion(.failure(error))
            case .failure(let error):
                completion(.failure(error))
            }
        }
    }

    func capturePaymentIntent(_ paymentIntentId: String, completion: @escaping ErrorCompletionBlock) {
        let url = self.baseURL.appendingPathComponent("capture_payment_intent")
        AF.request(url, method: .post,
                          parameters: ["payment_intent_id": paymentIntentId])
            .validate(statusCode: 200..<300)
            .responseString { response in
                switch response.result {
                case .success:
                    completion(nil)
                case .failure where response.response?.statusCode == 402:
                    let description = response.data.flatMap({ String(data: $0, encoding: .utf8) })
                        ?? "Failed to capture PaymentIntent"
                    let error = NSError(domain: "example",
                                        code: 2,
                                        userInfo: [
                                            NSLocalizedDescriptionKey: description
                    ])
                    completion(error)
                case .failure(let error):
                    completion(error)
                }
        }
    }

    func attachPaymentMethod(_ paymentMethodId: String, completion: @escaping ([String: AnyObject]?, Error?) -> Void) {
        let url = self.baseURL.appendingPathComponent("attach_payment_method_to_customer")
        AF.request(url, method: .post,
                   parameters: ["payment_method_id": paymentMethodId])
        .validate(statusCode: 200..<300)
        .stripeResponseJSON { (result, afDataResponse) in
            switch result {
            case .success(let json):
                completion(json, nil)
            case .failure where afDataResponse.response?.statusCode == 402:
                let description = afDataResponse.data.flatMap({ String(data: $0, encoding: .utf8) })
                ?? "Failed to decode PaymentMethod & Customer"
                let error = NSError(domain: "example",
                                    code: 3,
                                    userInfo: [
                                        NSLocalizedDescriptionKey: description
                                    ])
                completion(nil, error)
            case .failure(let error):
                completion(nil, error)
            }
        }
    }

    func registerReader(withCode registrationCode: String, label: String, locationId: String, completion: @escaping ([String: AnyObject]?, Error?) -> Void) {
        let url = self.baseURL.appendingPathComponent("register_reader")
        AF.request(url, method: .post, parameters: [
            "label": label,
            "registration_code": registrationCode,
            "location": locationId
        ])
        .validate(statusCode: 200..<300)
        .stripeResponseJSON { (result, afDataResponse) in
            switch result {
            case .success(let json):
                completion(json, nil)
            case .failure where afDataResponse.response?.statusCode == 402:
                let description = afDataResponse.data.flatMap({ String(data: $0, encoding: .utf8) })
                ?? "Failed to decode registered reader"

                let error = NSError(domain: "example",
                                    code: 3,
                                    userInfo: [
                                        NSLocalizedDescriptionKey: description
                                    ])
                completion(nil, error)
            case .failure(let error):
                completion(nil, error)
            }
        }
    }

    /**
    Creates a Location with the specified displayName and address
     */
    func createLocation(displayName: String, address: [String: String], completion: @escaping (Location?, Error?) -> Void) {
        let url = self.baseURL.appendingPathComponent("create_location")
        let parameters: Parameters = [
            "display_name": displayName,
            "address": address
        ]

        AF.request(url, method: .post, parameters: parameters)
        .validate(statusCode: 200..<300)
        .stripeResponseJSON { (result, _) in
            switch result {
            case .success(let json):
                if let location = Location.decodedObject(fromJSON: json) {
                    completion(location, nil)
                } else {
                    completion(nil, NSError(domain: "example",
                                            code: 3,
                                            userInfo: [
                                                NSLocalizedDescriptionKey: "Failed to decode created location"
                                            ]))
                }
            case .failure(let error):
                completion(nil, error)
            }
        }
    }
}
