// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v11)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.21.0/StripeTerminal.xcframework.zip",
      checksum: "3a7eff73fdd15c90f3054d9255da660f5e4da600781b939e2882c2f939548193"
    )
  ]
)
