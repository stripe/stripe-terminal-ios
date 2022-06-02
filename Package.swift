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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.9.1/StripeTerminal.xcframework.zip",
      checksum: "84d0e91c4769a2053c1bcd1e97c55c22cbbb5fd1650678b464358faad4e8b8e8"
    )
  ]
)
