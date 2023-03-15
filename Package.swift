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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.18.1/StripeTerminal.xcframework.zip",
      checksum: "26f833e686d593f72094f9b31d96d0194094549a76b5357575ea77da6d83775e"
    )
  ]
)
