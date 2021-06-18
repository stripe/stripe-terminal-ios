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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/v2.0.0/StripeTerminal.xcframework.zip",
      checksum: "f78e3652f5306b8882dbf67535a0c042ee2d0f03cf532d0f19ae130bebef5c3d"
    )
  ]
)
