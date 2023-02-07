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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.17.1/StripeTerminal.xcframework.zip",
      checksum: "124bf3173b5298627d5c4d5dc7fbfeef94cd6cb86a6a8c4cb7c041679f92df5e"
    )
  ]
)
