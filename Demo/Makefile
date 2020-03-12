####################################################
#
# Makefile SAILBOT DEMO
#
####################################################

CC = g++
CFLAGS = -Wall -pthread -D_REENTRANT -lwiringPi -lgps
TARGET = boatDemo

# Lägg till eventuella nya källkodsfiler för ditt program här
SOURCES = demo.cc \
../Modules/CMPS12/module_cmps12.cc \
../Modules/Servo//module_servo.cc \
../Modules/GPS/module_gps.cc \
../Modules/WindSensor/module_wind_sensor.cc \
../Modules/CalculationUnit/calculation_unit.cc \
../Utilities/utilities.cc \
../Utilities/DataContainers/gps_position.cc \
../Utilities/DataContainers/vec2.cc \
../Hardware/GPS/gps.cc \
../Hardware/CMPS12/cmps12.cc \
../Hardware/CMPS12/cmps12_data.cc \
../Hardware/MA3/ma3.cc \
../Hardware/Maestro/maestro.cc \
../Hardware/GPS/gps_data.cc

all : $(TARGET)

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean :
	rm $(TARGET) *~
