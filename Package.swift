// swift-tools-version:5.5
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v15)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/5.2.0/StripeTerminal.xcframework.zip",
      checksum: "454c0dc50687f933169297a15732a1641319675fea4fd42dcda25e3261212545"
    )
  ]
)
