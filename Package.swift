// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v13)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.2.1/StripeTerminal.xcframework.zip",
      checksum: "c2d8bb26c1ffdba23d3d99b2d5b77153a13d52681a9b4c889955a3ccc5cf2be1"
    )
  ]
)
