// swift-tools-version:5.2
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "SwiftJWKtoPEM",
    products: [
        // Products define the executables and libraries produced by a package, and make them visible to other packages.
        .library(
            name: "SwiftJWKtoPEM",
            targets: ["SwiftJWKtoPEM"]),
    ],
    dependencies: [
        .package(url: "https://github.com/apple/swift-nio-ssl-support.git", from: "1.0.0"),
        .package(url: "https://github.com/vapor/open-crypto.git", from: "4.0.0-beta.2"),
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages which this package depends on.
        .target(name: "CJWKPEMOpenSSL"),
        .target(name: "SwiftJWKtoPEM", dependencies: [
            "CJWKPEMOpenSSL",
            .product(name: "OpenCrypto", package: "open-crypto")]),
        .testTarget(
            name: "SwiftJWKtoPEMTests",
            dependencies: ["SwiftJWKtoPEM"]),
    ]
)
