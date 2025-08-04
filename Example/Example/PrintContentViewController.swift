//
//  PrintContentViewController.swift
//  AppStore
//
//  Created by Philip Zhang on 6/23/25.
//  Copyright © 2025 Stripe. All rights reserved.
//

import Static
import StripeTerminal
import UIKit

class PrintContentViewController: EventDisplayingViewController {
    private let printContent: PrintContent

    init(printContent: PrintContent) {
        self.printContent = printContent
        super.init()
        self.currentCancelLogMethod = .print
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        print(content: printContent)
    }

    private func print(content: PrintContent) {
        var printEvent = LogEvent(method: .print)
        events.append(printEvent)
        Terminal.shared.print(
            content,
            completion: { error in
                printEvent.result = error != nil ? .errored : .succeeded
                if let error = error {
                    printEvent.object = .error(error as NSError)
                }
                self.events.append(printEvent)
                self.complete()
            }
        )
    }
}
