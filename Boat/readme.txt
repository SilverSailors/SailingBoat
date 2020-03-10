##
##  HOWTO (GENERAL)
##
    Each Hardware component is wrapped wihtin a module component, this wrapper ensures that all exceptions caused by hardware can be caught by the module
    without extensive fault checking by the user, and will be notified if something went wrong via the module.
    
    
##
##  HOWTO (SETUP) FRESH
##

    1.  Install Desired OS on Raspberry Pi 3 (Rasbian in this project via NOOBS)
    
    2.  Install I2C tools (Optional, determines if compass is properly working and connected)
            
            pi$ sudo apt-get install -y i2c-tools
            
    
    3.  Turn on Following via:
    
            pi$ sudo raspi-config
        
            - I2C
            - SPI
            

    4.  Install GPSD module (GPS Daemon will run the gps on activation)
            
            pi$ sudo apt-get install gpsd
            
            
    5.0 Connect USB to Pi
    
        5.1 make sure that compass USB is connected the the pi.
        
        5.2 Make sure that the POLOLU MAESTRO is connected into the Pololu servo controller and pi USB
    
            - Make sure that paths are correct for both devices (Examine Hardware / Modules)
    
    6.  Install GPSMM to extract daemon data
    
            pi$ sudo apt-get install libgps-dev
            
            
    7.  Activate GPSM daemon (Instructions found in GPS modules readme on how to make program run on boot)
    
    8.  Run primary program. all modules whould show [ OK ] and be ready to collect data/parse data.

##
##  HOWTO (SENSORS [MA3 (Wind), CMPS12 (Compass), GPS (gps))
##

    Each sensor Module on the boat needs to be initialized via the init function 
    
        < module.init() >
    
    once a module has been successfully initialized it will work by running the run command
    
        < module.run() >
        
    once a module has run and has succesfully done so, data can be extracted from the sensor modules
    
        < module.get_reading() >
        
    if a .run() would fail it will not update the current iteration of data, this can be observed via the valid flag set in the data,
    as long as this flag is false after a .run() it means that this set of data was valid in the past but is now deprecated.

    
##
##  HOWTO (SERVOS)
##
    
    The constructors for the servos are
    
        Servo servo(Lower Limit, Upper Limit, Channel),
        
            - Channel represents which channel the Pololu will try to interface with
            
            Upper and lower limits are determined locally, with lower being the minimum value of the servo, and upper being the maximum value.
    
    Servos need to be initialized just like the sensor modules via the init function
    
        < servo.init() >
    
    These servos need a USB connection to connect to the POLULU MAESTRO Channel servo controller. (Make note of which path the USB is using matches the current one)
    
    Once a servo has been successfully initialized it can be used.
    
    this can be done via the usage of the servo.set_target() function, this must match the preset range decided in the constructor, otherwise it will default to the closes allowed value.
    
    
##
##  HOWTO (SETTINGS)
##

    destination.txt
    
        This file takes a format of Lat,Long as our destination coordinates, as many coordinates as desired can be inserted.
        
    sensor_config.txt (WAS NOT USED)
    
        This file was meant to fix calibration faults in sensors, (example, compass is pointing north but is slightly turned and reads 5 degrees, one would add -5 into the compass file to make it read properly 0)
        
        Same thing for the wind sensor
        
    settubgs.txt
    
        this file contains variables which determine thresholds for the waypoint_system implemented (with varying success)
        
