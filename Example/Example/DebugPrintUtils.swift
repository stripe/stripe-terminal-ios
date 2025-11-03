//
//  DebugPrintUtils.swift
//  Example
//
//  Created by Brian Cooke on 2025-08-28.
//  Copyright © 2025 Stripe. All rights reserved.
//
import Foundation

/// Utility functions for pretty-printing debug descriptions and other debugging-related formatting.
enum DebugPrintUtils {

    /// Pretty-prints a debug description string by formatting it with proper indentation.
    ///
    /// This function takes a debug description (typically from an object's `debugDescription` property)
    /// and formats it with proper indentation to make nested objects more readable.
    ///
    /// - Parameter debugDescription: The debug description string to format
    /// - Returns: A formatted string with proper indentation based on nested object markers
    static func prettyPrint(debugDescription: String) -> String {
        let lines = debugDescription.split(separator: ";").map { $0.trimmingCharacters(in: .whitespaces) }
        var result: [String] = []
        var indentLevel = 0

        for line in lines {
            // Apply current indentation
            let indentedLine = String(repeating: "\t", count: indentLevel) + line
            result.append(indentedLine)

            // Adjust the indent level after adding the line so the next items are adjusted
            // Count opening and closing brackets to determine indent changes
            let openBrackets = line.filter { $0 == "<" }.count
            let closeBrackets = line.filter { $0 == ">" }.count

            indentLevel += openBrackets
            indentLevel = max(0, indentLevel - closeBrackets)
        }

        return result.joined(separator: "\n")
    }
}
