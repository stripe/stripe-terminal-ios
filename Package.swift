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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/5.1.1/StripeTerminal.xcframework.zip",
      checksum: "a0ee01bea30b4b29655da5ac23df7102337f5b2ebaba864f57e9098d54aa23ca"
    )
  ]
)
