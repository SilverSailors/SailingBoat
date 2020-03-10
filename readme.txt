##
## SAILING ROBOT 2019
##

    - At worst, we'll have a submarine.

##
## DOCUMENTATION
##


##
##  HARDWARE
##############
##  Each hardware component represents the hard connection to the device it is speaking from->to.
##

##
##  MODULES
##############
##  Modules will perform the required adaptation of our raw data which our hardware components aquire.
##


##
## PROCEDURE
##


	1. DETERMINE DESTINATION (LAT, LON)

	2. CHECK WIND TO DETERMINE BEST ANGLE OF APPROACH

	3. SELECT ANGLE AND A SET A WAYPOINT (IN METERS)

	4. EACH UPDATE CYCLE, COMPARE OUR CURRENT BEARING VECTOR
	   AGAINST THE WAYPOINT, ADJUST BEARING AS NESSECARY.
	   
	5. REPEAT 2->4.