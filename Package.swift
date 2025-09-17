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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/4.7.2/StripeTerminal.xcframework.zip",
      checksum: "406d65faca2cb7dc6088eb34634d63c23daf184d4d3f60cd7fc56f96406d7483"
    )
  ]
)
