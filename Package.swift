// swift-tools-version:5.3
import PackageDescription

let package = Package(
  name: "StripeTerminal",
    platforms: [
      .iOS(.v14)
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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/4.1.0/StripeTerminal.xcframework.zip",
      checksum: "f326b8bd30a9dcc0035e83937c3d81745975c4019ff830659b98ade80695e3a3"
    )
  ]
)
