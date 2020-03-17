#!/bin/sh

# Run this file on boot after network.target is up,
# to ensure that the application is running the latest version of the application,
# and can therefore ensure that the application will work.

# Ensuring that root runs this.
if (( $EUID != 0 )); then
    echo "Please run as root"
    exit
fi

# Get the latest version from github.
git pull

# Go to Boat directory and make the sailingBoat binary
rm sailingBoat
make -j $(nproc)

# Check if sailingBoat is already installed, if true, then remove old
# and install new, otherwise just install
if [ -x "$(command -v sailingBoat)" ]; then
	make distclean
	make install
else
	make install
fi

