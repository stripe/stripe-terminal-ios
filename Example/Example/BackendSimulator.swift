//
//  BackendSimulator.swift
//  StripeTerminalFunctionalTests
//
//  Created by Ben Guo on 6/22/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import Foundation
import Alamofire

/**
 This backend simulator has been included as part of the example app's client
 side code for demonstration purposes only. Secret API keys should be kept
 confidential and stored only on your own servers. Your account’s secret API
 key can perform any API request to Stripe without restriction. You should
 _never_ hardcode your secret API key into your app, and only call these
 API endpoints from your backend.

 @see https://stripe.com/docs/keys
 */
@objc class BackendSimulator: NSObject {

    let defaultError = NSError(domain: "BackendSimulator",
                               code: 1,
                               userInfo: [
                                NSLocalizedDescriptionKey: "BackendSimulator request failed.",
                                ])

    let baseURL = URL(string: "https://api.stripe.com/v1/")!
    var apiKey: String

    init(secretAPIKey: String) {
        self.apiKey = secretAPIKey
    }

    /**
     Creates a Terminal Connection Token
     */
    func createConnectionToken(stripeAccount: String? = nil, completion: @escaping (String?, Error?) -> Void) {
        let url = self.baseURL.appendingPathComponent("terminal/connection_tokens")
        var headers: HTTPHeaders = [
            "Authorization": "Bearer \(self.apiKey)",
        ]
        headers["Stripe-Account"] = stripeAccount
        Alamofire.request(url,
                          method: .post,
                          parameters: nil,
                          headers: headers)
            .validate(statusCode: 200..<300)
            .responseJSON { response in
                let requestId = response.response?.allHeaderFields["Request-Id"] as? String
                switch response.result {
                case .success(let value):
                    if let json = value as? [String: AnyObject] {
                        if let token = json["secret"] as? String {
                            completion(token, nil)
                        }
                        else if json["error"] != nil {
                            if let requestId = requestId {
                                print("Request-Id: \(requestId)")
                            }
                            completion(nil, self.defaultError)
                        }
                        else {
                            completion(nil, self.defaultError)
                        }
                    }
                    else {
                        completion(nil, self.defaultError)
                    }
                case .failure(let error):
                    if let afError = error as? AFError,
                        let requestId = requestId,
                        afError.isResponseValidationError,
                        afError.responseCode == 404 {
                        let errorString = "ERROR: BackendSimulator could not create a connection token. The Stripe Terminal API is not yet available for your account. \(requestId)"
                        print(errorString)
                    }
                    else if let requestId = requestId {
                        print("Request-Id: \(requestId)")
                    }
                    completion(nil, error)
                }
        }
    }

    /**
     Captures a PaymentIntent
     @see https://stripe.com/docs/api#capture_charge
     */
    func capturePaymentIntent(_ paymentIntentId: String, stripeAccount: String?, completion: @escaping (Error?) -> Void) {
        let url = self.baseURL.appendingPathComponent("payment_intents")
            .appendingPathComponent(paymentIntentId)
            .appendingPathComponent("capture")
        var headers: HTTPHeaders = [
            "Authorization": "Bearer \(self.apiKey)",
        ]
        headers["Stripe-Account"] = stripeAccount
        print(url.absoluteString)
        Alamofire.request(url,
                          method: .post,
                          headers: headers)
            .validate(statusCode: 200..<300)
            .responseJSON { response in
                let requestId = response.response?.allHeaderFields["Request-Id"] as? String
                switch response.result {
                case .success(let value):
                    if let json = value as? [String: AnyObject] {
                        if json["error"] != nil {
                            if let requestId = requestId {
                                print("Request-Id: \(requestId)")
                            }
                            print(json)
                            completion(self.defaultError)
                        }
                        else {
                            completion(nil)
                        }
                    }
                    else {
                        completion(self.defaultError)
                    }
                case .failure(let error):
                    if let requestId = requestId {
                        print("Request-Id: \(requestId)")
                    }
                    print(error)
                    completion(error)
                }
        }
    }
}
