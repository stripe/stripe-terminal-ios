//
//  TapToPayAccountLinkedViewController.swift
//  Example
//
//  Created by Jamie Rollison on 3/26/26.
//  Copyright © 2026 Stripe. All rights reserved.
//

import Static
import StripeTerminal
import UIKit

@available(iOS 16.4, *)
class TapToPayAccountLinkedViewController: EventDisplayingViewController {

    private let onBehalfOf: String?

    init(onBehalfOf: String? = nil) {
        self.onBehalfOf = onBehalfOf
        super.init()
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        checkAccountLinked()
    }

    private func checkAccountLinked() {
        var event = LogEvent(method: .isTapToPayAccountLinked)
        self.events.append(event)

        Task {
            do {
                let isLinked = try await Terminal.shared.isTapToPayAccountLinked(onBehalfOf)
                event.result = .message("isLinked: \(isLinked.boolValue)")
            } catch {
                event.result = .errored
                event.object = .error(error as NSError)
            }
            self.events.append(event)
            self.complete()
        }
    }
}
