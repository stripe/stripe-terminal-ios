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
                case .success(let json):
                    if let json = json as? [String: AnyObject],
                        let secret = json["secret"] as? String {
                        completion(secret, nil)
                    }
                    else {
                        let error = NSError(domain: "example",
                                            code: 1,
                                            userInfo: [
                                                NSLocalizedDescriptionKey: "Failed to decode connection token"
                            ])
                        completion(nil, error)
                    }
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
                case .failure(let error):
                    completion(error)
                }
        }
    }
}
