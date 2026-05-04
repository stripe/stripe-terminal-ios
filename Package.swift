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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/5.5.0/StripeTerminal.xcframework.zip",
      checksum: "b7c52246f1093911f327b34f86654f4892a33abcbefbab5ed748e81e504bee12"
    )
  ]
)
