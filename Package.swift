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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.7.0/StripeTerminal.xcframework.zip",
      checksum: "3cc47ba9fe7cccc8bbd224dcde1a0d37c0d3b756e9c967bf2366e6478b11a260"
    )
  ]
)
