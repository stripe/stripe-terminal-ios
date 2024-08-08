// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v13)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.8.2/StripeTerminal.xcframework.zip",
      checksum: "0c89ba3cd606db91a20e5344326b28e9a3caa7ccf5134b0bffccd5e5cca6a209"
    )
  ]
)
