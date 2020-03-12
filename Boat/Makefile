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
../Modules/GPS/module_gps.cpp \
../Modules/Servo//module_servo.cpp \
../Modules/WindSensor/module_wind_sensor.cpp \
../Modules/CMPS12/module_cmps12.cpp \
../Modules/CalculationUnit/calculation_unit.cpp\
../Utilities/utilities.cpp \
../Utilities/DataContainers/gps_position.cpp \
../Utilities/DataContainers/vec2.cpp \
../Utilities/DataContainers/log.cpp\
../Hardware/GPS/gps_data.cpp \
../Hardware/Maestro/maestro.cpp \
../Hardware/CMPS12/cmps12.cpp \
../Hardware/CMPS12/cmps12_data.cpp \
../Hardware/MA3/ma3.cpp \
../Hardware/GPS/gps.cpp \
../Core/Logger/logger.cpp\
../Core/IO/io.cpp\
../Core/Parser/parser.cpp

all : $(TARGET)

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean :
	rm $(TARGET) *~
 
