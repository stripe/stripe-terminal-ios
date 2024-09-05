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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.9.1/StripeTerminal.xcframework.zip",
      checksum: "db7e4ba71f6d4962e997acfae281af96252ab3d204c08c41560103061b9e1937"
    )
  ]
)
