//
//  ReceiptWebViewController.swift
//  Example
//
//  Created by James Little on 8/20/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import Foundation
import WebKit
import UIKit

class ReceiptWebViewController: UIViewController, WKUIDelegate, WKNavigationDelegate {
    let url: URL
    let spinner = UIActivityIndicatorView()
    var webView: WKWebView!

    init(withUrl url: URL) {
        self.url = url
        super.init(nibName: nil, bundle: nil)
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        let myRequest = URLRequest(url: self.url)
        self.navigationItem.rightBarButtonItem = UIBarButtonItem.init(barButtonSystemItem: .action, target: self, action: #selector(didShareWebView))
        if #available(iOS 11.0, *) {
            self.navigationItem.largeTitleDisplayMode = .never
        }

        if #available(iOS 13.0, *) {
            view.backgroundColor = .systemBackground
        } else {
            view.backgroundColor = .white
        }

        let webConfiguration = WKWebViewConfiguration()
        webView = WKWebView(frame: .zero, configuration: webConfiguration)
        webView.uiDelegate = self
        webView.navigationDelegate = self
        view.addSubview(webView)
        webView.load(myRequest)

        if #available(iOS 13.0, *) {
            spinner.style = .large
        }
        view.addSubview(spinner)
        spinner.startAnimating()

        setAutolayout()
    }

    func setAutolayout() {
        spinner.translatesAutoresizingMaskIntoConstraints = false
        webView.translatesAutoresizingMaskIntoConstraints = false

        NSLayoutConstraint.activate([
            spinner.centerXAnchor.constraint(equalTo: view.centerXAnchor),
            spinner.centerYAnchor.constraint(equalTo: view.centerYAnchor),
        ])

        webView.anchorToSuperviewAnchors()
    }

    @objc
    func didShareWebView() {
        let vc = UIActivityViewController(activityItems: [url], applicationActivities: [])
        present(vc, animated: true)
    }

    func webView(_ webView: WKWebView, didFinish navigation: WKNavigation!) {
        self.spinner.stopAnimating()
    }
}
