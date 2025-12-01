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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/5.1.0/StripeTerminal.xcframework.zip",
      checksum: "bb1a0b772fccd41ce9d3bc55667e2949bcb35eed95e10806d2fb255fe8c456dc"
    )
  ]
)
