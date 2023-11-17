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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.2.0/StripeTerminal.xcframework.zip",
      checksum: "e2bfc417ba6fdea0b2ef03d0732246a8f499d70fdf5b42e23f30a15fea40d8ea"
    )
  ]
)
