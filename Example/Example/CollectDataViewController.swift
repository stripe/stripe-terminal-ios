//
//  CollectDataViewController.swift
//  Example
//
//  Created by Mindy Lou on 5/9/24.
//  Copyright © 2024 Stripe. All rights reserved.
//

import Static
import StripeTerminal
import UIKit

class CollectDataViewController: EventDisplayingViewController {
    private let collectDataConfig: CollectDataConfiguration

    init(collectDataConfiguration: CollectDataConfiguration) {
        self.collectDataConfig = collectDataConfiguration
        super.init()
        self.currentCancelLogMethod = .cancelCollectData
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        collectData(config: collectDataConfig)
    }

    private func collectData(config: CollectDataConfiguration) {
        var collectDataEvent = LogEvent(method: .collectData)
        events.append(collectDataEvent)

        task = Task {
            do {
                let collectedDataResult = try await Terminal.shared.collectData(collectDataConfig)

                collectDataEvent.result = .succeeded

                switch collectedDataResult {
                case .magstripe(let magstripeData):
                    collectDataEvent.object = .collectedData(magstripeData)
                    events.append(collectDataEvent)
                    #if SCP_RETRIEVES_COLLECTED_DATA
                    if let id = magstripeData.stripeId {
                        var retrieveCollectedDataEvent = LogEvent(method: .retrieveCollectedData)
                        self.events.append(retrieveCollectedDataEvent)
                        AppDelegate.apiClient?.retrieveReaderCollectedData(
                            id: id,
                            completion: { json, error in
                                if let error = error {
                                    retrieveCollectedDataEvent.result = .errored
                                    retrieveCollectedDataEvent.object = .error(error as NSError)
                                } else if let json = json {
                                    retrieveCollectedDataEvent.result = .succeeded
                                    retrieveCollectedDataEvent.object = .json(json)
                                }
                                self.events.append(retrieveCollectedDataEvent)
                                self.complete()
                            }
                        )
                    }
                    #else
                    self.complete()
                    #endif
                case .nfcUid(let nfcUidData):
                    collectDataEvent.object = .collectedData(nfcUidData)
                    events.append(collectDataEvent)
                    self.complete()
                }
            } catch {
                collectDataEvent.result = .errored
                collectDataEvent.object = .error(error as NSError)
                events.append(collectDataEvent)
                self.complete()
            }
        }
    }
}
