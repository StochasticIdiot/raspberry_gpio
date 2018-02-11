#include "raspberry_gpio.hpp"

Gpio::Gpio() {
	this->gpio = nullptr;
}

Gpio::~Gpio() {
	if(this->gpio != nullptr) {
		munmap((void *)gpio, GPIO_MEM_LENGTH);
	}
}

int Gpio::init(const char *file) {
	int mem_fd;
	void *gpio_map;
	//unsigned int BLOCK_SIZE = 4*1024;
	
	mem_fd = open("/dev/gpiomem", O_RDWR|O_SYNC);
	if(mem_fd < 0) {
		std::cout << "Error: Can't open " << file << std::endl;
		return -1;
	}
	
	gpio_map = (void *)mmap(NULL,
					GPIO_MEM_LENGTH, //BLOCK_SIZE,
					PROT_READ|PROT_WRITE,
					MAP_SHARED,
					mem_fd,
					0);
	close(mem_fd);
	
	if(gpio_map == MAP_FAILED) {
		std::cout << "Error: mmap " << (unsigned int) gpio_map << std::endl;
		return -1;
	}
	
	this->gpio = (volatile unsigned int*)gpio_map;
	return 0;
}

bool Gpio::validatePin(unsigned int pin) {
	if(pin >= GPIO_NUM_PINS || this->gpio == nullptr)
		return false;
	return true;
}

void Gpio::initPin(unsigned int pin, unsigned int mode, unsigned int pull_up_down) {
	unsigned int reg;
	unsigned int shift;
	
	if(!this->validatePin(pin)) {
		std::cout << "initPin: Not a valid pin." << std::endl;
		return;
	}
	
	reg = pin/10;
	shift = (pin%10) * 3;
	
	// Sets pin pull-up/down:
	if(pull_up_down < GPIO_PULL_DEFAULT) {
		this->setPinPulling(pin, pull_up_down);
	}
	
	*(this->gpio + GPIO_GPFSEL_OFFSET + reg) &= ~(0x7 << shift);
	*(this->gpio + GPIO_GPFSEL_OFFSET + reg) |= (mode << shift);
}

void Gpio::waitPUDClock() {
	for(int i = 0; i < 150; ++i)
		asm ("nop;");
}

void Gpio::setPinPulling(unsigned int pin, unsigned int mode) {
	unsigned int reg;
	unsigned int shift;
	
	if(!this->validatePin(pin))
		return;
	
	reg = pin/32;
	shift = pin%32;
	
	*(this->gpio + GPIO_GPPUD_OFFSET) &= ~3;
	*(this->gpio + GPIO_GPPUD_OFFSET) |= mode;
	
	this->waitPUDClock();
	*(this->gpio + GPIO_GPPUDCLK_OFFSET + reg) = (1 << shift);
	this->waitPUDClock();
	
	*(this->gpio + GPIO_GPPUD_OFFSET) &= ~3;
	*(this->gpio + GPIO_GPPUDCLK_OFFSET + reg) = 0;
}

void Gpio::setPin(unsigned int pin, unsigned int mode) {
	unsigned int reg;
	unsigned int shift;
	
	if(!this->validatePin(pin))
		return;
	
	reg = pin/32;
	shift = pin%32;
	
	if(mode == GPIO_LOW)
		*(this->gpio + GPIO_GPCLR_OFFSET + reg) = (0x1 << shift);
	else
		*(this->gpio + GPIO_GPSET_OFFSET + reg) = (0x1 << shift);
}