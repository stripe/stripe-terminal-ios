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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.8.0/StripeTerminal.xcframework.zip",
      checksum: "657adda0950cb7614631b0b269c80b130ca1afed27542301bcc2b6cf2c496aa3"
    )
  ]
)
