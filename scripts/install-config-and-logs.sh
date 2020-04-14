#!/usr/bin/env bash

mkdir -p ${XDG_CONFIG_HOME:-~/.config}/sailingBoat
mkdir -p ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/logs/
mkdir -p ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/

touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/destination.txt
echo " 60.10466745530005
19.94494629695896
60.105162915344735
19.944656985343613" >> ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/destination.txt

touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/logs/waypoint.json
touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/logs/contest.json
