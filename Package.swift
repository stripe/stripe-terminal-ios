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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.20.2/StripeTerminal.xcframework.zip",
      checksum: "1bbb6d1b77542d467d04a61056d52f294c7b8b0ef5dcc591056cbdb9959c9d21"
    )
  ]
)
