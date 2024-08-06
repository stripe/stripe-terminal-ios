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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.8.1/StripeTerminal.xcframework.zip",
      checksum: "dacfdc83770d102eb5aa15bba4b463a5807b67dbd7c00395b523e7ff70499b69"
    )
  ]
)
