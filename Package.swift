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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.0.0/StripeTerminal.xcframework.zip",
      checksum: "10e3cc0bfb8cc60d6f01dd46765a09db9a744ad06945d59df2cfe6165f637d5a"
    )
  ]
)
