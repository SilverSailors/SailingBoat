#!/bin/sh

# Ensuring that root runs this.
# if (( $EUID != 0 )); then
#     echo "Please run as root"
#     exit
# fi

mkdir -p ${XDG_CONFIG_HOME:-~/.config}/sailingBoat
mkdir -p ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/logs/
mkdir -p ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/


touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/settings.txt
touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/sensor_config.txt
touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/destination.txt

touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/logs/waypoint.txt
touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/logs/contest.txt
