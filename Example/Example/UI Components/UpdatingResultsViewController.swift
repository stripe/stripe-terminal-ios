//
//  UpdatingResultsViewController.swift
//  Example
//
//  Created by Ben Guo on 7/18/18.
//  Copyright © 2018 Stripe. All rights reserved.
//

import UIKit

class UpdatingResultsViewController<T>: UITableViewController where T: CustomStringConvertible {

    public var results: [T] = [] {
        didSet {
            DispatchQueue.main.async {
                self.tableView.reloadData()
            }
        }
    }

    var onSelectResult: (T)->() = { _ in }

    init(title: String) {
        super.init(nibName: nil, bundle: nil)
        self.title = title
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.tableView.register(UITableViewCell.self, forCellReuseIdentifier: NSStringFromClass(UpdatingResultsViewController.self))
        self.tableView.tableFooterView = UIView()
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    // MARK: - Table view data source

    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int { return results.count
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: NSStringFromClass(UpdatingResultsViewController.self), for: indexPath)
        let result = results[indexPath.row]
        cell.textLabel?.text = result.description
        return cell
    }

    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        let result = results[indexPath.row]
        onSelectResult(result)
    }

}
