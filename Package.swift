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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.19.1/StripeTerminal.xcframework.zip",
      checksum: "55283b01fd9a565275c3f7f6d3fdef3688db33eac4276106008ce9023892a036"
    )
  ]
)
