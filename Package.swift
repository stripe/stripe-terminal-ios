// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v14)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/4.4.0/StripeTerminal.xcframework.zip",
      checksum: "ff1d1210fc8e82f04e22d6f8586a06bae55a07aa9f77bb67f61cf13143f62b10"
    )
  ]
)
