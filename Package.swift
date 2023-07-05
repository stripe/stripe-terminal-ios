// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v11)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.22.0/StripeTerminal.xcframework.zip",
      checksum: "abbc1f950f656a2e3ed936e59ec4416da7aaf68211e52c73b1b08ed9fe7ad692"
    )
  ]
)
