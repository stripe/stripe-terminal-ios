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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.23.1/StripeTerminal.xcframework.zip",
      checksum: "62fc794de089f630143b6573b2906958651235607fa1fea8b7a064c0077ded55"
    )
  ]
)
