####################################################
#
# Makefile SAILBOT PROD
#
####################################################

CC = g++
CFLAGS = -Wall -pthread -D_REENTRANT -lwiringPi -lgps -lcurl
TARGET = sailingBoat
TEST = testSailingBoat
INSTALLBINDIR = /usr/local/bin

# Lägg till eventuella nya källkodsfiler för ditt program här
SOURCES = main.cc \
src/control_unit.cc \
src/module_gps.cc \
src/module_servo.cc \
src/module_wind.cc \
src/module_cmps12.cc \
src/calculation_unit.cc \
src/DataContainers/gps_data.cc \
src/maestro.cc \
src/cmps12.cc \
src/gps.cc \
src/logger.cc \
src/io.cc \

# test-main samt de fristående testfilerna
TESTSOURCES = test/test_main.cc \
test/test_module_wind.cc \
test/test_calculation_unit.cc

all : $(TARGET)

$(TARGET) : $(SOURCES) $(TESTSOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(TESTSOURCES) -DDOCTEST_CONFIG_DISABLE -o $@

install:
	@echo "Installing $(TARGET)..."; cp $(TARGET) $(INSTALLBINDIR)

distclean:
	@echo "Removing $(TARGET)..."; rm $(INSTALLBINDIR)/$(TARGET)

clean :
	rm $(TARGET) *~

test : $(TEST)

$(TEST) : $(SOURCES) $(TESTSOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(TESTSOURCES) -o $@
