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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.7.0/StripeTerminal.xcframework.zip",
      checksum: "7618b7b1df046908db61ad47d3f823f8121c74161e4fe78a754415178cc5ccdd"
    )
  ]
)
