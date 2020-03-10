####################################################
#
# Makefile SAILBOT DEMO
#
####################################################

CC = g++
CFLAGS = -Wall -pthread -D_REENTRANT -lwiringPi -lgps
TARGET = boatDemo

# Lägg till eventuella nya källkodsfiler för ditt program här
SOURCES = demo.cpp ../Modules/Compass/Module_CMPS12.cpp ../Modules/Servo/Module_SERVO.cpp ../Modules/GPS/Module_GPS.cpp ../Modules/Wind_Sensor/Module_Wind_Sensor.cpp ../Modules/Calculation_Unit/calculation_unit.cpp ../Utilities/utilities.cpp ../Utilities/Data_Containers/GPS_POSITION.cpp ../Utilities/Data_Containers/VEC2.cpp ../Hardware/GPS/GPS.cpp ../Hardware/CMPS12/CMPS12.cpp ../Hardware/CMPS12/CMPS12_data.cpp ../Hardware/MA3/MA3.cpp ../Hardware/MAESTRO/MAESTRO.cpp ../Hardware/GPS/GPS_data.cpp 

all : $(TARGET)

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean :
	rm $(TARGET) *~
