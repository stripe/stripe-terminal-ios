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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.15.0/StripeTerminal.xcframework.zip",
      checksum: "de9133a72554983262077dbd503c7ce9db809e2c4a1307b94ca86798a3343369"
    )
  ]
)
