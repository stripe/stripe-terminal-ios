//
//  DataRequest+StripeJSON.swift
//  Example
//
//  Created by Brian Cooke on 3/2/22.
//  Copyright © 2023 Stripe. All rights reserved.
//

import Alamofire

extension DataRequest {
    /**
     Simple pre-evaluation code that simplifies call sites by looking for the stripe expected error in the JSON
     and logs the request id to the console and calls the completion with a Result object with JSON or error.
     */
    @discardableResult
    public func stripeResponseJSON(completionHandler: @escaping ((result: Result<[String: AnyObject], Error>, afDataResponse: AFDataResponse<Data>)) -> ()) -> Self {
        response(queue: .main,
                 responseSerializer: DataResponseSerializer(),
                 completionHandler: { response in
            let result: (result: Result<[String: AnyObject], Error>, afDataResponse: AFDataResponse<Data>) = {
                if let url = response.request?.url {
                    print(url.absoluteString)
                }
                if let requestId = response.response?.allHeaderFields["request-id"] as? String {
                    print("Request-Id: \(requestId)")
                }
                if let error = response.error {
                    return (.failure(error), response)
                }
                guard let data = response.data else {
                    return (.failure(NSError(domain: "BackendSimulator", code: 10, userInfo: [
                        NSLocalizedDescriptionKey: "nil data response"
                    ])), response)
                }

                do {
                    let json = try JSONSerialization.jsonObject(with: data) as? [String: AnyObject]
                    // check for error from Stripe
                    if let error = json?["error"] as? [String: AnyObject] {
                        let message = error["message"] as? String
                        ?? error["code"] as? String
                        ?? error["type"] as? String
                        ?? "Unknown Stripe error"
                        return (.failure(NSError(domain: "BackendSimulator", code: 15, userInfo: [
                            NSLocalizedDescriptionKey: message
                        ])), response)
                    }

                    // Check for non-nil json and successful status code
                    if let json = json,
                       let statusCode = response.response?.statusCode,
                       (200..<300).contains(statusCode) {
                        return (.success(json), response)
                    } else {
                        // No stripe error message, but unsuccessful status code:
                        return (.failure(NSError(domain: "BackendSimulator", code: 20, userInfo: [
                            NSLocalizedDescriptionKey: "Unexpected status code: \(response.response?.statusCode ?? 1)"
                        ])), response)
                    }
                } catch {
                    return (.failure(error), response)
                }
            }()
            completionHandler(result)
        })
    }
}
