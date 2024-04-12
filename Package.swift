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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.5.0/StripeTerminal.xcframework.zip",
      checksum: "8385f2a7d28eccd67f72fe02bddbf25c7f0cd8cd6ce0c10cc190fd40bdc8f177"
    )
  ]
)
