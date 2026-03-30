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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/5.4.0/StripeTerminal.xcframework.zip",
      checksum: "27d399a97354e8355619a18eff1b29bda6c6a7e4f0aee01aba4ad08e00f86e52"
    )
  ]
)
