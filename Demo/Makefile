####################################################
#
# Makefile SAILBOT DEMO
#
####################################################

CC = g++
CFLAGS = -Wall -pthread -D_REENTRANT -lwiringPi -lgps
TARGET = boatDemo

# Lägg till eventuella nya källkodsfiler för ditt program här
SOURCES = demo.cpp \
../Modules/CMPS12/module_cmps12.cpp \
../Modules/Servo//module_servo.cpp \
../Modules/GPS/module_gps.cpp \
../Modules/WindSensor/module_wind_sensor.cpp \
../Modules/CalculationUnit/calculation_unit.cpp \
../Utilities/utilities.cpp \
../Utilities/DataContainers/gps_position.cpp \
../Utilities/DataContainers/vec2.cpp \
../Hardware/GPS/gps.cpp \
../Hardware/CMPS12/cmps12.cpp \
../Hardware/CMPS12/cmps12_data.cpp \
../Hardware/MA3/ma3.cpp \
../Hardware/Maestro/maestro.cpp \
../Hardware/GPS/gps_data.cpp

all : $(TARGET)

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean :
	rm $(TARGET) *~
