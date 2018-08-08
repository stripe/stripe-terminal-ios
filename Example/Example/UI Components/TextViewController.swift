//
//  TextViewController.swift
//  Stripe POS
//
//  Created by Ben Guo on 9/12/17.
//  Copyright © 2017 Stripe. All rights reserved.
//

import UIKit
import StripePOS

class TextViewController: StackViewController {

    let textView = UITextView()
    weak var shareButton: ColoredButton?

    let filenameFormatter = DateFormatter()

    init(title: String? = nil) {
        super.init(nibName: nil, bundle: nil)
        self.title = title
        filenameFormatter.dateFormat = "yyyy'-'MM'-'dd'_'hhmma"
    }

    convenience init(object: CustomStringConvertible) {
        let title = String(describing: type(of: object))
        self.init(title: title)
        if let decodable = object as? SCPJSONDecodable,
            let fields = decodable.originalJSON as? [String: Any] {
            // split description onto multiple lines
            let components = fields.description.components(separatedBy: ",")
            self.textView.text = components.map {
                $0.trimmingCharacters(in: .whitespacesAndNewlines) + "," + "\n"
            }.joined()
        }
        else {
            if object.description.contains(";") {
                // split description onto multiple lines
                let components = object.description.components(separatedBy: ";")
                self.textView.text = components.map {
                    $0.trimmingCharacters(in: .whitespacesAndNewlines) + ";" + "\n"
                    }.joined()
            }
            else {
                self.textView.text = object.description
            }
        }
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        // add a done button if there's no stack
        if let nc = navigationController, nc.viewControllers.count == 1 {
            navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .done, target: self, action: #selector(doneAction))
        }

        textView.backgroundColor = UIColor.stripeDarkGrey
        textView.font = UIFont.preferredFont(forTextStyle: .body)
        textView.isSelectable = false
        textView.textColor = .white

        let shareButton = ColoredButton(title: "Share", color: UIColor.stripeBlue) {
            self.shareButton?.isEnabled = false
            defer {
                self.shareButton?.isEnabled = true
            }
            let dateString = self.filenameFormatter.string(from: Date())
            let filename = "\(self.title ?? "StripePOS")_\(dateString).txt"
            self.shareTextFile(contents: self.textView.text, filename: filename)
        }
        self.shareButton = shareButton

        stack = [
            [textView],
            [shareButton],
        ]
        stackView.distribution = .fill
        stackView.arrangedSubviews.first?.heightAnchor.constraint(equalTo: stackView.heightAnchor, multiplier: 0.8)
        stackView.arrangedSubviews.last?.heightAnchor.constraint(equalTo: stackView.heightAnchor, multiplier: 0.2)
    }

    @objc func doneAction() {
        dismiss(animated: true, completion: nil)
    }

}
