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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.3.0/StripeTerminal.xcframework.zip",
      checksum: "9cf872b313f124f2b2e3ba5e50b044c9cccbb8556ba8596f587abc231185868f"
    )
  ]
)
