// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v14)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/4.7.1/StripeTerminal.xcframework.zip",
      checksum: "ea6b6e99ba8b5d58b148603967c914da79e679ec74a8d13fc34ed4bb55f9c231"
    )
  ]
)
