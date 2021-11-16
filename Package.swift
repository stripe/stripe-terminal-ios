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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.4.0/StripeTerminal.xcframework.zip",
      checksum: "e26cfce8731ef8690f3dd94552fda174acc686ca67707f252b25ac738c443600"
    )
  ]
)
