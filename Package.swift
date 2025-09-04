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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/4.7.0/StripeTerminal.xcframework.zip",
      checksum: "60be980f953e270450831eb6dffba39c0cf8a06a9efeb37f8d2f4fd658cd2438"
    )
  ]
)
