// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v10)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.2.0/StripeTerminal.xcframework.zip",
      checksum: "abf0d717af6b7c1d2112b388026412ec677a8dea011979f9b6d61b489dbaf74c"
    )
  ]
)
