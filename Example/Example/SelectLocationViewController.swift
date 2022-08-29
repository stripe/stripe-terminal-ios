//
//  SelectLocationViewController.swift
//  Terminal
//
//  Created by Catriona Scott on 8/21/20.
//  Copyright © 2020 Stripe. All rights reserved.
//

import Foundation
import Static
import StripeTerminal

class SelectLocationViewController: TableViewController, UITableViewDelegate, CancelingViewController {

    var onSelectLocation: (Location) -> Void = { _ in }
    internal var cancelButton: UIBarButtonItem?
    internal var newLocationButton: UIBarButtonItem?
    private var locations: [Location] = []
    private var hasMore: Bool = false
    private var fetchingLocations = false
    private let activityIndicatorHeader = ActivityIndicatorHeaderView(title: "Fetching Locations")

    init() {
        super.init(style: .plain)
        self.dataSource = DataSource(tableView: self.tableView, sections: nil, tableViewDelegate: self)
    }

    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        title = "Locations"
        activityIndicatorHeader.activityIndicator.hidesWhenStopped = true

        // Give the activity indicator header a white bg so it doesn't clash with the location rows when there are enough to need to scroll
        activityIndicatorHeader.backgroundColor = UIColor.white

        let cancelButton = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(dismissAction))
        self.cancelButton = cancelButton
        navigationItem.leftBarButtonItem = cancelButton

        let newLocationButton = UIBarButtonItem(barButtonSystemItem: .add, target: self, action: #selector(showLocationCreationForm))
        self.newLocationButton = newLocationButton
        navigationItem.rightBarButtonItem = newLocationButton

        // Need to set it explicitly here for first fetch to ensure updateContent renders the loading-specific content
        self.fetchingLocations = true
        self.updateContent()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)

        fetchNextPageOfLocations {
            self.updateContent()
        }
    }

    @objc
    private func dismissAction() {
        presentingViewController?.dismiss(animated: true, completion: nil)
    }

    private func presentModalInNavigationController(_ vc: UIViewController) {
        let navController = LargeTitleNavigationController(rootViewController: vc)
        navController.presentationController?.delegate = self
        self.present(navController, animated: true, completion: nil)
    }

    @objc
    private func showLocationCreationForm() {
        let createLocationVC = CreateLocationViewController()
        createLocationVC.onCreateLocation = { [unowned createLocationVC, unowned self] location in
            createLocationVC.dismissAction()
            self.locations.insert(location, at: 0)
            self.updateContent()
        }
        self.presentModalInNavigationController(createLocationVC)
    }

    private func fetchNextPageOfLocations(completion: (() -> Void)?) {
        activityIndicatorHeader.activityIndicator.startAnimating()

        // If we already have some locations, use the latest one for the startingAfter pagination cursor
        let startingAfter = !locations.isEmpty ? locations[locations.count - 1].stripeId : nil

        let parameters = ListLocationsParameters.init(
            limit: NSNumber.init(value: 100),
            endingBefore: nil,
            startingAfter: startingAfter
        )

        self.fetchingLocations = true
        Terminal.shared.listLocations(parameters: parameters) { [unowned self] (locations: [Location]?, hasMore: Bool, error: Error?) in
            if let fetchLocationError = error {
                self.presentAlert(error: fetchLocationError)
            }
            if let unwrappedLocations = locations {
                for location in unwrappedLocations {
                    self.locations.append(location)
                }
                self.hasMore = hasMore
            }

            self.activityIndicatorHeader.activityIndicator.stopAnimating()
            self.fetchingLocations = false
            if let completion = completion {
                completion()
            }
        }
    }

    func tableView(_ tableView: UITableView, willDisplay row: UITableViewCell, forRowAt indexPath: IndexPath) {
        // Fetch next page of locations when the bottom of the table is reached
        if indexPath.row + 1 == self.locations.count {
            if self.hasMore && !self.fetchingLocations {
                self.fetchNextPageOfLocations { () in
                    self.updateContent()
                }
            }
        }
    }

    internal func updateContent() {
        var rows: [Row] = []
        if fetchingLocations {
            activityIndicatorHeader.title = "Fetching Locations"
        } else if locations.isEmpty {
            activityIndicatorHeader.title = "No Locations found for this account"
        } else {
            activityIndicatorHeader.title = "\(locations.count)\(self.hasMore ? "+" : "") Locations found"

            for location in self.locations {
                rows.append(self.row(for: location))
            }
        }

        dataSource.sections = [
            Section(header: Section.Extremity.view(activityIndicatorHeader), rows: rows)
        ]
    }

    internal func row(for location: Location) -> Row {
        return Row(
            text: location.displayName ?? location.stripeId,
            detailText: location.stripeId,
            selection: { [unowned self] in
                self.onSelectLocation(location)
            }, cellClass: SubtitleCell.self
        )
    }

}
