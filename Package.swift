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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/5.7.0/StripeTerminal.xcframework.zip",
      checksum: "ec06892aeff7eef02cf357be9cd3a3d3077dbb038a72f577c5c69586cb526a38"
    )
  ]
)
