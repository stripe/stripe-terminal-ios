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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.1.1/StripeTerminal.xcframework.zip",
      checksum: "60253d8509fd36aeb9d30f9855da80256a1f56844eabcd530a9c9d97f3c6db16"
    )
  ]
)
