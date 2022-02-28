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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.6.0/StripeTerminal.xcframework.zip",
      checksum: "88c610f058378d9a2be161071e3726aa312f93f5e90bbae6b892ca3ccb728af9"
    )
  ]
)
