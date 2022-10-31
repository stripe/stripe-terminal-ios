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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.14.0/StripeTerminal.xcframework.zip",
      checksum: "26c4a25105d2c5668df038438c8290fc349b534b94fe1a282641e3d60d5fb041"
    )
  ]
)
