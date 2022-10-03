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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.13.0/StripeTerminal.xcframework.zip",
      checksum: "578827717a58ea7fccdf2d63c34ec4dda160d6fff91984c87add5d1944bfe4b7"
    )
  ]
)
