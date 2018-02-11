#ifndef _RASPBERRY_GPIO_HPP
#define _RASPBERRY_GPIO_HPP

#include <iostream>

#include <sys/mman.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>

const unsigned int GPIO_BASE_ADDR = 0x20200000;
const unsigned int GPIO_MEM_LENGTH = 0xB4;

const unsigned int GPIO_NUM_PINS = 54;

const unsigned int GPIO_PUD_CONTROL_OFFSET = 0;
const unsigned int GPIO_PUD_CONTROL_PULL_DOWN = 1;
const unsigned int GPIO_PUD_CONTROL_PULL_UP = 2;

const unsigned int GPIO_GPFSEL_OFFSET = 0;
//const unsigned int GPIO_REG_NUM_GPFSEL0 = 0;
//const unsigned int GPIO_REG_NUM_GPFSEL1 = 1;
//const unsigned int GPIO_REG_NUM_GPFSEL2 = 2;
//const unsigned int GPIO_REG_NUM_GPFSEL3 = 3;
//const unsigned int GPIO_REG_NUM_GPFSEL4 = 4;
//const unsigned int GPIO_REG_NUM_GPFSEL5 = 5;

const unsigned int GPIO_GPSET_OFFSET = 7;
//const unsigned int GPIO_GPSET0_REG_OFFS = 7;
//const unsigned int GPIO_REG_NUM_GPSET1 = 8;

const unsigned int GPIO_GPCLR_OFFSET = 10;
//const unsigned int GPIO_REG_NUM_GPCLR0 = 10;
//const unsigned int GPIO_REG_NUM_GPCLR1 = 11;

const unsigned int GPIO_GPLEV_OFFSET = 	13;
//const unsigned int GPIO_REG_NUM_GPLEV0 = 13;
//const unsigned int GPIO_REG_NUM_GPLEV1 = 14;

const unsigned int GPIO_GPPUD_OFFSET = 37;
const unsigned int GPIO_GPPUDCLK_OFFSET = 38;
//const unsigned int GPIO_REG_NUM_GPPUDCLK0 = 38;
//const unsigned int GPIO_REG_NUM_GPPUDCLK1 = 39;


const unsigned int GPIO_MODE_INPUT = 0;
const unsigned int GPIO_MODE_OUTPUT = 1;

const unsigned int GPIO_PULL_NONE = 0;
const unsigned int GPIO_PULL_DOWN = 1;
const unsigned int GPIO_PULL_UP = 2;
const unsigned int GPIO_PULL_DEFAULT = 3;

const unsigned int GPIO_LOW = 0;
const unsigned int GPIO_HIGH = 1;

const unsigned int GPIO_BCM_0 = 0;
const unsigned int GPIO_BCM_1 = 1;
const unsigned int GPIO_BCM_2 = 2;
const unsigned int GPIO_BCM_3 = 3;
const unsigned int GPIO_BCM_4 = 4;
const unsigned int GPIO_BCM_5 = 5;
const unsigned int GPIO_BCM_6 = 6;
const unsigned int GPIO_BCM_7 = 7;
const unsigned int GPIO_BCM_8 = 8;
const unsigned int GPIO_BCM_9 = 9;

const unsigned int GPIO_BCM_10 = 10;
const unsigned int GPIO_BCM_11 = 11;
const unsigned int GPIO_BCM_12 = 12;
const unsigned int GPIO_BCM_13 = 13;
const unsigned int GPIO_BCM_14 = 14;
const unsigned int GPIO_BCM_15 = 15;
const unsigned int GPIO_BCM_16 = 16;
const unsigned int GPIO_BCM_17 = 17;
const unsigned int GPIO_BCM_18 = 18;
const unsigned int GPIO_BCM_19 = 19;

const unsigned int GPIO_BCM_20 = 20;
const unsigned int GPIO_BCM_21 = 21;
const unsigned int GPIO_BCM_22 = 22;
const unsigned int GPIO_BCM_23 = 23;
const unsigned int GPIO_BCM_24 = 24;
const unsigned int GPIO_BCM_25 = 25;
const unsigned int GPIO_BCM_26 = 26;
const unsigned int GPIO_BCM_27 = 27;
const unsigned int GPIO_BCM_28 = 28;
const unsigned int GPIO_BCM_29 = 29;

const unsigned int GPIO_BCM_30 = 30;
const unsigned int GPIO_BCM_31 = 31;
const unsigned int GPIO_BCM_32 = 32;
const unsigned int GPIO_BCM_33 = 33;
const unsigned int GPIO_BCM_34 = 34;
const unsigned int GPIO_BCM_35 = 35;
const unsigned int GPIO_BCM_36 = 36;
const unsigned int GPIO_BCM_37 = 37;
const unsigned int GPIO_BCM_38 = 38;
const unsigned int GPIO_BCM_39 = 39;

const unsigned int GPIO_BCM_40 = 40;
const unsigned int GPIO_BCM_41 = 41;
const unsigned int GPIO_BCM_42 = 42;
const unsigned int GPIO_BCM_43 = 43;
const unsigned int GPIO_BCM_44 = 44;
const unsigned int GPIO_BCM_45 = 45;
const unsigned int GPIO_BCM_46 = 46;
const unsigned int GPIO_BCM_47 = 47;
const unsigned int GPIO_BCM_48 = 48;
const unsigned int GPIO_BCM_49 = 49;

const unsigned int GPIO_BCM_50 = 50;
const unsigned int GPIO_BCM_51 = 51;
const unsigned int GPIO_BCM_52 = 52;
const unsigned int GPIO_BCM_53 = 53;

class Gpio {
	volatile unsigned int *gpio;
	
	void waitPUDClock(); // Wait 150 cycles
	bool validatePin(unsigned int pin);
public:
	Gpio();
	~Gpio();
	
	int init(const char *file="/dev/gpiomem");
	
	void initPin(unsigned int pin, unsigned int mode, unsigned int pull_up_down=GPIO_PULL_DEFAULT);
	void setPin(unsigned int pin, unsigned int mode);
	int readPin(unsigned int pin);
	
	void setPinPulling(unsigned int pin, unsigned int mode);
	
	//void configurePin(int pin, unsigned int mode){this->configurePin((unsigned int) pin, (unsigned int) mode);};
	//void setPin(int pin){this->setPin((unsigned int)pin);};
	//void clearPin(int pin){this->clearPin((unsigned int)pin);};
	
	// Set pull-up/down of a given pin
	//void setPUD(unsigned int pin, unsigned int mode);
	//void setPUD(int pin, unsigned int mode){this->setPUD((unsigned int)pin, mode);};
};


#endif