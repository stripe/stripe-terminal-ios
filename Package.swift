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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.17.0/StripeTerminal.xcframework.zip",
      checksum: "f0ddf6cdc8c9bb3857750a7d2f208a3efc23c63feef858764778fc0992d1030c"
    )
  ]
)
