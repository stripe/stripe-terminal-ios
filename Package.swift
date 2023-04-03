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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.19.0/StripeTerminal.xcframework.zip",
      checksum: "01962eaae980c5b73db81a69f16967b59a275b3c2b6260111543f6ea8e0f82f3"
    )
  ]
)
