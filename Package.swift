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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.7.0/StripeTerminal.xcframework.zip",
      checksum: "a5a136e05fa6e23a313f69c8160fadc2fb58bb5a355842af242cf9e9162716ed"
    )
  ]
)
