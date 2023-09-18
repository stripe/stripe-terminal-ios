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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.23.2/StripeTerminal.xcframework.zip",
      checksum: "106692d34374bfc31299f92d0e75101ad78ec524b95112daaa3d1a245740d042"
    )
  ]
)
