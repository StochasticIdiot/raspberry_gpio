CPP=arm-linux-gnueabihf-gcc
CFLAGS=-Wall -Wextra -Werror -std=c++11 --sysroot=$(HOME)/Raspberry/rootfs
INCLUDE_PATH=-Isrc -I$(HOME)/Raspberry/rootfs/arm-linux-gnueabihf -I$(HOME)/Raspberry/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/../arm-linux-gnueabihf/libc
LIB_DIR=-L$(HOME)/Raspberry/rootfs/usr/local/lib -L$(PWD)/lib

NAME := rpigpio
MAJOR := 0
MINOR := 0
COMPAT := 0
VERSION := $(MAJOR).$(MINOR).$(COMPAT)
#VERSION := $(MAJOR).$(MINOR)

all: lib lib/lib$(NAME).so.$(VERSION) bin/gpio_test bin/lib_test bin/lib_test_shared

.phony: lib

lib: lib/lib$(NAME).so.$(VERSION)

#################################################################################################
# Generate lib_test_shared executable,
# It's the same code as lib_test but in this case the library is shared
# Used to test if the library is properly setup.
#################################################################################################
bin/lib_test_shared: build/lib_test.o lib/lib$(NAME).so.$(VERSION)
	$(CPP) -o bin/lib_test_shared build/lib_test.o $(LIB_DIR) -lrpigpio -lstdc++
	
##################################################################################################
# Compile lib_test, a program made to test the library
# In this case using dierctly the library object file
# Test if the library works
##################################################################################################
bin/lib_test: build/lib_test.o build/raspberry_gpio.o
	$(CPP) -o bin/lib_test build/lib_test.o build/raspberry_gpio.o -lstdc++

build/lib_test.o: test/lib_test.cpp
	$(CPP) -c $(CFLAGS) test/lib_test.cpp $(INCLUDE_PATH) -o build/lib_test.o

##################################################################################################
# Compile gpio_test, program made only to test the gpio
##################################################################################################
bin/gpio_test: build/main.o
	$(CPP) -o bin/gpio_test build/main.o

build/main.o: test/gpio_test.cpp
	$(CPP) -c $(CFLAGS) test/gpio_test.cpp -o build/main.o

###################################################################################################
# Compile and create shared library
###################################################################################################
lib/lib$(NAME).so.$(VERSION): build/raspberry_gpio.o
	$(CPP) -shared -lstdc++ -o lib/lib$(NAME).so.$(VERSION) build/raspberry_gpio.o $(INCLUDE_PATH)

build/raspberry_gpio.o: src/raspberry_gpio.cpp
	$(CPP) -c $(CFLAGS) -fpic -Wl,-soname,lib$(NAME).so.$(MAJOR) src/raspberry_gpio.cpp -o build/raspberry_gpio.o