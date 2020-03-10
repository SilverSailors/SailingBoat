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
../Modules/Control_Unit/control_unit.cpp \
../Modules/GPS/Module_GPS.cpp \
../Modules/Servo/Module_SERVO.cpp \
../Modules/Wind_Sensor/Module_Wind_Sensor.cpp \
../Modules/Compass/Module_CMPS12.cpp \
../Modules/Calculation_Unit/calculation_unit.cpp\
../Utilities/utilities.cpp \
../Utilities/Data_Containers/GPS_POSITION.cpp \
../Utilities/Data_Containers/VEC2.cpp \
../Utilities/Data_Containers/LOG.cpp\
../Hardware/GPS/GPS_data.cpp \
../Hardware/MAESTRO/MAESTRO.cpp \
../Hardware/CMPS12/CMPS12.cpp \
../Hardware/CMPS12/CMPS12_data.cpp \
../Hardware/MA3/MA3.cpp \
../Hardware/GPS/GPS.cpp \
../Core/Logger/logger.cpp\
../Core/IO/IO.cpp\
../Core/Parser/Parser.cpp


all : $(TARGET)

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean :
	rm $(TARGET) *~
 
