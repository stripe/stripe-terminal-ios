// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v10)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.3.0/StripeTerminal.xcframework.zip",
      checksum: "63351180dcb03103246a87ac28e44c22f915681f3a8e5c02dba7f9fd8a29e310"
    )
  ]
)
