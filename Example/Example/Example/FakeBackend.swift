//
//  FakeBackend.swift
//  StripePOSFunctionalTests
//
//  Created by Ben Guo on 6/22/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import Foundation
import Alamofire

/**
 This fake backend that has been included as part of the example app for
 demonstration purposes only. Secret API keys should be kept confidential and
 only stored on your own servers. Your account’s secret API key can perform any
 API request to Stripe without restriction. You should never hardcode your
 secret API key into your app.

 @see https://stripe.com/docs/keys
 */
@objc class FakeBackend: NSObject {

    let defaultError = NSError(domain: "FakeBackend",
                               code: 1,
                               userInfo: [
                                NSLocalizedDescriptionKey: "FakeBackend request failed.",
                                ])

    let baseURL = URL(string: "https://api.stripe.com/v1/")!
    var apiKey: String

    init(secretAPIKey: String) {
        self.apiKey = secretAPIKey
    }

    /**
     Creates a POS activation token
     */
    func createActivationToken(_ completion: @escaping (String?, Error?) -> Void) {
        let url = self.baseURL.appendingPathComponent("point_of_sale/activation_token")
        let headers: HTTPHeaders = [
            "Authorization": "Bearer \(self.apiKey)",
        ]
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
                        if let token = json["activation_token"] as? String {
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
                        let errorString = "ERROR: FakeBackend could not create an activation token. This account may not gated into the Point of Sale APIs. Please contact your account manager. Please include this request id in your email: \(requestId)"
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
     Charges a source
     @see https://stripe.com/docs/api#create_charge
     */
    func chargeSource(_ sourceId: String, amount: Int, currency: String, completion: @escaping (String?, Error?) -> Void) {
        let url = self.baseURL.appendingPathComponent("charges")
        let headers: HTTPHeaders = [
            "Authorization": "Bearer \(self.apiKey)",
        ]
        print(url.absoluteString)
        let params: [String: Any] = [
            "source": sourceId,
            "amount": amount,
            "currency": currency,
        ]
        Alamofire.request(url,
                          method: .post,
                          parameters: params,
                          headers: headers)
            .validate(statusCode: 200..<300)
            .responseJSON { response in
                let requestId = response.response?.allHeaderFields["Request-Id"] as? String
                switch response.result {
                case .success(let value):
                    if let json = value as? [String: AnyObject] {
                        if let chargeId = json["id"] as? String {
                            completion(chargeId, nil)
                        }
                        else if json["error"] != nil {
                            if let requestId = requestId {
                                print("Request-Id: \(requestId)")
                            }
                            print(json)
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
                    if let requestId = requestId {
                        print("Request-Id: \(requestId)")
                    }
                    print(error)
                    completion(nil, error)
                }
        }
    }

    /**
     Captures a payment intent
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

    /**
     Converts a card present source into a card source. You must attach a
     reusable source to a customer before making a charge request.
     @see https://stripe.com/docs/sources/customers#reusable-sources
     */
    func convertSource(_ cardPresentSourceId: String, completion: @escaping (String?, Error?) -> Void) {
        let url = self.baseURL.appendingPathComponent("sources")
        let headers: HTTPHeaders = [
            "Authorization": "Bearer \(self.apiKey)",
        ]
        let params: [String: Any] = [
            "type": "card",
            "card": [
                "card_present_source": cardPresentSourceId,
            ],
        ]
        print(url.absoluteString)
        Alamofire.request(url,
                          method: .post,
                          parameters: params,
                          headers: headers)
            .validate(statusCode: 200..<300)
            .responseJSON { response in
                let requestId = response.response?.allHeaderFields["Request-Id"] as? String
                switch response.result {
                case .success(let value):
                    if let json = value as? [String: AnyObject] {
                        if let sourceId = json["id"] as? String {
                            completion(sourceId, nil)
                        }
                        else if json["error"] != nil {
                            if let requestId = requestId {
                                print("Request-Id: \(requestId)")
                            }
                            print(json)
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
                    if let requestId = requestId {
                        print("Request-Id: \(requestId)")
                    }
                    completion(nil, error)
                }
        }
    }

}
