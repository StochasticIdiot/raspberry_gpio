#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <time.h>
#include <sys/time.h>

#define GPIO_BASE 0x20200000

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int mem_fd;
void *gpio_map;

volatile unsigned *gpio;

int main(void) {
	mem_fd = open("/dev/gpiomem", O_RDWR|O_SYNC);
	if(mem_fd < 0) {
		printf("Can't open /dev/gpiomem \n");
		exit(-1);
	}
	
	gpio_map = (void *) mmap(NULL,
					0xB4, // BLOCK_SIZE
					PROT_READ|PROT_WRITE,
					MAP_SHARED,
					mem_fd,
					0);
	close(mem_fd);
	
	if(gpio_map == MAP_FAILED) {
		printf("mmap error %d\n", (int)gpio_map);
		exit(-1);
	}
	
	gpio = (unsigned *)gpio_map;
	
	printf("Apparently ok.\n");
	
	// #### Configure pin ####
	unsigned int pin = 2;
	unsigned int reg, bitshift;
	// Disable pull-up/down
	*(gpio + 37) &= ~3; //  GPPUD register, disable Pull-up/down
	for(int i=0; i < 150; ++i)
		asm("nop;");
	reg = pin/32;
	bitshift = pin%32;
	*(gpio + 38 + reg) = (1 << bitshift);
	for(int i=0; i < 150; ++i)
		asm("nop;");
	*(gpio + 37) &= ~3;
	*(gpio + 38) = 0;
	
	// Configure led pin as output
	reg = pin/10;
	bitshift = (pin%10)*3;
	*(gpio + reg) = (*(gpio + reg) & ~(7 << bitshift)) | 0x00000001 << bitshift;
	
	// Set pin low
	reg = pin/32;
	bitshift = pin%32;
	*(gpio + 10 + reg) |= (0x00000001 << bitshift);
	
	
	
	struct timespec delay;
	struct timespec half_period;
	
	delay.tv_sec = 0;
	delay.tv_nsec = 500000000;
	half_period.tv_sec = 0;
	half_period.tv_nsec = 50000000;
	while(1) {
		// Set pin high
		printf("Una pedra hi ha al carrer\n");
		*(gpio + 7 + reg) |= (0x00000001 << bitshift);
		for(int i = 0; i < 5; i++) {
			//*(gpio + 7) |= 0x00000001;
			nanosleep(&half_period, NULL);
			//*(gpio + 10) |= 0x00000001;
			nanosleep(&half_period, NULL);
		}
		*(gpio + 10 + reg) |= (0x00000001 << bitshift);
		nanosleep(&delay, NULL);
	}
	
	return 0;
}