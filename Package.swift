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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/5.8.1/StripeTerminal.xcframework.zip",
      checksum: "08f3eecb8f79e9598c1148d157923e68fb825f26855726c9f983512967607a30"
    )
  ]
)
