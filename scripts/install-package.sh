#!/bin/sh

# Ensuring that root runs this.
if (( $EUID != 0 )); then
    echo "Please run as root"
    exit
fi

# Check linux version is used, a consdensed list is used, as these are most likely the most used ones.
function linux_type
{
	which dnf &&    { echo fedora; return; }
	which apt &&    { echo debian; return; }
	which pacman && { echo arch; return;   }
}

## this will check if there's either fedora, debian(or it's derivatives) or pacman(or derivatives)
## Then install the approriate packages in order to both use the services needed, as well as the libraries
## to both run and program the application.
if (( linux_type == fedora ))
	then
	sudo dnf install -y i2c-tools gpsd gpsd-devel cmake boost boost-devel
	git clone https://github.com/WiringPi/WiringPi.git
	cd WiringPi
	sh build
elif (( linux_type == debian ))
	then
	sudo apt install -y i2c-tools libgps-dev libboost-all-dev
	git clone https://github.com/WiringPi/WiringPi.git
	cd WiringPi
	sh build
elif (( linux_type == pacman ))
	then
	yes | sudo pacman -S i2c-tools gpsd boost boost-libs
	git clone https://github.com/WiringPi/WiringPi.git
	cd WiringPi
	sh build
else
	echo "You do not have one of the most used linux distributions, please use it."
fi
