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
      url: "https://github.com/stripe/stripe-terminal-ios/releases/download/3.7.0/StripeTerminal.xcframework.zip",
      checksum: "11b922eeac598595951882fa4be9991a5e2a85590b362063c9a56126e78e5b7e"
    )
  ]
)
