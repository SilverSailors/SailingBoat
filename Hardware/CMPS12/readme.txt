##
## CMPS12
##

##
## I2C SETUP via Raspberry Pi 3b+
##

#---------------------------------#

    Raspberry PI Pins 
    
            -------
    POWER   | A O |
            | B O |
            | C F |
            | O O |
            | O O |
            | O O |
            | O O |
            | O O |
            | O O |
            | O O |
            | O O |
            -------
            
        USB CONNECTORS
        
        
    A = 3.3v PIN
    B = (SDA) GPIO 2
    C = (SCL) GPIO 3
    F = GND (Ground)
        
        
#---------------------------------#

    CMPS12 PINS
        
            CMPS12
            -----
            | A |
            | B |
            | C |
            | D |
            | E |
            | F |
            -----
        
    A = 3.3V
    B = SDA/TX
    C = SCL/TX
    D = Mode (I2C Default, Connect for Serial)  [UNUSED]
    E = Factory use                             [UNUSED]
    F = 0v GND (Ground)

#---------------------------------#

##
##  HARDWARE INSTRUCTIONS
##
        
    Connect A->A For all PINS Of corresponding Letter 
    (Power Supply of 3.3v might be taken so split the power source from somewhere else in that case (Be Vary of using 5v))
    
    PI Should detect I2C Port 
    (See I2C Instructions for details on setting up I2C on the PI)
    
    
##
##  REGISTRY (I2C MODE)
##

     [0x01] = COMMAND_WRITE
     [0x00] =
     [0x00] =
     [0x00] =
     [0x00] =
     [0x00] =
     [0x00] =
     [0x00] =
     [0x00] =
     [0x00] =
     [0x00] =
     [0x00] =





    
    
