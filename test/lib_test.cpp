/**
 * librpigpio test
 **/
#include "raspberry_gpio.hpp"


int main(void) {
	Gpio gpio;
	
	if(gpio.init() < 0) {
		exit(-1);
	}
	unsigned int pins[] = {0, 1, 2, 3, 4};
	
	for(int i = 0; i < 5; i++) {
		gpio.initPin(pins[i], GPIO_MODE_OUTPUT, GPIO_PULL_NONE);
	}
	
	int n = 0;
	unsigned int led = 0;
	while(1) {
		for(int i = 1; i < 5; i++)
			gpio.setPin(pins[i], GPIO_LOW);
		sleep(1);
		gpio.setPin(pins[n], GPIO_HIGH);
		sleep(1);
		n = n + 1;
		if(n > 4) {
			n = 1;
			led = 1 - led;
			gpio.setPin(pins[0], led);
		}
	}
	
	return 0;
}