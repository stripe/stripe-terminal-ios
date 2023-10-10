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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.1.0/StripeTerminal.xcframework.zip",
      checksum: "b86f86806d69e446ff30741c3fec632a499cd1d72c7db45ad7d42a54d3ddc781"
    )
  ]
)
