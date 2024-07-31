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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.8.0/StripeTerminal.xcframework.zip",
      checksum: "c0e1eaa3f3179cd239055af7718ef88507f6ff544ccde6cc44c890be833ee8be"
    )
  ]
)
