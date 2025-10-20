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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/4.7.3/StripeTerminal.xcframework.zip",
      checksum: "51f0b37f7f86330b54241b8bcc323255f9af7b054916629bd3d11b4e9b4fda7a"
    )
  ]
)
