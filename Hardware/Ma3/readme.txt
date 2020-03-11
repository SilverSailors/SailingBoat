##
## Ma3 Rotary Encoder (Wind sensor)
##


##
## SPI SETUP Via Raspberry pi
##

##
## 	NOTE: 	As the Pi does not have a ADC (Analog/Digial Converter)
## 		we use a CMP3008 to handle that for us 
##		

#---------------------------------#

    	Raspberry PI Pins 
    
	NOTE: DIAGRAM IS DOES NOT INCLUDE ALL PINS AVAILABLE ON BOARD

            -------
    POWER   | A O |
            | O O |
            | O F |
            | O O |
            | O O |
            | O O |
            | O O |
            | O O |
            | O O |
            | R O |
            | G O |
            | B H |
            -------
            
  	USB CONNECTORS
        
        
    	A = 3.3v PIN
    	F = GND (Ground)
    	R = MOSI
    	G = MISO
    	B = SCLK
    	H = CEO
        
        
#---------------------------------#

	CMP3008

	 --
	0||A
	1||B
	2||C
	3||D
	4||E
	5||F
	6||G
	7||H
	 --	

	Connect as follows: CMPS3008 -> PI
	
	0 - 7 (SPI-CHANNELS)
 
	A -> A
	B -> A
	C -> F
	D -> B
	E -> G
	F -> B
	G -> H
	H -> F
	
	
