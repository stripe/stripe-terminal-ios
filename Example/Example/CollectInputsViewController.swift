//
//  CollectInputsViewController.swift
//  Example
//
//  Created by Stephen Lee on 11/2/23.
//  Copyright © 2023 Stripe. All rights reserved.
//

import Static
import StripeTerminal
import UIKit

class CollectInputsViewController: EventDisplayingViewController {
    private let collectInputsParams: CollectInputsParameters

    init(collectInputsParams: CollectInputsParameters) {
        self.collectInputsParams = collectInputsParams
        super.init()
        self.currentCancelLogMethod = .cancelCollectInputs
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        collectInputs(collectInputsParams: collectInputsParams)
    }

    private func collectInputs(collectInputsParams: CollectInputsParameters) {
        var collectInputsEvent = LogEvent(method: .collectInputs)
        self.events.append(collectInputsEvent)
        self.cancelable = Terminal.shared.collectInputs(collectInputsParams) { (collectInputsResult, error) in
            if let error = error {
                collectInputsEvent.result = .errored
                collectInputsEvent.object = .error(error as NSError)
                self.events.append(collectInputsEvent)
                self.complete()
            } else if let result = collectInputsResult {
                collectInputsEvent.result = .succeeded
                collectInputsEvent.object = .collectInputs(result)
                self.events.append(collectInputsEvent)
                self.complete()
            }
        }
    }
}
