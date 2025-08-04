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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/4.6.0/StripeTerminal.xcframework.zip",
      checksum: "48f2520161e9a623c0461f48fb1b5879f2711b0759bc6c67032b0650f36702cb"
    )
  ]
)
