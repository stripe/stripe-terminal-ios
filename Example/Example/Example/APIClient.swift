//
//  APIClient.swift
//  Stripe POS
//
//  Created by Ben Guo on 3/12/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import Foundation
import Alamofire
import StripePOS

class APIClient: NSObject, SCPActivationTokenProvider {

    init(backend: FakeBackend) {
        self.backend = backend
        super.init()
    }
    private let backend: FakeBackend

    func getActivationToken(_ completion: @escaping SCPActivationTokenCompletionBlock) {
        self.backend.createActivationToken(completion)
    }

    func capturePaymentIntent(_ paymentIntentId: String, completion: @escaping SCPErrorCompletionBlock) {
        self.backend.capturePaymentIntent(paymentIntentId, stripeAccount: nil, completion: completion)
    }
}
