#!/usr/bin/env bash
# Run this only once!

# Ensure that root runs this script.
if (( $EUID != 0 )); then
    echo "Please run as root"
    exit
fi

cp ../services/boat.service /etc/systemd/system/
cp ../services/run-update.service /etc/systemd/system/

systemctl enable boat.service
systemctl enable run-update.service
systemctl start run-update.service
