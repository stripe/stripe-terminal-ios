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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.23.3/StripeTerminal.xcframework.zip",
      checksum: "3978516cbf49d63b1b891141fed9a55a14246cd3a71caab6388be509387cb567"
    )
  ]
)
