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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/4.3.0/StripeTerminal.xcframework.zip",
      checksum: "514794bd7d09d418deb36375797b46da3d7c58a918dbaecfd4edf7b016ce8543"
    )
  ]
)
