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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.3.1/StripeTerminal.xcframework.zip",
      checksum: "79f39db1a19b4c5fc598d74a06c38516d3b18d8d8eb33edf92f190b3a2d25fac"
    )
  ]
)
