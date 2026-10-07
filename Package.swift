// swift-tools-version:5.7
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v16)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/6.0.0/StripeTerminal.xcframework.zip",
      checksum: "90f370b39edee8a45ab50c512d6c054e7d6d3304931a7aeef80916ea97010129"
    )
  ]
)
