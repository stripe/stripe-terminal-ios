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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.23.0/StripeTerminal.xcframework.zip",
      checksum: "68355b745ba2082bfb7bf3194a0bda51aac385193ae2a1fb8fe54846af972872"
    )
  ]
)
