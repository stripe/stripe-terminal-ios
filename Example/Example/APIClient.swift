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
    var baseURLString: String? = nil

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
        Alamofire.request(url, method: .post, parameters: [:])
            .validate(statusCode: 200..<300)
            .responseJSON { responseJSON in
                switch responseJSON.result {
                case .success(let json as [String: AnyObject]) where json["secret"] is String:
                    completion((json["secret"] as! String), nil)
                case .success(_),
                     .failure where responseJSON.response?.statusCode == 402:
                    let description = responseJSON.data.flatMap({ String(data: $0, encoding: .utf8) })
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

    func capturePaymentIntent(_ paymentIntentId: String, completion: @escaping ErrorCompletionBlock) {
        let url = self.baseURL.appendingPathComponent("capture_payment_intent")
        Alamofire.request(url, method: .post,
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
                                            NSLocalizedDescriptionKey: description,
                                            ])
                    completion(error)
                case .failure(let error):
                    completion(error)
                }
        }
    }

    func attachPaymentMethod(_ paymentMethodId: String, completion: @escaping ([String: AnyObject]?, Error?) -> ()) {
        let url = self.baseURL.appendingPathComponent("attach_payment_method_to_customer")
        Alamofire.request(url, method: .post,
                          parameters: ["payment_method_id": paymentMethodId])
            .validate(statusCode: 200..<300)
            .responseJSON { responseJSON in
                switch responseJSON.result {
                case .success(let json as [String: AnyObject]):
                    completion(json, nil)
                case .success(_),
                     .failure where responseJSON.response?.statusCode == 402:
                    let description = responseJSON.data.flatMap({ String(data: $0, encoding: .utf8) })
                        ?? "Failed to decode PaymentMethod & Customer"
                    let error = NSError(domain: "example",
                                        code: 3,
                                        userInfo: [
                                            NSLocalizedDescriptionKey: description,
                                            ])
                    completion(nil, error)
                case .failure(let error):
                    completion(nil, error)
                }
        }
    }
}
