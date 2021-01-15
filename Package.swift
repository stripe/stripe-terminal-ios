// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v9)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v1.4.0/StripeTerminal.xcframework.zip",
      checksum: "59ef16e65e24c85c4080f916218a5750fb34d064079fbbbd22514b4569d8f08a"
    )
  ]
)
