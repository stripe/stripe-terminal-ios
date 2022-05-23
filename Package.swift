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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.9.0/StripeTerminal.xcframework.zip",
      checksum: "9deabb96585159a44050082932d5b7375260f6e377e40f620e36b81e82c53f07"
    )
  ]
)
