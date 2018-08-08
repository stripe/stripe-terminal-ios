//
//  UIViewController+UIActivityViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/12/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit

extension UIViewController {

    /**
     Shares the given text as a text file
     */
    func shareTextFile(contents: String, filename: String) {
        guard let fileURL = NSURL(fileURLWithPath: NSTemporaryDirectory()).appendingPathComponent(filename),
            let data = contents.data(using: .utf8) else {
                return
        }
        do {
            try data.write(to: fileURL)
        }
        catch {
            presentAlert(title: "Error", message: "Couldn't write file")
        }
        let activityController = UIActivityViewController(activityItems: [fileURL], applicationActivities: nil)
        let excludedTypes: [UIActivityType] = [
            .postToFlickr,
            .postToWeibo,
            .message,
            .print,
            .copyToPasteboard,
            .assignToContact,
            .saveToCameraRoll,
            .addToReadingList,
            .postToFlickr,
            .postToVimeo,
            .postToTencentWeibo
        ]
        activityController.excludedActivityTypes = excludedTypes
        activityController.completionWithItemsHandler = { (_, _, _, error) in
            if let e = error {
                self.presentAlert(error: e)
            }
            do {
                try FileManager.default.removeItem(at: fileURL)
            }
            catch {
                NSLog("Error deleting file")
            }
        }
        present(activityController, animated: true, completion: nil)
    }
    
}
