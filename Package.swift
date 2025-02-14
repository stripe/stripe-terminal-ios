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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/4.2.0/StripeTerminal.xcframework.zip",
      checksum: "c184c9389c4b24673831945f9a731561451d941c91e92ec01bd33cfa73a14751"
    )
  ]
)
