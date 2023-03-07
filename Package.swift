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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.18.0/StripeTerminal.xcframework.zip",
      checksum: "95a285f30236981e2e11332aeb2c6d4bb950d4bc560efe1fd717a0da9b286f1a"
    )
  ]
)
