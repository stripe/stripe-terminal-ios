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
      checksum: "2335ca022c842bf73a6e098df653934805df36b82335fcb7a6a5798b11c79ffb"
    )
  ]
)
