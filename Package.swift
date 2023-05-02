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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.20.0/StripeTerminal.xcframework.zip",
      checksum: "d6dfdc95b4e7fc0ffedcfe398022902c4cc33cdb97b81f81b1ccfa3623728f26"
    )
  ]
)
