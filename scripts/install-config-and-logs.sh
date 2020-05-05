#!/usr/bin/env bash

mkdir -p ${XDG_CONFIG_HOME:-~/.config}/sailingBoat
mkdir -p ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/logs/
mkdir -p ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/

touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/destination.txt
echo "" >> ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/destination.txt
