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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.11.0/StripeTerminal.xcframework.zip",
      checksum: "445600b677ba0b2a17de11b925f189b2cb84d9dbded5e87dc910e799557a6767"
    )
  ]
)
