####################################################
#
# Makefile SAILBOT PROD
#
####################################################

CC = g++
CFLAGS = -Wall -pthread -D_REENTRANT -lwiringPi -lgps
TARGET = boat

# Lägg till eventuella nya källkodsfiler för ditt program här
SOURCES = main.cc \
../Modules/ControlUnit/control_unit.cc \
../Modules/GPS/module_gps.cc \
../Modules/Servo//module_servo.cc \
../Modules/WindSensor/module_wind_sensor.cc \
../Modules/CMPS12/module_cmps12.cc \
../Modules/CalculationUnit/calculation_unit.cc \
../Utilities/utilities.cc \
../Utilities/DataContainers/gps_position.cc \
../Utilities/DataContainers/vec2.cc \
../Utilities/DataContainers/log.cc \
../Hardware/GPS/gps_data.cc \
../Hardware/Maestro/maestro.cc \
../Hardware/CMPS12/cmps12.cc \
../Hardware/CMPS12/cmps12_data.cc \
../Hardware/MA3/ma3.cc \
../Hardware/GPS/gps.cc \
../Core/Logger/logger.cc \
../Core/IO/io.cc \
../Core/Parser/parser.cc

all : $(TARGET)

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean :
	rm $(TARGET) *~
 
