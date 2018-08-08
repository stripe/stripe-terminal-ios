#!/bin/bash

echo '▸ Installing dependencies for Example.xcodeproj';

if [[ -e Cartfile.resolved ]]; then
  rm Cartfile.resolved;
fi

if ! command -v carthage > /dev/null; then
  echo ''
  echo 'ERROR: Please install carthage before running setup.sh:'
  echo 'https://github.com/Carthage/Carthage#installing-carthage';
  exit 1;
fi

carthage update --platform ios --no-use-binaries;

echo '▸ Finished installing dependencies for Example.xcodeproj';
