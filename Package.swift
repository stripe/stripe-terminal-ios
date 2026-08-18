// swift-tools-version:5.5
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v15)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/5.8.0/StripeTerminal.xcframework.zip",
      checksum: "92c65013c4d92ce9dcba2310a0103651756bb65eeca409324ec54ed9896da4f7"
    )
  ]
)
