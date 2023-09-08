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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.0.0/StripeTerminal.xcframework.zip",
      checksum: "4cf81e6795559d5663a5d903abe4b3cacd6ac4a756a8d118513a2c28b8829dd0"
    )
  ]
)
