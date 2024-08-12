// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v13)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.8.3/StripeTerminal.xcframework.zip",
      checksum: "713c4b6e46d7c940dfdeacfe699304963e9e5ab149be025248466fcfd649af06"
    )
  ]
)
