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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/5.6.0/StripeTerminal.xcframework.zip",
      checksum: "6da57b64671bf449b221fcbe58a4ea732df3ef4c0c5e30cfa5ee01d00d7c487d"
    )
  ]
)
