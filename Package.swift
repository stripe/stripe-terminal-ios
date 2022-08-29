// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v10)
    ],
  products: [
    .library(
        name: "StripeTerminal",
        targets: ["StripeTerminal"]
    )
  ],
  targets: [
    .binaryTarget(
      name: "StripeTerminal",
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.12.0/StripeTerminal.xcframework.zip",
      checksum: "f1582e41e8f3c7d0588b354d318766557d7afe786627bf249e7f72ba0b7c6304"
    )
  ]
)
