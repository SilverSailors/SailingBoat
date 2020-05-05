#!/usr/bin/env bash
# Run this only once!

# Ensure that root runs this script.
if (( $EUID != 0 )); then
    echo "Please run as root"
    exit
fi

cp ../services/boat.service /etc/systemd/system/

systemctl enable boat.service