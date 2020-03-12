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
../Modules/ModuleCmps12/module_cmps12.cpp \
../Modules/ModuleServo//module_servo.cpp \
../Modules/ModuleGps/module_gps.cpp \
../Modules/ModuleWindSensor/module_wind_sensor.cpp \
../Modules/CalculationUnit/calculation_unit.cpp \
../Utilities/utilities.cpp \
../Utilities/DataContainers/gps_position.cpp \
../Utilities/DataContainers/vec2.cpp \
../Hardware/Gps/gps.cpp \
../Hardware/Cmps12/cmps12.cpp \
../Hardware/Cmps12/cmps12_data.cpp \
../Hardware/Ma3/ma3.cpp \
../Hardware/Maestro/maestro.cpp \
../Hardware/Gps/gps_data.cpp

all : $(TARGET)

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean :
	rm $(TARGET) *~
