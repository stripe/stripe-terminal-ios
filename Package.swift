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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.4.0/StripeTerminal.xcframework.zip",
      checksum: "9bec32c621a7ae13d02973d6f02a64ab2fd1b676325f8dd695659e580fe6285f"
    )
  ]
)
