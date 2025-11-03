//
//  SetupIntentViewController.swift
//  AppStore
//
//  Created by James Little on 1/13/21.
//  Copyright © 2021 Stripe. All rights reserved.
//

import Static
import StripeTerminal
import UIKit

class SetupIntentViewController: EventDisplayingViewController {
    private let setupParams: SetupIntentParameters
    private let setupConfig: CollectSetupIntentConfiguration
    private let allowRedisplay: AllowRedisplay
    private let useProcessSetupIntent: Bool

    init(
        setupParams: SetupIntentParameters,
        setupConfig: CollectSetupIntentConfiguration,
        allowRedisplay: AllowRedisplay,
        useProcessSetupIntent: Bool
    ) {
        self.setupParams = setupParams
        self.setupConfig = setupConfig
        self.allowRedisplay = allowRedisplay
        self.useProcessSetupIntent = useProcessSetupIntent
        super.init()
        self.currentCancelLogMethod = .cancelCollectSetupIntentPaymentMethod
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        // This sets the EventDisplayingVC's task which then will cancel the task when requested.
        task = Task {
            do {
                defer {
                    self.task = nil
                    self.complete()
                }

                let intent = try await createSetupIntent(self.setupParams)

                if useProcessSetupIntent {
                    // Use processSetupIntent (combined collect + confirm)
                    _ = try await processSetupIntent(intent: intent)
                } else {
                    // Use separate flow
                    let collectedIntent = try await collectSetupIntent(intent: intent)
                    _ = try await confirmSetupIntent(intent: collectedIntent)
                }
            } catch {
                // All error logging is handled in individual methods
            }
        }
    }

    private func createSetupIntent(_ params: SetupIntentParameters) async throws -> SetupIntent {
        var createEvent = LogEvent(method: .createSetupIntent)
        self.events.append(createEvent)

        do {
            let createdSetupIntent = try await Terminal.shared.createSetupIntent(params)

            createEvent.result = .succeeded
            createEvent.object = .setupIntent(createdSetupIntent)
            self.events.append(createEvent)

            return createdSetupIntent
        } catch {
            createEvent.result = .errored
            createEvent.object = .error(error as NSError)
            self.events.append(createEvent)
            throw error
        }
    }

    private func collectSetupIntent(intent: SetupIntent) async throws -> SetupIntent {
        var event = LogEvent(method: .collectSetupIntentPaymentMethod)

        do {
            self.events.append(event)
            let collectedSetupIntent = try await Terminal.shared.collectSetupIntentPaymentMethod(
                intent,
                allowRedisplay: self.allowRedisplay,
                setupConfig: self.setupConfig
            )
            self.handleSetupResult(collectedSetupIntent, event: &event)
            return collectedSetupIntent
        } catch {
            self.handleSetupResult(intent, event: &event)
            throw error
        }
    }

    private func confirmSetupIntent(intent: SetupIntent) async throws -> SetupIntent {
        var confirmEvent = LogEvent(method: .confirmSetupIntent)

        do {
            self.events.append(confirmEvent)
            let confirmedSetupIntent = try await Terminal.shared.confirmSetupIntent(intent)
            self.handleSetupResult(confirmedSetupIntent, event: &confirmEvent)
            return confirmedSetupIntent
        } catch {
            self.handleSetupError(error, event: &confirmEvent)
            throw error
        }
    }

    private func processSetupIntent(intent: SetupIntent) async throws -> SetupIntent {
        var processEvent = LogEvent(method: .processSetupIntent)
        self.events.append(processEvent)

        do {
            let processedSetupIntent = try await Terminal.shared.processSetupIntent(
                intent,
                allowRedisplay: self.allowRedisplay,
                collectConfig: self.setupConfig
            )

            self.handleSetupResult(processedSetupIntent, event: &processEvent)

            return processedSetupIntent
        } catch {
            self.handleSetupError(error, event: &processEvent)
            throw error
        }
    }

    private func handleSetupError(_ error: Error, event: inout LogEvent) {
        event.result = .errored
        event.object = .error(error as NSError)
        self.events.append(event)
    }

    private func handleSetupResult(_ intent: SetupIntent, event: inout LogEvent) {
        if intent.status == .succeeded || intent.status == .requiresConfirmation {
            event.result = .succeeded
            event.object = .setupIntent(intent)
            self.events.append(event)
        } else {
            event.result = .errored
            event.object = .setupIntent(intent)
            self.events.append(event)
        }
    }
}
