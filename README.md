# SailingBoat
    Sailboat application for URSC 2020

# Setup
    The following has been used for this application:
    
        - Raspberry Pi 3 WiFi - Arch Linux ARM
        - CMPS 12 - Compass unit
        - MAESTRO - Servo unit
        - MA3 Digital - Analog potentiometer
        - GlobalSat GPS Receiver
        - RC Laser sailing boat
        - Futaba RC Receiver
        - Futaba RC Controller
        - RC Switch (RC -> digital)

## General (HOWTO)
    Each Hardware component is wrapped wihtin a module component, this wrapper
    ensures that all exceptions caused by hardware can be caught by the module
    without extensive fault checking by the user, and will be notified if
    something went wrong via the module.
    
## Base installation
    Download Archlinux ARM for Raspberry Pi 3 and follow the installation guide:
    [Archlinux ARM](https://archlinuxarm.org/platforms/armv8/broadcom/raspberry-pi-3)
    
    After installation, install following packages:
        - i2c-tools
        - gpsd
        - [WiringPi](https://github.com/WiringPi/WiringPi)
    
    Initial configuration:
    
    Edit the file *boot/cmdline.txt* and remove entries with *ttyAMA0(ex. console=ttyAMA0,115200)*.
    
    Edit the file *boot/config.txt*
        - Uncomment the line *device_tree_param=i2c_arm=on*.
        - Uncomment the line *device_tree_param=i2s=on*.
        - Uncomment the line *device_tree_param=psi=on*.
    
    Edit the file */etc/modules-load.d/raspberrypi.conf*.
        - Add line *i2c-bcm2708*.
        - Add line *i2c-dev*.
    
    Edit the file */etc/hostname*.
        - Change text to *sailbot*.
    
    for more information about devices on the raspberry pi go to: [this link](https://archlinuxarm.org/wiki/Raspberry_Pi)
    
    
    
# Hardware
    Each hardware component represents the hard connection to the device it is
    speaking from->to.
    
    
# Modules
    Modules will perform the required adaptation of our raw data which our
    hardware components aquire.
    
# Procedure

1. Determine destination (Latitude, Longitude)
2. Check wind to determine best angle of approach (AOA)
3. Select angle and set a waypoint (in meters)
4. Each update cycle, compare our current bearing vector and adjust the
   waypoint, adjust bearing as neccesary.
5. repeat step 2->4.
