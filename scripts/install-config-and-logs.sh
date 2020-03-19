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
echo "# Distance Threshold (Meters)
# How far should we be to our waypoints before getting a new one
5.0

# Time Threshold (How long should we wait before we establish a new waypoint
# (If we dont manage to get to our current one in time) [Seconds]
30

# Distance Factor (How far away should waypoints be (In Accordance to our goal, 2.0 means halfway, 3.0 a third)
2.0

# Waypoint Constraint (Meters)
# Once we get close to our destination our waypoints will become smaller and smaller
# This value determines the lower limit, if we go below it we default to our value
1.0" >> ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/settings.txt

touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/sensor_config.txt
echo "
#COMPASS OFFSET
0

#WIND SENSOR OFFSET
0" >> ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/sensor_config.txt

touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/destination.txt
echo "# Coordinates for our goal
# Latitude Longitude
# (NOTE THE Delimiter ',')
60.10466745530005,19.94494629695896
60.105162915344735,19.944656985343613" >> ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/settings/destination.txt

touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/logs/waypoint.json
touch ${XDG_CONFIG_HOME:-~/.config}/sailingBoat/logs/contest.json
