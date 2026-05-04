//
//  TestReaderUpdateConfigurationViewController.swift
//  Example
//
//  Copyright © 2026 Stripe. All rights reserved.
//

import StripeTerminal
import SwiftUI
import UIKit

enum TestReaderUpdateSelection: String, CaseIterable, CustomStringConvertible {
    case none
    case random
    case available
    case required
    case requiredOffline
    case lowBattery
    case lowBatterySucceedConnect

    var description: String {
        switch self {
        case .none:
            return "None"
        case .random:
            return "Random"
        case .available:
            return "Available"
        case .required:
            return "Required"
        case .requiredOffline:
            return "Required (Offline)"
        case .lowBattery:
            return "Low Battery"
        case .lowBatterySucceedConnect:
            return "Low Battery (Succeed Connect)"
        }
    }
}

private final class TestReaderUpdateConfigurationViewModel: ObservableObject {
    @Published var selectedType: TestReaderUpdateSelection
    @Published var selectedComponents: UpdateComponent

    let isTapToPayMode: Bool
    let componentOptions: [UpdateComponent] = [.incremental, .firmware, .config, .keys]

    init(
        isTapToPayMode: Bool,
        initialSelection: TestReaderUpdateSelection,
        initialComponents: UpdateComponent
    ) {
        self.isTapToPayMode = isTapToPayMode
        if isTapToPayMode && initialSelection != .none && initialSelection != .required && initialSelection != .random {
            self.selectedType = .none
        } else {
            self.selectedType = initialSelection
        }
        self.selectedComponents = initialComponents
    }

    var typeOptions: [TestReaderUpdateSelection] {
        if isTapToPayMode {
            return [.none, .required, .random]
        }
        return [.none, .random, .required, .available, .requiredOffline, .lowBattery, .lowBatterySucceedConnect]
    }

    var shouldShowComponentsSection: Bool {
        if isTapToPayMode { return false }

        switch selectedType {
        case .available, .required, .requiredOffline:
            return true
        case .none, .random, .lowBattery, .lowBatterySucceedConnect:
            return false
        }
    }

    func isEnabled(_ component: UpdateComponent) -> Bool {
        selectedComponents.contains(component)
    }

    func setEnabled(_ enabled: Bool, for component: UpdateComponent) {
        if enabled {
            selectedComponents.insert(component)
        } else {
            selectedComponents.remove(component)
        }
    }

    func componentLabel(_ component: UpdateComponent) -> String {
        switch component {
        case .incremental:
            return "Incremental"
        case .firmware:
            return "Firmware"
        case .config:
            return "Config"
        case .keys:
            return "Keys"
        default:
            return "Unknown"
        }
    }
}

struct TestReaderUpdateConfigView: View {
    @ObservedObject fileprivate var viewModel: TestReaderUpdateConfigurationViewModel

    var body: some View {
        Form {
            Section("Update Type") {
                ForEach(viewModel.typeOptions, id: \.self) { type in
                    Button {
                        viewModel.selectedType = type
                    } label: {
                        HStack {
                            Text(type.description)
                            Spacer()
                            if viewModel.selectedType == type {
                                Image(systemName: "checkmark")
                                    .foregroundStyle(.tint)
                            }
                        }
                        .frame(maxWidth: .infinity, alignment: .leading)
                        .contentShape(Rectangle())
                    }
                    .buttonStyle(.plain)
                }
            }

            if viewModel.shouldShowComponentsSection {
                Section("Components") {
                    ForEach(Array(viewModel.componentOptions.enumerated()), id: \.offset) { _, component in
                        Toggle(
                            viewModel.componentLabel(component),
                            isOn: Binding(
                                get: { viewModel.isEnabled(component) },
                                set: { enabled in
                                    viewModel.setEnabled(enabled, for: component)
                                }
                            )
                        )
                    }
                }
            }
        }
        .navigationTitle("Test Reader Update")
        .navigationBarTitleDisplayMode(.inline)
    }
}

final class TestReaderUpdateConfigViewController: UIHostingController<TestReaderUpdateConfigView> {
    var onSave: ((TestReaderUpdateSelection, UpdateComponent) -> Void)?

    private let viewModel: TestReaderUpdateConfigurationViewModel

    init(
        isTapToPayMode: Bool,
        initialSelection: TestReaderUpdateSelection,
        initialComponents: UpdateComponent
    ) {
        self.viewModel = TestReaderUpdateConfigurationViewModel(
            isTapToPayMode: isTapToPayMode,
            initialSelection: initialSelection,
            initialComponents: initialComponents
        )
        super.init(rootView: TestReaderUpdateConfigView(viewModel: viewModel))
    }

    @available(*, unavailable)
    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        navigationItem.rightBarButtonItem = UIBarButtonItem(
            title: "Done",
            style: .done,
            target: self,
            action: #selector(didTapDone)
        )
    }

    @objc
    private func didTapDone() {
        onSave?(viewModel.selectedType, viewModel.selectedComponents)
        if let navigationController {
            navigationController.popViewController(animated: true)
        } else {
            dismiss(animated: true)
        }
    }
}
