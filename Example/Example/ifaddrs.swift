//
//  Ifaddrs.swift
//  Example
//
//  Created by Daniel Jackson on 9/10/19.
//  Copyright © 2019 Stripe. All rights reserved.
//

import Foundation

/**
 Namespace for Swift wrappers around ifaddrs.h functionality.

 Requires a bridging header with `#import "ifaddrs.h"`
 */
enum Ifaddrs_h {
    /**
     using `getifaddrs`, find the `en0` interface and return its IP address.

     Adapted from code on StackOverflow, primarily:
     https://stackoverflow.com/a/30754194/1196205

     - returns: Device's WIFI IP address.
     */
    static func getWifiIPAddress() -> String? {
        var wifiIPAddress: String?
        var ifaddrList: UnsafeMutablePointer<ifaddrs>?

        // 0 on success, anything else is an error
        guard getifaddrs(&ifaddrList) == 0 else { return nil }
        // list might be empty
        guard let firstAddress = ifaddrList else { return nil }
        // make sure to release memory when done
        defer { freeifaddrs(ifaddrList) }

        for interface in sequence(first: firstAddress.pointee, next: { $0.ifa_next?.pointee }) {
            let addressFamily = interface.ifa_addr.pointee.sa_family
            let isIPv4Address = AF_INET == addressFamily
            let isIPv6Address = AF_INET6 == addressFamily
            let dontHaveAddressYet = wifiIPAddress == nil

            // prefer ipv4 addresses over ipv6, ignore any others
            if isIPv4Address || (isIPv6Address && dontHaveAddressYet),
                // stack overflow says wifi is always 'en0' on iOS
                let ifa_name = interface.ifa_name, "en0" == String(cString: ifa_name)
            {

                // Return the address in numeric form, storing in hostname,
                // and don't care about service name
                var hostname = [CChar](repeating: 0, count: Int(NI_MAXHOST))
                let returnValue = getnameinfo(
                    interface.ifa_addr,
                    socklen_t(interface.ifa_addr.pointee.sa_len),
                    &hostname,
                    socklen_t(hostname.count),
                    nil,
                    0,
                    NI_NUMERICHOST
                )
                guard returnValue == 0 else { continue }

                wifiIPAddress = String(cString: hostname)
            }
        }

        return wifiIPAddress
    }

}
