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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/5.3.0/StripeTerminal.xcframework.zip",
      checksum: "5494561c2f92da7188fdb0e453d5ed8201944cd579b3a918380909b58939014b"
    )
  ]
)
