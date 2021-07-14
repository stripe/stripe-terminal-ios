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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.0.1/StripeTerminal.xcframework.zip",
      checksum: "77bff4e78089b130291aaa9727b7118030676cf210d2d51f1f66070f7efdb4e4"
    )
  ]
)
