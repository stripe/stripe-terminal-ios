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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.5.0/StripeTerminal.xcframework.zip",
      checksum: "3c2c871b09ae7b9d1123d2613ae065d7d1ce133c2cdbd02fd44528dcd7cd1b71"
    )
  ]
)
