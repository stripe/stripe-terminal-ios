// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v11)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.16.0/StripeTerminal.xcframework.zip",
      checksum: "9c1e14a142e0549ca05b35ae019e39d192ff4c83c0face858353ecf4af084caf"
    )
  ]
)
