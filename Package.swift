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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/4.6.1/StripeTerminal.xcframework.zip",
      checksum: "a2d2525d9074be165dc87e93e92e68a20c813e7393296bf0e4680f0b01a9cd13"
    )
  ]
)
