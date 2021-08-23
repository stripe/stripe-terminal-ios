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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.1.0/StripeTerminal.xcframework.zip",
      checksum: "8fa229a487979c113e669899a59fb2f0a1592da28e20957131ffbf1f31c4678d"
    )
  ]
)
