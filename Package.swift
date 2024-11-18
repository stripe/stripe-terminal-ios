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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/4.1.0/StripeTerminal.xcframework.zip",
      checksum: "e93084589f6a35a72922a106725272191cfbef922c81767297c7b1af19b49981"
    )
  ]
)
