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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/4.5.0/StripeTerminal.xcframework.zip",
      checksum: "1887241aea2abc86ca77ffc4b4c9ec73bc17abcccc0bf2b920c8d021da8050d9"
    )
  ]
)
