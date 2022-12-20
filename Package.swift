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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.16.1/StripeTerminal.xcframework.zip",
      checksum: "c35b143bbd7419b8561552c9316972fe7a6ce6ab6977782239bbd3de4c1c0d90"
    )
  ]
)
