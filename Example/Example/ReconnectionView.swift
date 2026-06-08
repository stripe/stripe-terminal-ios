//
//  ReconnectionView.swift
//  Example
//
//  Copyright © 2026 Stripe. All rights reserved.
//

import SwiftUI

/// State machine for the reconnection overlay. One presentation, multiple state transitions.
enum ReconnectionState {
    case reconnecting(serialNumber: String, reason: String)
    case succeeded
    case failed
}

/// Observable model that drives the reconnection overlay.
class ReconnectionModel: ObservableObject {
    @Published var state: ReconnectionState = .reconnecting(serialNumber: "", reason: "")
    var onCancel: (() -> Void)?
    var onDismiss: (() -> Void)?
}

/// A single SwiftUI view presented once for the entire reconnect lifecycle.
/// State changes update the view in place — no dismiss/present races.
struct ReconnectionView: View {
    @ObservedObject var model: ReconnectionModel

    var body: some View {
        VStack(spacing: 20) {
            switch model.state {
            case .reconnecting(let serialNumber, let reason):
                ProgressView()
                    .scaleEffect(1.2)
                Text("Reconnecting...")
                    .font(.headline)
                Text("Reader \(serialNumber) has disconnected: \(reason)")
                    .font(.subheadline)
                    .foregroundColor(.secondary)
                    .multilineTextAlignment(.center)
                Button("Cancel") {
                    model.onCancel?()
                }

            case .succeeded:
                Image(systemName: "checkmark.circle.fill")
                    .font(.system(size: 40))
                    .foregroundColor(.green)
                Text("Reconnected!")
                    .font(.headline)
                Text("We were able to reconnect to the reader.")
                    .font(.subheadline)
                    .foregroundColor(.secondary)
                    .multilineTextAlignment(.center)
                Button("OK") {
                    model.onDismiss?()
                }

            case .failed:
                Image(systemName: "xmark.circle.fill")
                    .font(.system(size: 40))
                    .foregroundColor(.red)
                Text("Reader Disconnected")
                    .font(.headline)
                Text("Reader reconnection failed!")
                    .font(.subheadline)
                    .foregroundColor(.secondary)
                    .multilineTextAlignment(.center)
                Button("OK") {
                    model.onDismiss?()
                }
            }
        }
        .padding(30)
        .frame(maxWidth: 300)
        .background(Color(UIColor.systemBackground))
        .cornerRadius(14)
        .shadow(radius: 20)
    }
}
