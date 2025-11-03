// swift-tools-version:5.5
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v15)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/5.0.0/StripeTerminal.xcframework.zip",
      checksum: "40735b9808b29eedc027f19e41c7eb4da805bdf1ec02f2ed914637a62e6d08f0"
    )
  ]
)
