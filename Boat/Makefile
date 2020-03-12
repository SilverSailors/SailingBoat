####################################################
#
# Makefile SAILBOT PROD
#
####################################################

CC = g++
CFLAGS = -Wall -pthread -D_REENTRANT -lwiringPi -lgps
TARGET = boat

# Lägg till eventuella nya källkodsfiler för ditt program här
SOURCES = main.cpp \
../Modules/ControlUnit/control_unit.cpp \
../Modules/ModuleGps/module_gps.cpp \
../Modules/ModuleServo//module_servo.cpp \
../Modules/ModuleWindSensor/module_wind_sensor.cpp \
../Modules/ModuleCmps12/module_cmps12.cpp \
../Modules/CalculationUnit/calculation_unit.cpp\
../Utilities/utilities.cpp \
../Utilities/DataContainers/gps_position.cpp \
../Utilities/DataContainers/vec2.cpp \
../Utilities/DataContainers/log.cpp\
../Hardware/Gps/gps_data.cpp \
../Hardware/Maestro/maestro.cpp \
../Hardware/Cmps12/cmps12.cpp \
../Hardware/Cmps12/cmps12_data.cpp \
../Hardware/Ma3/ma3.cpp \
../Hardware/Gps/gps.cpp \
../Core/Logger/logger.cpp\
../Core/Io/io.cpp\
../Core/Parser/parser.cpp

all : $(TARGET)

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean :
	rm $(TARGET) *~
 
