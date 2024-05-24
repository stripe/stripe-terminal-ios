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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.6.0/StripeTerminal.xcframework.zip",
      checksum: "389742f2d2f931f560f3bfbf219cfdcaf49ab55223330c7415b0fd12ebcf8576"
    )
  ]
)
