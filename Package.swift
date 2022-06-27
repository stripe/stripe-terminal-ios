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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.10.0/StripeTerminal.xcframework.zip",
      checksum: "d79f976e7446faf95922ceac59bcbfe25414993b42830faef7d946356b26eb17"
    )
  ]
)
