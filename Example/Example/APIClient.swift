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

    init(backend: BackendSimulator) {
        self.backend = backend
        super.init()
    }
    private let backend: BackendSimulator

    func fetchConnectionToken(_ completion: @escaping ConnectionTokenCompletionBlock) {
        self.backend.createConnectionToken(completion)
    }

    func capturePaymentIntent(_ paymentIntentId: String, completion: @escaping ErrorCompletionBlock) {
        self.backend.capturePaymentIntent(paymentIntentId, stripeAccount: nil, completion: completion)
    }
}
