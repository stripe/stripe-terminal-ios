# Release & Support Lifecycle

## Release Schedule
We release a new major version of the Terminal mobile SDK annually. Major
versions may include breaking changes. Minor versions are released
approximately monthly and include bug fixes and new features for the latest
major version only.

## Support Lifecycle
Each Terminal mobile SDK major version follows a three-phase lifecycle from
the date of its General Availability (GA) release:

- **Active development** (1 year): Full support including new features, bug fixes, and security patches.
- **Maintenance** (1 year): Critical bug fixes and security or compliance patches only. No new feature development.
- **Deprecated** (1 year): No patches or support. The SDK may continue to function, but you should upgrade to a supported version as soon as possible.

## End-of-Life Enforcement
At the end of the Deprecated phase, SDK versions will be blocked from
connecting to Terminal readers. Integrations using blocked SDK versions
will not be able to discover readers, connect to readers, or process
payments. You must upgrade to a supported SDK version before the hard
block date to avoid interruption to your payment processing.

## Support and Enforcement Schedule

| Release         | GA Date         | Patch Support Until | Status                            | Hard Block Date |
|-----------------|-----------------|---------------------|-----------------------------------|-----------------|
| Versions 1.x.x | October, 2019   | January, 2024       | Deprecated                        | January, 2027   |
| Versions 2.x.x | June, 2021      | October, 2024       | Deprecated                        | January, 2027   |
| Versions 3.x.x | September, 2023 | October, 2025       | Deprecated                        | January, 2027   |
| Versions 4.x.x | October, 2024   | October, 2026       | Maintenance                       | October, 2027   |
| Versions 5.x.x | October, 2025   | October, 2027       | Active development                | October, 2028   |

V1–V3 entered the Deprecated phase before this policy was formalized. The
January 2027 hard block date provides additional transition time.

## Minimum Supported Version
After each hard block date, the minimum SDK version required to connect to
Stripe will be updated:

- After January 2027: minimum SDK V4.0.0 (V5+ recommended)
- After October 2027: minimum SDK V5.0.0
- After October 2028: minimum SDK V6.0.0 (or later)

## Upgrade Resources
- [Migration guide](https://docs.stripe.com/terminal/references/sdk-migration-guide)
- [SDK versioning and support policy](https://docs.stripe.com/terminal/references/sdk-versioning)
- [Changelog](https://github.com/stripe/stripe-terminal-ios/blob/master/CHANGELOG.md)

## Additional Notes
Tap to Pay functionality within Terminal may have additional constraints
that require upgrades to your SDK in advance of the timeline described in
this document. For more information, see the
[Tap to Pay security guidance](https://docs.stripe.com/terminal/references/ttpa-security-guidance).

This policy applies to all current and future Terminal mobile SDK major
versions (iOS, Android, and React Native).
