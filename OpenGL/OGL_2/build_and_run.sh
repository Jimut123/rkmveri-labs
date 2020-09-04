#!/bin/sh

DIRECTORY=build

if [ -d "$DIRECTORY" ]
then
  # Control will enter here if $DIRECTORY exists.
  echo "Yes Build Directory Exists.. Deleting directory $DIRECTORY"
  rm -rf $DIRECTORY
fi
echo "Building from scratch ..."
meson build
echo "Compiling using Meson ..."
meson compile -C build
echo "Running ..."
meson test -C build

